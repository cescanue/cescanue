
# 🧠 Philosophers - Process Synchronization and Mutex

Welcome to **Philosophers**, a project that explores the fundamental concepts of multithreading, process synchronization, and mutexes in C. This project simulates a group of philosophers sitting at a table, each philosopher alternating between thinking, eating, and sleeping. The goal is to prevent them from starving by managing shared resources (forks) while avoiding data races. 🚀

---

## 🎯 Project Overview

The **Philosophers** project simulates the well-known "Dining Philosophers Problem," where several philosophers share forks to eat spaghetti. Each philosopher needs two forks to eat, but there are fewer forks than philosophers, requiring careful synchronization to prevent deadlocks and starvation.

---

## 🚀 Key Features

- **Thread-based Simulation**: Each philosopher is represented as a separate thread, with their own lifecycle of thinking, eating, and sleeping.
- **Mutex Protection**: Forks are protected by mutexes to ensure that only one philosopher can hold a fork at a time.
- **Philosopher Death Simulation**: The program monitors philosophers’ eating times, and if a philosopher doesn’t eat in the defined time, they will "die."
- **Real-Time Event Logging**: The program logs important events (taking a fork, eating, thinking, sleeping) with precise timestamps.

---

## 📋 Simulation Flow

- Philosophers alternate between three states: **eating**, **thinking**, and **sleeping**.
- A philosopher can only eat when they have acquired both their left and right forks (mutexes).
- Once finished eating, the philosopher releases both forks and starts sleeping.
- If a philosopher doesn't eat within a specified amount of time (`time_to_die`), the simulation stops, and the philosopher is marked as "dead."

---

## 🛠️ Code Structure and Synchronization

### 1. **Multithreading with Mutexes**:
   - The program uses **pthreads** to create separate threads for each philosopher. Each philosopher operates independently, but shares the forks with their neighbors, making the mutexes critical to ensure that no two philosophers hold the same fork simultaneously.
   
   - **Philosopher Life Cycle**: The function `philo_main1()` controls the life cycle of each philosopher, checking whether they are still alive, managing their eating times, and printing their actions in real time.
   
   - **Critical Sections**: Forks are protected by mutexes to ensure that only one philosopher can access them at a time. Each philosopher tries to lock both forks (left and right) before they can eat.

### 2. **Philosopher Death Handling**:
   - The program constantly monitors each philosopher's time since their last meal. If the time exceeds the `time_to_die` threshold, the philosopher is considered dead, and the simulation stops immediately.
   
   - **Efficient Time Management**: The function `get_time_ms()` retrieves the current time in milliseconds to ensure that all actions and state changes are logged with accurate timestamps.

### 3. **Efficient Resource Management**:
   - The use of mutexes and the careful control of when a philosopher takes or releases a fork ensures that the simulation avoids deadlocks and race conditions, making the code robust and efficient for concurrent execution.

---

## 🧑‍💻 Usage

To compile and run the program, use the following commands:

```bash
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

This command simulates five philosophers with 800ms as the time to die, 200ms to eat, and 200ms to sleep.

---

## 📂 Project Structure

```
philosophers/
│
├── Makefile                # Build instructions
├── includes/               # Header files for the project
├── srcs/                   # Source code for the main and bonus parts
│   ├── philo/              # Main part source code
│   └── philo_bonus/        # Bonus part with processes and semaphores
└── philosophers_visualizer # Visual tool to debug and visualize philosopher actions
```

---

## 🔍 Key Code Highlights

1. **Thread Management and Synchronization**: The use of pthreads for each philosopher ensures that the simulation runs concurrently, with efficient use of mutexes to handle the forks and prevent race conditions.
   
2. **Accurate Timing with Millisecond Precision**: The program logs every event (eating, sleeping, thinking) with precise timestamps using `get_time_ms()` for accurate simulation results.

3. **Death Handling and Simulation Control**: The simulation automatically ends when a philosopher "dies" due to starvation, ensuring real-time control and monitoring of the philosopher's states.

---

## 🏅 Conclusion

The **Philosophers** project demonstrates efficient use of multithreading and synchronization mechanisms (mutexes) to solve a classic concurrency problem. With careful control of shared resources and accurate time management, the program simulates the philosophers' life cycles while avoiding deadlocks and ensuring correct operation in a concurrent environment.
