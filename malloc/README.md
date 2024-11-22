
# 🧵 libft_malloc

Welcome to **libft_malloc**, a custom dynamic memory allocation library. This project implements `malloc`, `free`, and `realloc` functions, mimicking the behavior of the standard C library while allowing fine-grained control over memory management. 🚀

## 📜 Project Overview

**libft_malloc** provides a robust and efficient mechanism for dynamic memory allocation using low-level system calls like `mmap` and `munmap`. The project also includes advanced features like memory zone management, block alignment, and thread safety through mutexes.

### Key Features

- **🔧 Dynamic Memory Management**:
  - **`malloc(size_t size)`**: Allocates a block of memory of the specified size.
  - **`free(void *ptr)`**: Deallocates the memory previously allocated by `malloc` or `realloc`.
  - **`realloc(void *ptr, size_t size)`**: Resizes the memory block pointed to by `ptr`.

- **📂 Memory Zone Segmentation**:
  - **TINY**: Handles allocations of up to 1024 bytes.
  - **SMALL**: Handles allocations between 1025 and 15360 bytes.
  - **LARGE**: Handles allocations above 15360 bytes in separate memory zones.

- **🖥 Memory Debugging**:
  - **`show_alloc_mem()`**: Displays the current state of allocated memory in TINY, SMALL, and LARGE zones.
  - **`show_alloc_mem_hex()`**: Provides a hex dump of allocated memory zones.

- **🔒 Thread Safety**:
  - Uses `pthread_mutex` for synchronized access to shared data structures.

- **⚙️ Block Alignment**:
  - Ensures all allocations are aligned to 16 bytes for performance optimization.

## 📁 Project Structure

```
libft_malloc/
├── malloc.c               # Core implementation of malloc, free, and realloc
├── malloc.h               # Header file with definitions and structures
├── Makefile               # Build system for compiling the shared library
├── libft/                 # Custom utility functions library
```

## 🌟 Implementation Highlights

### 1. **Zone Management**
Memory is pre-allocated in chunks (zones) to minimize system calls (`mmap` and `munmap`) and improve performance. Each zone contains blocks managed by linked lists:

- **TINY and SMALL Zones**: Pre-allocated zones store multiple blocks, reducing overhead from frequent system calls.
- **LARGE Allocations**: Directly mapped to individual memory areas for flexibility.

### 2. **Thread Safety**
Global variables (`g_zone`, `g_mutex`) ensure consistency in a multi-threaded environment. Mutex locks protect critical sections, ensuring safe access to shared data structures.

### 3. **Memory Alignment**
Blocks are aligned to 16 bytes using the `ALIGN` macro, ensuring efficient memory access and compatibility with hardware requirements.

### 4. **Debugging Tools**
- **`show_alloc_mem()`**:
  Displays allocated memory blocks in ascending order of addresses:
  ```
  TINY : 0xA0000
  0xA0020 - 0xA004A : 42 bytes
  SMALL : 0xAD000
  LARGE : 0xB0000
  Total : 52698 bytes
  ```

- **`show_alloc_mem_hex()`**:
  Provides a hexadecimal representation of allocated blocks for advanced debugging.

## 🖥️ Usage

### Compilation
Compile the library with the provided `Makefile`:
```bash
make
```

### Linking
Link the library in your project:
```bash
gcc -L. -lft_malloc -o my_program my_program.c
```

### Example
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *ptr = malloc(100);
    snprintf(ptr, 100, "Hello, libft_malloc!");
    printf("%s\n", ptr);
    free(ptr);
    return 0;
}
```

## 🖥️ Requirements

- **Operating System**: Linux or macOS.
- **Compiler**: `gcc` with support for C99.
- **Permissions**: Requires a compatible environment for `mmap` and `pthread` usage.

## 🌟 Technical Analysis

The project achieves a balance between performance and flexibility:

1. **Code Quality**:
   - Modular implementation separates responsibilities across files.
   - Well-commented code improves maintainability and readability.

2. **Efficiency**:
   - Minimizes system calls by pre-allocating memory zones.
   - Aligns memory for improved performance.

3. **Robustness**:
   - Ensures thread safety with mutex locks.
   - Handles invalid pointers and edge cases gracefully.

4. **Extensibility**:
   - Supports additional debugging tools like `show_alloc_mem_hex()`.
   - Easily adjustable zone sizes and alignment.

## 🌐 Contributions

Contributions are welcome! If you have ideas to improve the library or add features, feel free to fork the repository and submit a pull request. Collaboration makes us stronger! 🚀

