
# 🔧 Pipex - Conceptual Test for Learning Pipes

This project, **Pipex**, was created solely as a conceptual test to learn and understand how UNIX pipes work. It was never meant to implement the full project but served as a stepping stone for the later development of **Minishell**. The code here explores basic process execution and pipe management to gain the necessary foundation for building more complex systems like shell environments. 🚀

---

## 🎯 Project Overview

**Pipex** was created as an experimental project to test the functionality of UNIX pipes. The focus was entirely on learning how processes can communicate via pipes, redirecting output from one command to another, and understanding basic command execution in a controlled environment.

---

## 🚀 Key Features

- **Basic Pipe Handling**: The program demonstrates the basic mechanism of piping between two processes.
- **Process Execution**: A conceptual test on how to run commands in separate processes and redirect input/output.
- **Learning Tool for Minishell**: The main purpose of this project was to experiment with pipes and prepare for building **Minishell**.

---

## 📋 Usage

To compile and run the conceptual test:

```bash
make
./pipex infile "command1" "command2" outfile
```

Example:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This simulates the shell behavior:

```bash
< infile ls -l | wc -l > outfile
```

---

## 📂 Project Structure

```
pipex/
│
├── Makefile                # Build instructions
├── includes/               # Header files
├── srcs/                   # Source code files
│   ├── pipex.c             # Main conceptual test logic
│   └── pipex_exec.c        # Process and command execution handling
├── obj/                    # Object files generated during compilation
├── ft_printf/              # Custom printf implementation
└── infile, outfile         # Example files used for testing
```

---

## 🛠️ Code Highlights

### 1. **Basic Use of UNIX Pipes**:
   - This project’s core focus was to understand how two commands can communicate via pipes using system calls like `exec()` and how to manage process input/output redirection.

### 2. **Learning for Minishell**:
   - The purpose of **Pipex** was strictly to gain hands-on experience with pipes. The insights gained from this conceptual test formed the basis for the future implementation of the **Minishell** project.

---

## 🏅 Conclusion

**Pipex** was created as a conceptual test, focusing on understanding pipes and process management in UNIX. While it is not a full implementation, it provided the knowledge required to tackle more complex projects, particularly **Minishell**.
