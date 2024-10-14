
# 🎮 So Long - 2D Game Adventure

Welcome to **So Long**, a 2D adventure game where the player must collect objects and navigate through a series of obstacles to reach the exit. The game is designed to give you experience working with graphical libraries, sprites, textures, and basic gameplay mechanics. 🚀

---

## 🎯 Project Overview

In **So Long**, the player must collect all the objects present in the map and find the shortest route to the exit while avoiding obstacles. The game runs in a 2D environment and is developed using **MiniLibX**, a simple graphics library that allows you to open windows, manage textures, and capture user input (keyboard and mouse events).

---

## 🚀 Key Features

- **🕹️ Basic Gameplay**: Move your character using `W`, `A`, `S`, `D` keys or arrow keys to collect objects and reach the exit. 
- **🎯 Goal**: The objective is to gather all the collectables and reach the exit while avoiding obstacles and walls.
- **🎨 Sprite Management**: The game includes custom sprites and textures for the player, enemies, and various other game elements.
- **🖼️ 2D View**: The game uses a 2D perspective (top-down view).
- **🖱️ Interactive Window**: The player can interact with the game window—resize, minimize, or close it using the ESC key or red close button.
- **📜 Real-time Move Counter**: The number of movements made by the player is displayed in the terminal after each move.

---

## 🧑‍💻 Usage

To run the game, compile the project using the **Makefile** and pass a valid map file as an argument:

```bash
# Build the project
make

# Run the game with a valid .ber map file
./so_long maps/level1.ber
```

---

## 🎮 Game Controls

- **W / UP Arrow**: Move up
- **A / LEFT Arrow**: Move left
- **S / DOWN Arrow**: Move down
- **D / RIGHT Arrow**: Move right
- **ESC**: Exit the game

---

## 📋 Game Elements

The following elements are part of the game:

- **Player**: Controlled by the user to navigate the map.
- **Collectables**: Objects that the player must gather to unlock the exit.
- **Obstacles**: Walls and other barriers that prevent the player from moving in certain directions.
- **Exit**: The final destination of the player after collecting all objects.

---

## 📂 Noteworthy Code Highlights

1. **Modular Design**: The code is well-organized into modules for game logic, graphics, and map processing, making it easy to maintain and extend.
   
2. **Flexible Sprite Management**: Sprites are dynamically loaded from external files. This allows for easy customization and expansion by simply modifying sprite lists in text files, without needing to modify the code itself.

3. **Efficient Memory Handling**: The game ensures proper memory management by freeing all dynamically allocated resources, avoiding memory leaks—a key aspect for long-running games.

4. **MiniLibX Integration**: The game utilizes **MiniLibX** for handling windowing, graphics, and event management, providing a lightweight and efficient approach to 2D game development.

---

## 📁 Project Structure

The project follows a well-organized directory structure:

```
so_long/
│
├── Makefile                 # Build instructions
├── srcs/                    # Source code for the game logic
│   ├── main.c
│   └── ...
├── maps/                    # Sample map files (.ber format)
├── imgs/                    # Game images and sprites
│   ├── performer.png
│   ├── enemy.png
│   ├── ...
└── includes/                # Header files
```

---

## 🏅 Conclusion

**So Long** provides a solid foundation for understanding graphical game development in **C**. Its modular design, flexible sprite management, and memory-efficient coding make it an engaging and expandable project for anyone looking to explore game programming.
