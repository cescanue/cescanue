
# 🌐 Inception - Dockerized Web Infrastructure

Welcome to **Inception**, a system administration project designed to give you hands-on experience with Docker and containerization. The goal of this project is to build a small infrastructure with Docker that simulates a real-world web server environment. 🚀

---

## 🎯 Project Overview

The **Inception** project challenges you to set up a fully Dockerized web infrastructure that includes an NGINX server, a WordPress website with a MariaDB database, and the appropriate networking setup, all running in separate Docker containers.

Each service (NGINX, WordPress, MariaDB) runs in its dedicated container, ensuring a modular and scalable architecture. The infrastructure is secured with TLS (Transport Layer Security) and allows data persistence via Docker volumes.

---

## 🚀 Key Features

- **🔐 TLS Secured NGINX Server**: The NGINX container serves as the entry point for all traffic, supporting only TLSv1.2 and TLSv1.3.
- **📡 WordPress + php-fpm**: A separate container is dedicated to running WordPress with PHP-FPM for optimized performance, independent of NGINX.
- **📦 MariaDB Database**: MariaDB runs in its own container, ensuring isolation and scalability for the database management system.
- **📂 Data Persistence**: Volumes are used to store the WordPress website data and the database files, ensuring that the data persists even if containers are stopped or removed.
- **🌐 Custom Domain**: The infrastructure is configured to use a custom domain that resolves to the local environment (e.g., `login.42.fr`).
- **⚙️ Full Docker Automation**: The project setup is fully automated with Docker Compose, enabling you to bring up the entire infrastructure with a single command.

---

## 🛠️ Code Quality

The architecture of the **Inception** project promotes scalability, modularity, and ease of management through containerization. Key aspects of the code include:

- **📂 Modular Setup**: Each service (NGINX, WordPress, MariaDB) is isolated in its container, allowing for independent scaling and maintenance.
- **🔄 Restart Policies**: Containers are configured to restart automatically in case of failure, ensuring high availability.
- **💡 Environment Variables**: Sensitive information such as database passwords and certificates is managed through environment variables, improving security and maintainability.
- **🔧 Custom Dockerfiles**: Each service is built from scratch using custom Dockerfiles, ensuring that the setup is optimized for your specific requirements.

---

## 🧑‍💻 Usage

To deploy the infrastructure, use the provided **Makefile** to set up all containers. The following commands are available:

```bash
# Build and start the entire Docker infrastructure
make

# Stop and remove the containers
make fclean

# Rebuild and restart the infrastructure
make re
```

---

## 📋 Dockerized Services

The following services are included in the project:

- **NGINX**: Acts as the reverse proxy server, handling HTTPS connections with TLS and forwarding requests to the appropriate services.
- **WordPress**: A containerized WordPress website using PHP-FPM for dynamic content generation.
- **MariaDB**: The database container that stores all data related to the WordPress site, with persistent storage enabled via Docker volumes.
- **Volumes**: Two volumes are created:
  - One for the WordPress database.
  - One for the WordPress website files.

---

## 📁 Project Structure

The project follows a well-organized directory structure that ensures modularity and scalability:

```
inception/
│
├── Makefile                  # Build instructions for the project
├── scrs/                     # Source files for Docker setup
│   ├── docker-compose.yml     # Main Docker Compose file
│   ├── .env                   # Environment variables for the project
│   └── requirements/          # Service-specific configurations
│       ├── mariadb/           # MariaDB Docker setup
│       │   └── Dockerfile
│       ├── nginx/             # NGINX Docker setup with TLS
│       │   └── Dockerfile
│       └── wordpress/         # WordPress + php-fpm setup
│           └── Dockerfile
```

---

## 🔍 Technical Highlights

### 1. **Custom Dockerfiles**
Each service (NGINX, WordPress, MariaDB) has its custom Dockerfile, ensuring that the environment is tailored for the project’s needs without relying on pre-built images.

### 2. **TLS Security with NGINX**
The NGINX server is configured to only allow secure connections via TLSv1.2 and TLSv1.3, providing enhanced security for web traffic.

### 3. **Environment Variables and `.env` File**
All sensitive data (e.g., database credentials, domain names) are stored in an `.env` file, improving security and preventing hardcoding of passwords in Dockerfiles.

### 4. **Modular and Scalable Setup**
The use of Docker containers allows each service to be scaled independently. The architecture is designed for easy maintenance and future scaling.

---

## 🛡️ Robustness and Scalability

- **Automatic Restarts**: Containers are configured with restart policies, ensuring that the services automatically recover from failures.
- **Modular Services**: Each service is isolated in its container, which enables easy scaling and independent updates.
- **Data Persistence**: The use of Docker volumes ensures that the WordPress site and MariaDB data persist even if the containers are stopped or removed.

---

## 🌟 Bonus Features

The following optional features can be added to enhance the infrastructure:

- **Redis Cache**: Set up Redis caching for the WordPress site to improve performance.
- **FTP Server**: Configure an FTP server that points to the WordPress volume, allowing for direct file uploads.
- **Static Website**: Create a static website in a language of your choice (excluding PHP) for additional functionality.
- **Adminer**: Set up Adminer for easy database management.

---

## 🔧 Testing

To test the setup, ensure Docker is installed and run the following commands:

```bash
# Build and start the infrastructure
make

# Access the WordPress site by navigating to the custom domain in your browser (e.g., login.42.fr)
```

You can also test specific containers by accessing their logs or running commands directly within them.

---

## 🏅 Conclusion

**Inception** is a practical system administration project that gives you hands-on experience with Docker. By building a fully containerized web infrastructure, you gain knowledge of how real-world servers are deployed and managed, all while maintaining a focus on security and scalability. 
