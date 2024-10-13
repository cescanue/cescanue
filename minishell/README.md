
# 🌟 **Minishell**: Your Custom Shell Implementation 🚀

![Shell](https://img.shields.io/badge/Shell-C-blue.svg) ![Contributions](https://img.shields.io/badge/Contributions-Welcome-green.svg)

## Table of Contents
1. [✨ Overview](#-overview)
2. [⚙️ Key Features](#-key-features)
3. [📦 Installation](#-installation)
4. [💻 Usage](#-usage)
5. [🔧 Built-in Commands](#-built-in-commands)
6. [🧩 Project Structure](#-project-structure)
7. [🔍 How It Works](#-how-it-works)
8. [🛠️ Memory Management](#-memory-management)
9. [🚨 Error Handling](#-error-handling)
10. [🎉 Bonus Features](#-bonus-features)
11. [🤝 Contributors](#-contributors)

---

## ✨ Overview

**Minishell** is a minimalistic, yet powerful implementation of a Unix-like shell written in C. It mimics core features of the Bash shell while being educational and efficient, helping you understand how shells interact with the system at a low level. 

> ⚡ **Key Concepts**: Process creation, input/output redirection, signal handling, and command parsing.

---

## ⚙️ Key Features

- 🌈 **Command Execution**: Run any executable, using `$PATH` or absolute/relative paths.
- 📜 **History Management**: Navigate through your command history easily.
- 🔄 **Environment Variables**: Supports dynamic variable expansion (`$VAR`) and special variables like `$?`.
- 📡 **Pipes**: Chain commands with pipes (`|`) for powerful workflows.
- 🚨 **Signal Handling**: Responsive to signals like `ctrl-C` and `ctrl-D`.
- 📥 **Redirection**: Input and output redirection (`>`, `<`, `>>`, `<<`) fully supported.

---

## 📦 Installation

```bash
cd minishell
make
```

Run your shell:
```bash
./minishell
```

---

## 💻 Usage

Once in the shell, you can execute commands just like you would in Bash:

```bash
minishell$ ls -la
minishell$ cd /path/to/directory
minishell$ echo "Hello, World!"
```

### 🔗 Redirection and Pipes
- **Redirect input**: `command < file`
- **Redirect output**: `command > file` or `command >> file` (append mode)
- **Piping**: `command1 | command2 | command3`

### 🛑 Signal Handling
- **Ctrl-C**: Interrupt current command.
- **Ctrl-D**: Exit the shell.
- **Ctrl-\**: Ignored, as in Bash.

---

## 🔧 Built-in Commands

Minishell supports several built-in commands:

| Command     | Description                            |
|-------------|----------------------------------------|
| `echo`      | Prints text with optional `-n` flag    |
| `cd`        | Changes the current directory          |
| `pwd`       | Prints the working directory           |
| `export`    | Sets environment variables             |
| `unset`     | Unsets environment variables           |
| `env`       | Displays the environment               |
| `exit`      | Exits the shell                        |

---

## 🧩 Project Structure

```
.
├── includes/         # Header files
├── srcs/             # Source code
│   ├── minishell.c   # Main entry point
│   ├── builtins/     # Built-in command implementations
│   ├── parser/       # Command parsing logic
│   └── executor/     # Command execution logic
├── libft/            # Custom C library (if applicable)
├── Makefile          # Build instructions
└── README.md         # Documentation
```

---

## 🔍 How It Works

- **Command Parsing**: Input is tokenized and parsed to identify commands, arguments, redirection operators, and pipes.
- **Process Creation**: Commands are executed using `fork()` and `execve()`, allowing for both external and built-in commands to be run.
- **Redirection & Pipes**: Redirect input/output using file descriptors, and chain commands together with pipes to enable multi-stage workflows.
- **Environment Variable Expansion**: Expands variables like `$PATH`, and special variables like `$?` for command exit status.

---

## 🛠️ Memory Management

- **Dynamic Memory**: Memory is allocated using `ft_calloc` and freed appropriately to avoid leaks.
- **Error-safe Allocation**: If a memory allocation fails, Minishell gracefully exits with error messages, preventing segmentation faults or undefined behavior.

---

## 🚨 Error Handling

- **Descriptive Errors**: Minishell provides clear error messages for failed operations such as failed `dup` calls or incorrect command syntax.
- **Exit Status**: The `$?` variable stores the exit status of the last command, just like in Bash, allowing for more complex scripting.

---

## 🎉 Bonus Features

- **Logical Operators**: Supports `&&` and `||` to chain commands based on success or failure.
- **Wildcard Expansion**: Expands `*` in the current directory, allowing flexible file matching.

---

## 🤝 Contributors

- **[Jesuserr](https://github.com/jesuserr)**

Feel free to open issues and contribute to this project by submitting pull requests.

---
