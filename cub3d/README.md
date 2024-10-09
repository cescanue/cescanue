
# cub3D Project

Welcome to **cub3D**, a collaborative project created by `jesuserr` and myself. This project is a 3D graphical application using raycasting, inspired by the classic Wolfenstein 3D game. The goal is to simulate a first-person view in a 2D map, creating an immersive experience using C programming and the MiniLibX library.

## 📜 Project Description

The project is structured to render 3D graphics based on a 2D map layout. It involves parsing configuration files, loading textures, and using raycasting techniques to create a first-person shooter-like environment. The version includes both "mandatory" features and "bonus" enhancements for an enriched experience.

### ✨ Key Features

1. **🏰 Advanced Raycasting Engine**
   - Implements a raycasting algorithm to simulate a 3D perspective on a 2D map.
   - Calculates the distance between the player and walls to adjust the wall height rendering accordingly.
   - Handles fisheye distortion correction for a realistic visual effect.

2. **🗺️ Map Parsing and Validation**
   - Reads configuration files (`.cub` maps) that define wall textures, floor, and ceiling colors, as well as the layout.
   - Supports various map configurations, including textures for the north, south, east, and west walls.
   - Ensures proper map validation, including closed boundaries and correct placement of starting positions.

3. **🕹️ Player Interaction and Movement**
   - Keyboard and mouse input handling for player movements (walking forward/backward, strafing, and rotating the view).
   - Dynamic updates to the player's view based on the mouse movements for a more immersive experience.
   - Collision detection to prevent walking through walls.

4. **🎨 Textures and Graphics**
   - Loads and applies textures to the walls for a realistic visual appearance.
   - Supports different wall textures, and adjusts their rendering based on the player's perspective.
   - The floor and ceiling colors are customizable via the map configuration files.

5. **🚪 Bonus Features**
   - Additional elements like doors, sprites, and animated objects that enhance the interactivity of the game.
   - Implementation of more complex map features, such as dynamic lighting and shading.
   - A maze generator that can automatically create random labyrinths for the player to explore.

6. **🧱 Modular Code Design**
   - Uses a modular approach, organizing the code into different sections for map handling, rendering, input processing, and utilities.
   - The `libft` library provides various helper functions, enhancing code readability and reusability.
   - Separate files for the mandatory and bonus features to maintain clear organization.

## 🚀 Running the Project

### Prerequisites
- **MiniLibX**: Ensure that the MiniLibX library is correctly installed on your system.
- **Make**: Required for compiling the project.

### Compiling and Running
To compile the project, navigate to the root directory and run:
```bash
make
```

For the bonus features, use:
```bash
make bonus
```

To clean up compiled files:
```bash
make clean
```

To run the program, provide a valid `.cub` file:
```bash
./cub3D maps/example.cub
```

## 📁 Project Structure

```
cub3d/
├── srcs/                    # Source files for mandatory features
├── srcs_bonus/              # Source files for bonus features
├── maps/                    # Example map files
├── libft/                   # Custom C library for utility functions
├── includes/                # Header files
├── mlx/                     # MiniLibX library files
└── Makefile                 # Makefile for building the project
```

## 🛠️ Requirements

- **Operating System**: macOS or Linux (MiniLibX support required).
- **C Compiler**: Compatible with C99 or higher.
- **Make**: Necessary for compiling the project.

## 🌟 Collaborative Effort

This project was developed in collaboration with `jesuserr`, showcasing our combined skills in C programming, graphics rendering, and game development. Together, we implemented an efficient raycasting engine, handled map parsing intricately, and introduced bonus features to enhance the gameplay.

## 🎮 Demo

To see the project in action, use one of the provided `.cub` files or create your own maps. Enjoy the retro-styled 3D experience!
