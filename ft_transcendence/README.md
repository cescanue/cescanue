
# 🏓 ft_transcendence

Welcome to **ft_transcendence**, a fully-featured web-based Pong game platform that offers various game modes including local and remote multiplayer, AI matches, and different tournament formats. This project integrates real-time chat, user management, and advanced security features to deliver an engaging gaming experience. 🚀

## 📜 Project Description

The aim of **ft_transcendence** is to create a comprehensive gaming platform where players can:
- Compete in Pong across various game modes: local, remote, AI, and tournaments.
- Participate in different types of tournaments with flexible formats.
- Enjoy real-time communication and community features.
- Experience a modern, single-page web application for seamless interaction.

The project is built using a modular architecture that integrates several services managed via Docker.

## ✨ Key Features

- **🎮 Multiple Game Modes**:
  - **Local Multiplayer**: Play Pong with another player on the same network.
  - **Remote Multiplayer**: Compete against other players online in real-time.
  - **AI Matches**: Play against an AI opponent with configurable difficulty.
  - **Tournaments**: Supports various tournament types:
    - **Single and Double Elimination**: Players compete in knockout-style tournaments.
    - **Round-Robin**: Each player competes against every other player.
    - **Local and Remote Tournaments**: Participate in both local network and online tournaments.

- **💬 Real-Time Chat**:
  - **Public and Private Chat Rooms**: Engage in conversations with friends or the community.
  - **User Blocking and Message History**: Manage chat permissions and access past messages.

- **👤 User Management**:
  - **Custom Profiles**: Users can create profiles with avatars and keep track of game statistics.
  - **Friend Management**: Add friends, view their online status, and invite them to play.
  - **Secure Authentication**: Includes JWT-based authentication and two-factor authentication (2FA).

- **🔒 Security**:
  - **Data Protection Best Practices**: Includes input validation, HTTPS, and protection against common vulnerabilities.
  - **Two-Factor Authentication (2FA)**: Provides extra security for account access.

- **🔧 Modular Architecture with Docker**:
  - Uses Docker to manage services including Django, PostgreSQL, Redis, and Nginx.
  - Simplifies deployment and scaling.

## 🚀 Running the Project

### Prerequisites
- **Docker**: Make sure Docker is installed and running on your system.

### Starting the Project
Run the following command to set up and launch the project:
```bash
make all
```
This command will:
1. Create necessary directories for data storage.
2. Assign appropriate permissions.
3. Build and run the application using `docker-compose`.

### Additional Commands
- **Stop and remove services**:
  ```bash
  make down
  ```
- **Rebuild and restart services**:
  ```bash
  make re
  ```
- **Clean up Docker containers and data**:
  ```bash
  make clean
  ```

## 📁 Project Structure

```
ft_transcendence/
├── resources/                  # Project resources, including subject files
│   ├── subject/                # Subject files for project requirements
│   └── eval_sheet/             # Evaluation criteria for the project
├── requirements/               # Service configurations and application code
│   ├── postgresql/             # PostgreSQL database configuration
│   ├── redis/                  # Redis configuration for caching
│   ├── nginx/                  # Nginx configuration for web server
│   └── django/                 # Django configuration and application logic
│       ├── www/                # Main application modules and functionalities
│       │   ├── chat/           # Chat system for real-time communication
│       │   ├── tournament/     # Tournament logic and game management
│       │   ├── game/           # Game modes and logic for different types of Pong matches
│       │   ├── pongapi/        # API for user management and game data
│       │   ├── friends/        # Friend management system
│       │   └── stats/          # Statistics and game history tracking
│       └── conf/               # Django configuration files
├── Makefile                    # Makefile for building and running the project
├── docker-compose.yml          # Docker Compose configuration
└── .env                        # Environment variables for configuration
```

## 🖥️ Requirements

- **Operating System**: Windows, macOS, or Linux.
- **Docker**: Make sure Docker is installed.
- **Web Browser**: Google Chrome or Firefox is recommended for the best experience.

## 🌐 Contributions

Contributions are welcome! Please fork the repository, submit issues, and make pull requests to improve the project.
