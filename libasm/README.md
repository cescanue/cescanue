
# 🛠 libasm

Welcome to **libasm**, a project focused on writing low-level implementations of standard library functions in x86-64 assembly. This project dives deep into the intricacies of system calls and assembly language programming, providing a practical learning experience. 🚀

## 📜 Project Overview

**libasm** re-implements common C library functions in assembly language (`.s` files). These functions follow the x86-64 Intel syntax and are compiled using NASM. The project includes a test suite (`main.c`) to demonstrate the correctness of each function.

### Key Features

- **🔧 Functionality Rewritten in Assembly**:
  - **`ft_strlen`**: Computes the length of a string.
  - **`ft_strcpy`**: Copies a string to a destination buffer.
  - **`ft_strcmp`**: Compares two strings lexicographically.
  - **`ft_write`**: Writes data to a file descriptor.
  - **`ft_read`**: Reads data from a file descriptor.
  - **`ft_strdup`**: Duplicates a string using dynamic memory allocation.

- **📂 Clean and Modular Design**:
  - Each function is implemented in its own `.s` file for maintainability and clarity.

- **💡 System Call Integration**:
  - `ft_write` and `ft_read` directly interact with the system using Linux system calls, properly handling `errno`.

- **🔒 Error Handling**:
  - Implements robust error checking for system calls, ensuring the behavior matches the original C library.

- **🛠 Test Suite**:
  - A comprehensive `main.c` program tests all the implemented functions, providing immediate feedback.

## 📁 Project Structure

```
libasm/
├── ft_strlen.s           # Implementation of strlen
├── ft_strcpy.s           # Implementation of strcpy
├── ft_strcmp.s           # Implementation of strcmp
├── ft_write.s            # Implementation of write
├── ft_read.s             # Implementation of read
├── ft_strdup.s           # Implementation of strdup
├── main.c                # Test program for all functions
├── Makefile              # Build system for creating libasm.a
```

## 🌟 Implementation Highlights

### 1. **Assembly Language Mastery**
All functions are implemented using x86-64 assembly with Intel syntax, compiled via NASM. The project adheres to the 64-bit calling convention and ensures proper stack alignment.

### 2. **System Call Wrapping**
- **`ft_write`** and **`ft_read`** wrap Linux system calls, managing buffers and error states.
- Properly sets `errno` using `extern ___error` or equivalent mechanisms.

### 3. **Dynamic Memory Allocation**
- **`ft_strdup`** utilizes `malloc` to allocate memory dynamically, mimicking the behavior of the standard function.

### 4. **Error Handling**
Ensures all functions gracefully handle edge cases, such as null pointers or invalid file descriptors.

## 🖥️ Usage

### Compilation
Compile the library with the provided `Makefile`:
```bash
make
```

### Linking
Link the library in your project:
```bash
gcc -L. -lasm -o test main.c
```

### Example
```c
#include <stdio.h>

size_t  ft_strlen(const char *s);
char    *ft_strcpy(char *dst, const char *src);
int     ft_strcmp(const char *s1, const char *s2);

int main() {
    const char *str = "Hello, libasm!";
    printf("Length: %zu\n", ft_strlen(str));
    char buffer[20];
    ft_strcpy(buffer, str);
    printf("Copied String: %s\n", buffer);
    printf("Comparison: %d\n", ft_strcmp("abc", "abc"));
    return 0;
}
```

## 🌟 Technical Analysis

1. **Code Quality**:
   - Clean, modular `.s` files, each focusing on a single function.
   - Follows best practices for assembly programming, ensuring maintainability.

2. **Performance**:
   - Optimized implementations leveraging the power of assembly for string manipulation and system interaction.

3. **Error Robustness**:
   - Matches the behavior of libc functions, including error states.

4. **Learning-Oriented**:
   - Serves as an excellent introduction to assembly language, x86-64 architecture, and system call integration.

## 🌐 Contributions

Contributions are welcome! If you have suggestions or improvements, feel free to fork the repository and submit a pull request. Happy hacking! 🚀

