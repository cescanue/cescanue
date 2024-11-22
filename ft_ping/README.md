
# 🌐 ft_ping

Welcome to **ft_ping**, a detailed and custom-built implementation of the `ping` command. This project aims to replicate the functionality of standard `ping` while delving into the low-level details of networking, raw sockets, and ICMP protocols in C. A robust educational and functional tool for understanding network communication from the ground up. 🚀

## 📜 Project Overview

**ft_ping** allows users to test the accessibility of remote hosts over a network, simulating the behavior of the standard `ping` utility. Unlike traditional implementations, this project avoids using advanced system libraries or shortcuts, offering a complete hands-on learning experience with the ICMP protocol.

### Key Features

- **📦 Advanced Option Support**:
  - `-c <count>`: Limit the number of packets to send.
  - `-t <TTL>`: Set the packet's Time To Live value.
  - `-s <size>`: Specify the size of the data payload in bytes.
  - `-v`: Enable verbose output for detailed debugging.
  - `-f`: Enable "flood" mode for rapid packet sending.
  - `-p <pattern>`: Use a custom pattern for the packet payload.
  - `-n`: Numeric output only (no DNS resolution).
  - `-w <deadline>`: Set a maximum runtime in seconds.
  - `-W <timeout>`: Specify a timeout for each packet in seconds.

- **🖥 Comprehensive Packet Handling**:
  - Prepares ICMP headers with proper checksum calculations.
  - Handles sending and receiving packets via raw sockets.
  - Manages ICMP errors, including "Time to Live Exceeded."

- **📊 Detailed Statistics**:
  - Provides minimum, maximum, average, and standard deviation (mdev) for Round-Trip Time (RTT).
  - Tracks transmitted, received, and lost packets.
  - Detects specific ICMP errors and reports them.

- **🔧 Linux Compatibility**:
  - Implements advanced features like `IP_RECVERR` for error queue handling.
  - Supports options such as `SO_TIMESTAMP` and reception of TTL (`IP_RECVTTL`).

- **🔒 Robustness and Safety**:
  - Validates input arguments extensively.
  - Cleans up resources on exit, avoiding memory leaks or dangling sockets.

## 📁 Project Structure

```
ft_ping/
├── ft_ping_main.c       # Entry point and main loop
├── ft_ping_utils.c      # Utility functions like checksum and parsing
├── ft_ping_socket.c     # Raw socket creation and configuration
├── ft_ping_packet.c     # ICMP packet preparation and handling
├── ft_ping_signal.c     # Signal handling (SIGINT, SIGALRM)
├── ft_ping_display.c    # Output and statistics display
├── ft_ping_compat.c     # Advanced Linux compatibility
├── ft_ping.h            # Shared definitions and global structure
├── Makefile             # Compilation rules
```

### Code Highlights

#### 1. **Socket Management (`ft_ping_socket.c`)**  
Creates and configures a raw socket for ICMP communication. `set_socket_options` handles critical configurations like TTL, timeouts, and error queue settings (`IP_RECVERR`).

#### 2. **ICMP Packet Preparation (`ft_ping_packet.c`)**  
- `prepare_packet`: Constructs ICMP packets with headers and payload.
- `send_packet` and `receive_packet`: Manage packet transmission and reception, with detailed error handling.

#### 3. **Statistics and Output (`ft_ping_display.c`)**  
- `print_statistics`: Displays RTT statistics, including mdev.
- `print_reply`: Provides clear feedback on packet replies, including RTT and TTL.

#### 4. **Linux-Specific Features (`ft_ping_compat.c`)**  
Handles advanced configurations for Linux, such as receiving ICMP errors via `errqueue` for better debugging and diagnostics.

#### 5. **Signal Management (`ft_ping_signal.c`)**  
Cleans up resources and prints statistics upon receiving signals like `SIGINT`.

#### 6. **Option Parsing (`ft_ping_main.c`)**  
`parse_arguments` validates and sets options like packet size, TTL, and custom payload patterns.

## 🖥️ Requirements

- **Operating System**: Linux with kernel >= 3.14.
- **Permissions**: Requires `CAP_NET_RAW` or root access for raw socket usage.
- **Compiler**: `gcc` with C99 support.

## 🌟 Technical Analysis

The project excels in both functionality and educational value:

1. **Code Quality**:
   - Modular design separates responsibilities across files.
   - Well-documented functions and consistent coding style.

2. **Robustness**:
   - Handles edge cases like invalid packet sizes or unreachable hosts gracefully.
   - Prevents resource leaks through comprehensive cleanup routines.

3. **Performance**:
   - Accurate RTT calculations using microsecond precision.
   - Optimized memory usage with dynamic payload allocation.

4. **Extensibility**:
   - Designed to support additional flags and features without major restructuring.

5. **Learning-Oriented**:
   - Provides an in-depth understanding of ICMP, sockets, and low-level networking.

## 🚀 Usage Examples

### Basic Ping
```bash
sudo ./ft_ping google.com
```

### Customized Ping
```bash
sudo ./ft_ping -c 5 -t 128 -s 64 -v google.com
```

### Advanced Ping
```bash
sudo ./ft_ping -p ff -n -W 2 -f 192.168.1.1
```

## 🌐 Contributions

Contributions are welcome! If you have ideas for improving the project or adding features, feel free to fork the repository and submit a pull request. Collaboration is key! 🚀
