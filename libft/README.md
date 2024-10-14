
# 📚 Libft - Your First C Library

**Libft** is a comprehensive library of essential C functions, reimplemented from scratch, that mimics the behavior of standard library functions. This project not only provides standard functions but also includes optimizations that enhance memory management, string manipulation, and linked list operations. 🚀

---

## 🎯 Project Overview

The **Libft** project re-creates common C library functions from the ground up, offering more control over memory, safety, and performance. Notably, several functions have been optimized to prevent common errors such as memory overflows and ensure better performance in real-world applications.

---

## 🚀 Key Features

- **Standard C Functions with Enhancements**: Reimplementations of common functions like `strlen`, `strjoin`, `memcpy`, and `atoi`, with a focus on memory safety and efficiency.
- **Custom Memory Management**: Functions like `ft_calloc` optimize memory allocation and initialization, ensuring error-free memory handling.
- **Linked List Operations**: Implementations like `lstnew` and `lstadd_back` simplify the handling of dynamic data structures, with clear and efficient logic.
- **Optimized String Handling**: Functions such as `ft_strjoin` prevent memory overflows and ensure safe string concatenation.

---

## 📋 Usage

To compile and use the **Libft** library:

1. **Compile the library**:
   ```bash
   make
   ```

2. **Link the library in your projects**:
   ```c
   #include "libft.h"
   ```

3. **Example Usage**:
   ```c
   char *joined_str = ft_strjoin("Hello, ", "World!");
   ft_putstr_fd(joined_str, 1);
   free(joined_str);
   ```

This will print: `Hello, World!`

---

## 📂 Project Structure

```
libft/
│
├── Makefile                 # Build instructions
├── includes/                # Header files for function declarations
├── srcs/                    # Source code for all implemented functions
│   ├── ft_strlen.c          # Implementation of strlen
│   ├── ft_strjoin.c         # Implementation of strjoin
│   ├── ft_lstadd_back.c     # Linked list function to add nodes at the end
│   └── [other functions].c  # Additional C standard library functions
```

---

## 🛠️ Code Highlights

### 1. **Secure String Handling**:
   - Functions like `ft_strjoin()` ensure that memory is managed safely, preventing buffer overflows by using secure string functions like `ft_strlcpy` and `ft_strlcat`. This ensures safe concatenation and correct memory allocation.

### 2. **Memory Initialization with ft_calloc**:
   - The `ft_calloc()` function not only allocates memory but also initializes it to zero in one step, preventing potential errors caused by uninitialized memory.

### 3. **Linked List Operations**:
   - Functions like `ft_lstadd_back()` are designed to work efficiently with dynamic data structures. They provide simple and reliable management of linked lists, making them highly reusable.

### 4. **Memory Safe ft_memcpy**:
   - `ft_memcpy()` ensures correct memory copying, even when source and destination memory regions overlap. This prevents undefined behavior in critical memory operations.

---

## 🏅 Conclusion

**Libft** is more than just a reimplementation of the C standard library—it provides optimized and safer versions of commonly used functions. By focusing on memory safety and efficiency, this library is an essential tool for any C project, ensuring reliable and performant code.
