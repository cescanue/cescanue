
# 🌐 ft_irc - Internet Relay Chat Server

Welcome to **ft_irc**, an IRC (Internet Relay Chat) server built in **C++98**, designed to manage real-time communication between multiple clients. This project replicates the core features of an IRC server while incorporating best programming practices and advanced non-blocking network management concepts. 🚀

---

## 🎯 Project Overview

`ft_irc` is an IRC server that enables communication between multiple users through channels. It uses the IRC protocol to allow clients to connect, send messages, join channels, and manage accounts. The server is lightweight and efficient, designed to support non-blocking operations using the `poll()` system or equivalent methods.

---

## 🚀 Key Features

- **🔐 Secure Authentication**: Users must provide a password to connect to the server.
- **📡 TCP/IP Connection**: Supports both IPv4 and IPv6, utilizing low-level sockets.
- **📚 Non-Blocking Operations**: Implemented using `poll()` to manage all I/O operations, ensuring the server doesn’t block even under high loads.
- **👥 Multi-Client Support**: The server can handle multiple connected clients simultaneously.
- **💬 Channel System**: Users can join channels, send messages, and manage channel states (e.g., setting topics, user limits, etc.).
- **👤 Operators and Users**: Differentiates between regular users and channel operators, with exclusive commands for operators:
  - `KICK`: Remove a user from the channel.
  - `INVITE`: Invite a user to a channel.
  - `TOPIC`: Change the channel’s topic.
  - `MODE`: Manage channel modes such as `invite-only`, `password`, and more.

---

## 🛠️ Code Quality

The codebase of `ft_irc` shines in multiple areas, ensuring robustness, maintainability, and scalability:

- **📂 Modularity**: The project structure clearly separates responsibilities into modules such as `IRCClient`, `IRCChannel`, and `IRCCore`, making the code easy to extend and maintain.
- **🧩 Best Programming Practices**: An object-oriented approach is employed, leveraging the capabilities of C++98 without sacrificing performance or code simplicity.
- **📜 Clarity**: The code is well-documented and structured so that each functionality is clearly defined and located in specific files, such as IRC commands implemented in the `commands` folder.
- **🔄 Non-Blocking I/O**: By using `poll()` or equivalents, `ft_irc` manages all network connections in a non-blocking manner, which optimizes resource usage and ensures high availability.
- **💡 Effective Error Handling**: Every potential error in networking and data handling is accounted for, ensuring the server never crashes unexpectedly.
- **🔒 Secure Socket Usage**: All client-server communication is handled securely and efficiently using sockets.

---

## 🧑‍💻 Usage

To run the server, compile the project with the provided Makefile and run the server with the following command:

```bash
./ircserv <port> <password>
```

- `<port>`: The port where the server will listen for incoming connections.
- `<password>`: The password required for clients to connect to the server.

Example:

```bash
./ircserv 6667 mySecretPassword
```

---

## 📋 Supported IRC Commands

The server supports the following essential IRC commands:

- **`KICK`**: Remove a client from the channel.
- **`INVITE`**: Invite a user to a channel.
- **`TOPIC`**: Change or view the channel’s topic.
- **`MODE`**: Manage channel modes (e.g., invite-only, password-protection, user limits).
- **`NICK`**: Change a user’s nickname.
- **`JOIN`**: Join a channel.
- **`QUIT`**: Disconnect from the server.
- **`PRIVMSG`**: Send private messages between users.
- **`PASS`**: Set a password for client connection.
- **`USER`**: Set the username for the client.
- **`PART`**: Leave a channel.
- **`PING`**: Check the connection status between server and client.
- **`WHOIS`**: Query information about a specific user.
- **`LIST`**: List all available channels.

---

## 📁 Project Structure

The project is organized into several directories and files, each serving a specific purpose:

```
ft_irc/
│
├── incs/               # Header files for class declarations
│   ├── IRCClient.hpp
│   ├── IRCChannel.hpp
│   ├── IRCCore.hpp
│   └── IRCSocket.hpp
│
├── srcs/               # Source files containing the core logic
│   ├── commands/       # Implementation of IRC commands
│   │   ├── kick.cpp
│   │   ├── invite.cpp
│   │   ├── topic.cpp
│   │   ├── ...
│   ├── IRCClient.cpp   # Client handling logic
│   ├── IRCChannel.cpp  # Channel management logic
│   ├── IRCCore.cpp     # Core server operations
│   ├── IRCSocket.cpp   # Socket handling logic
│   └── main.cpp        # Main entry point for the server
│
├── Makefile            # Build instructions
└── README.md           # Project documentation
```

Each component of the project is modularized for clarity and maintainability. The `commands` folder contains individual files for each supported IRC command, while the `IRCCore` handles the server's main operations.

---

## 🔍 Technical Highlights

### 1. **IPv6 Support**
The `IRCSocket` class supports both IPv4 and IPv6 by default, ensuring compatibility with modern network infrastructures and future-proofing the server.

### 2. **Efficient Resource Management**
The destructor of `IRCSocket` properly closes all open file descriptors, preventing resource leaks and ensuring long-term stability in high-uptime environments.

### 3. **Non-Blocking I/O with `poll()`**
The use of `poll()` for handling multiple clients simultaneously allows for efficient, non-blocking operations, ensuring the server remains responsive under heavy loads.

### 4. **Error Handling with Centralized Logging**
The class includes centralized logging for detailed error reporting, making debugging and monitoring easier in both development and production environments.

### 5. **Socket Reuse (`SO_REUSEADDR`)**
By enabling `SO_REUSEADDR`, the server can quickly restart and reuse ports, improving its resilience and flexibility in scenarios requiring rapid reboots.

---

## 🛡️ Robustness and Scalability

This server is not just functional but also designed for robustness and scalability. Key features that enhance its reliability include:

- **Resource Efficiency**: Thanks to the use of `poll()` for all I/O operations, resource consumption is minimized.
- **Crash-Proof**: The server is designed to never crash, even in extreme cases like memory exhaustion.
- **Cross-Platform Compatibility**: The code is adapted to run on different operating systems, ensuring file descriptors are handled correctly across platforms.

---

## 🌟 Bonus Features

In addition to the mandatory features, the project includes the following optional enhancements for an improved user experience:

- **🤖 Automated Bot**: Support for bots that can execute automated tasks within channels.
- **📁 File Transfer**: Allows users to transfer files directly through the server.

---

## 🔧 Testing

To test the server, you can use any standard IRC client or perform simple tests using `nc` (netcat):

```bash
nc 127.0.0.1 6667
```

Send test commands and ensure the server handles all operations appropriately.

---

## 🏅 Conclusion

`ft_irc` is more than just an IRC server. It’s a prime example of how to leverage C++98 features to create an efficient, modular, and scalable system, following strict code quality standards. Additionally, it’s designed with future extensibility and long-term maintenance in mind, making it a robust and reliable solution for real-time communication management.
