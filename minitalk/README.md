
# 🛰️ Minitalk - UNIX Signal-Based Communication

**Minitalk** is a project designed to explore UNIX signal-based communication by implementing a client-server model. The objective is to send messages between a client and server using only UNIX signals. This project is an exercise in low-level data communication, demonstrating how strings can be encoded, transmitted, and decoded using just two signals: `SIGUSR1` and `SIGUSR2`. 🚀

---

## 🎯 Project Overview

In **Minitalk**, the server waits for incoming signals from the client, which encodes a message using the signals. The server decodes these signals back into a string and displays it. The challenge is to achieve fast, reliable communication using only UNIX signals, which is an unconventional method for data transmission.

---

## 🚀 Key Features

- **Client-Server Communication**: The client sends a string to the server, which decodes and prints the received message.
- **Signal-Based Data Transfer**: The project uses only `SIGUSR1` and `SIGUSR2` signals for communication.
- **Multiple Clients**: The server can handle multiple client connections consecutively without needing to restart.
- **Error Handling**: The program handles errors gracefully, ensuring there are no memory leaks or unexpected crashes.

---

## 📋 Usage

To compile and run the server and client:

1. **Start the server**:
   ```bash
   ./server
   ```

   The server will display its Process ID (PID) and wait for incoming messages.

2. **Run the client**:
   ```bash
   ./client <server_PID> <message>
   ```

   The client will send the message to the server using UNIX signals.

---

## 📂 Project Structure

```
minitalk/
│
├── Makefile                # Build instructions
├── includes/               # Header files
├── srcs/                   # Source code files
│   ├── client.c            # Client-side logic
│   ├── server.c            # Server-side logic for handling signals
│   └── server2.c           # Additional server-side functionality
└── ft_printf/              # Custom printf implementation
```

---

## 🛠️ Code Highlights

### 1. **Signal Encoding and Decoding**:
   - The server decodes the message by interpreting incoming signals (`SIGUSR1` and `SIGUSR2`) as binary bits. The client encodes the message string into these signals and sends them one by one.

   - **Signal Handling**: The server uses `sigaction` to handle signals asynchronously, ensuring the signals are processed correctly without race conditions.

### 2. **UNIX Signal Mechanism**:
   - The communication is implemented using only the `kill()` function to send signals and `sigaction()` to receive and process them. This is an unconventional method, highlighting how low-level system features can be used for communication.
   
### 3. **Handling Multiple Clients**:
   - The server can process multiple messages from different clients consecutively without needing to restart, thanks to its ability to continuously listen for new signals.

---

## 🏅 Conclusion

**Minitalk** is an excellent exercise in low-level system programming, demonstrating how to communicate between processes using UNIX signals. The use of `SIGUSR1` and `SIGUSR2` for message transmission makes the project both unique and challenging, pushing the boundaries of how data can be transferred with limited resources.
