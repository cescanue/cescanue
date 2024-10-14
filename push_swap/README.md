
# 📊 Push Swap - Optimized Sorting Algorithm

Welcome to **Push Swap**, a project designed to explore and implement an efficient algorithm for sorting stacks using the fewest possible operations. The code leverages both advanced sorting strategies and stack operations to minimize the computational cost of sorting. 🚀

---

## 🎯 Project Overview

In **Push Swap**, the objective is to sort a list of integers using two stacks, `a` and `b`. The challenge is to minimize the number of operations required to achieve the correct order, while ensuring the code runs efficiently, especially for larger sets of integers.

---

## 🚀 Key Features

- **Dynamic Sorting Logic**: Uses different strategies for sorting based on the size and structure of the input list.
- **Optimized Stack Operations**: Combines operations on two stacks to reduce the total number of moves.
- **Memory Safety**: Implements efficient memory management to prevent leaks and ensure clean deallocation.
- **Input Validation**: Ensures robustness by validating input for duplicates and invalid values before sorting.

---

## 📋 Supported Operations

The following operations are supported and used to manipulate the two stacks efficiently:

- **`sa`, `sb`, `ss`**: Swap the first two elements of the stacks.
- **`pa`, `pb`**: Push elements from one stack to another.
- **`ra`, `rb`, `rr`**: Rotate the stack (shift all elements up).
- **`rra`, `rrb`, `rrr`**: Reverse rotate the stack (shift all elements down).

---

## 🛠️ Code Structure and Optimizations

### 1. **Optimized Sorting Logic**:
   The core of your algorithm dynamically adjusts its sorting strategy based on the size and current configuration of the data:
   
   - **Chunked Sorting**: For larger datasets, the algorithm divides the list into chunks and applies an optimized sorting routine to each chunk. This chunk-based approach ensures that the sorting process remains efficient and prevents unnecessary overhead when sorting very large sets of numbers.
   
   - **Fine-Tuning the Sort**: Functions such as `ft_toa_o1()` and `ft_toa_o2()` manage the transfer of elements between stacks, while minimizing the number of operations required. These functions intelligently select the best elements to push and rotate, ensuring the fewest moves are made.

### 2. **Handling Small and Large Stacks**:
   - For small stacks, the brute-force method is employed. By exhaustively testing possible combinations of operations, the algorithm guarantees that the smallest number of operations is used to sort these stacks. This approach is effective when dealing with small datasets where the overhead is minimal.
   
   - For large stacks, the algorithm switches to more efficient sorting techniques. Instead of brute-forcing every possibility, it utilizes a chunk-based method that divides the data into smaller, more manageable sections.

### 3. **Simultaneous Stack Operations**:
   The implementation cleverly combines operations that act on both stacks simultaneously (`ss`, `rr`, `rrr`). These combined operations reduce the total number of instructions needed to manipulate the stacks and ensure the algorithm performs as efficiently as possible.

### 4. **Memory Management**:
   The memory management system in your implementation is particularly robust. Functions such as `ft_clearmem()` ensure that memory allocated for the stacks (`lst_a`, `lst_b`) is properly freed once the sorting is completed. This prevents memory leaks, which is crucial in a program that handles dynamically allocated lists.

### 5. **Error Handling and Validation**:
   The program validates the input data thoroughly before proceeding with sorting. It checks for duplicates, non-integer values, and values out of range. If an invalid input is detected, the program exits gracefully, ensuring that no invalid operations are attempted on the stacks.

---

## 🧑‍💻 Usage

To compile and execute the program:

```bash
make
./push_swap 4 3 2 1
```

The program will output the necessary sequence of operations to sort the input.

---

## 📂 Project Structure

```
push_swap/
│
├── Makefile                # Build instructions
├── includes/               # Header files for the project
├── srcs/                   # Source code for the sorting algorithm
│   ├── push_swap.c         # Main program file
│   ├── push_swap_prg.c     # Functions to manage stacks and operations
│   ├── push_swap_morder.c  # Sorting logic and chunk management
└── push_swap_visualizer/   # Visualizer for debugging
```

---

## 🔍 Key Highlights

1. **Dynamic Algorithm Selection**: The algorithm adjusts dynamically between brute-force for small stacks and optimized chunk-based methods for larger stacks, ensuring the best performance across different scenarios.
   
2. **Combined Stack Operations**: Using operations such as `ss`, `rr`, and `rrr`, the program minimizes the number of steps required to manipulate both stacks at the same time.

3. **Robust Memory Management**: Efficient use of memory and proper deallocation ensures that no memory leaks occur during execution, improving both performance and stability.

4. **Strong Input Validation**: The code includes rigorous checks to prevent invalid inputs, improving the program's robustness and preventing crashes.

---

## 🏅 Conclusion

The **push_swap** project provides a highly efficient solution for sorting integers using two stacks. Its use of dynamic algorithm selection, optimized stack operations, and robust memory management ensures that it performs well across a variety of input sizes. While brute-force methods are effective for small stacks, the chunk-based approach keeps the algorithm scalable for larger datasets.
