
# 🌌 Tinky-Winky

Welcome to **Tinky-Winky**! This project offers a unique experience in Windows development, allowing you to dive into creating system services and low-level monitoring tools in C. Get ready to explore the inner workings of Windows with Tinky-Winky! 🚀

## 📜 Project Description

Tinky-Winky consists of two main components:

1. **`svc.exe` (Tinky Service)**: A Windows service that allows installing, starting, stopping, and deleting the service named "tinky." This service launches the keylogger with elevated permissions to ensure it operates even in restricted environments.

2. **`winkey.exe` (Winkey Keylogger)**: A keylogger that monitors keystrokes and logs user activity, associating each keystroke with the active process at that time. The log includes the timestamp and the foreground process name, with support for the system's regional configuration.

## ✨ Key Features

- **👤 System Impersonation**: The `tinky` service performs system token impersonation, allowing it to operate with elevated permissions and launch the keylogger securely.
- **📂 Configurable Settings**: Through the optional `winkey.ini` file, you can define the path for the keystroke log file using the `path` variable.
- **🧩 Advanced Regional Handling**: The keylogger adapts keystroke capture according to the current keyboard layout.
- **🔍 Active Process Detection**: `winkey.exe` logs keystrokes along with the active process name and timestamp, providing a complete view of user activity.
- **🔒 Error Handling and Security**: A robust logging system ensures any errors are documented in detail, making troubleshooting straightforward.
- **🚫 Single Instance Control**: Only one instance of the keylogger can run at a time, preventing conflicts.

## 🚀 Usage Examples

### 🔧 Service Installation and Management
```bash
svc.exe install
svc.exe start
svc.exe stop
svc.exe delete
```

### 📝 Keystroke Logging

The generated log file (`winkey.log`) contains entries in a human-readable format:
```
[08.10.2024 12:34:56] - 'Google Chrome'
Ctrl+T
[08.10.2024 12:35:02] - 'Visual Studio Code'
H e l l o   W o r l d
```

### ⚙️ Optional Configuration with `winkey.ini`

Example `winkey.ini`:
```ini
[config]
path=C:\Users\cescanue\ProyectosWin\outcore\tinky\winkey.log
```

## 📁 Project Structure

```
tinky-winky/
├── svc.exe          # Windows Service
├── winkey.exe       # Keylogger
├── winkey.ini       # Optional configuration file for log path
├── svc.cpp          # Source code for the service
├── winkey.c         # Source code for the keylogger
├── Makefile         # Makefile for building the project
├── winkey.log       # Example log file
└── older/           # Older versions and tests
```

## 🖥️ Requirements

- **Operating System**: Windows 10 or newer.
- **Compiler**: `CL` and `NMAKE` from Visual Studio.
- **Disable Windows Defender**: It may be necessary to disable or configure the antivirus to allow the keylogger to function properly.

## 🌐 Contributions

Contributions are welcome! If you have ideas to improve the project or want to add new features, feel free to fork the repository and submit a pull request.
