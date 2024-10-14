
# 📜 Get Next Line - Optimized Multi-File Line Reader

**Get Next Line** is an optimized implementation of the line-by-line file reading function, with special attention to memory management, buffer handling, and multi-file reading. This project showcases efficient handling of static variables and dynamic memory allocation to ensure the function can read lines sequentially from multiple file descriptors without re-reading unnecessary data. 🚀

---

## 🎯 Project Overview

**Get Next Line** reads from a file descriptor, returning one line at a time. What makes this implementation special is its ability to handle multiple open files simultaneously, maintain efficient memory management, and correctly process lines that span multiple buffer reads. The function is designed to work with any buffer size, making it adaptable for various file reading tasks.

---

## 🚀 Key Features

- **Multi-File Descriptor Support**: Capable of handling multiple open file descriptors, allowing simultaneous line-by-line reading from several files.
- **Efficient Line Fragment Handling**: Correctly handles cases where lines are fragmented across multiple reads, ensuring no loss or duplication of data.
- **Memory-Safe Design**: Manages memory dynamically and ensures proper cleanup after each read, avoiding memory leaks.
- **Static Variable Usage**: Uses static variables to maintain the state of the buffer between function calls, allowing for continuous reading without re-reading the same data.

---

## 📋 Usage

To compile and use the **Get Next Line** function:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c -o gnl
```

Run the function with a file:

```bash
./gnl <file_name>
```

This will print each line from the file sequentially.

---

## 📂 Project Structure

```
get_next_line/
│
├── get_next_line.c          # Core logic for reading from file descriptor
├── get_next_line_utils.c    # Utility functions for memory and string management
├── get_next_line.h          # Header file with function prototypes and macros
└── Makefile                 # Build instructions
```

---

## 🛠️ Code Highlights

### 1. **Multi-File Support**:
   - Unlike standard implementations, this version of **get_next_line** can read from multiple file descriptors simultaneously. Each file descriptor has its own buffer, ensuring that the function can track the progress of multiple files independently.

### 2. **Line Fragmentation Handling**:
   - The function efficiently handles lines that are fragmented across multiple buffer reads. It ensures that partial lines are stored and concatenated until the full line is retrieved.

### 3. **Dynamic Memory Allocation**:
   - The function dynamically allocates and frees memory as needed, ensuring that there are no memory leaks and that buffer space is used efficiently.

---

## 🏅 Conclusion

**Get Next Line** is an optimized version of the line reading function, designed to handle multiple file descriptors and large files efficiently. Its memory-safe design and ability to handle fragmented lines make it a robust solution for various file reading tasks in C.
