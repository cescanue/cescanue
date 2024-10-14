
# 🛡️ **BornToBeRoot** - Ultimate Beginner-Friendly Server Setup Guide

Welcome to **BornToBeRoot**, a project designed to guide you step-by-step through setting up and securing your own server on a Debian-based virtual machine. Whether you have no technical knowledge or are experienced in system administration, this guide will help you complete the project smoothly. Let's get started! 🚀

---

## 🛠️ **Pre-Requisites**

### 🔧 **Tools & Resources**
- **VirtualBox** (or **UTM**) for creating a virtual machine.
- A **Debian** or **Rocky Linux** ISO file (latest stable version).
- Stable internet connection for downloading and updating packages.

### 📋 **Requirements**
- **5GB of disk space** allocated for the virtual machine.
- Network configured in **Bridge Mode** to ensure your virtual machine can communicate with other devices on your network.

---

## 📚 **Step-by-Step Instructions**

### 🖥️ **1. Virtual Machine Setup**

1. **Install VirtualBox or UTM**:
   - Download and install **VirtualBox** or **UTM** depending on your system.
  
2. **Create a Virtual Machine**:
   - Allocate **5GB of space** for the virtual machine and assign at least **2 CPUs**.
   
3. **Configure Network**:
   - Set the network to **Bridge Mode** to allow the virtual machine to access the internet directly.

---

### 🖥️ **2. Debian Installation**

#### 🔍 **Expert Mode Installation**
- Boot into **Expert Mode** during installation for more control over the system setup. This will allow you to configure advanced options like partitioning.

#### 🗂️ **Partitioning with LVM**
1. Choose to install Debian with **LVM** (Logical Volume Manager). 
   - This allows you to manage disk partitions more flexibly.
2. Set up at least two partitions:
   - **/boot** (unencrypted)
   - **/ (root)** (encrypted with LVM)

3. **Create a Separate `/home` Partition**:
   - During the partition setup, create an additional LVM partition for `/home`, which stores user data separately from the system.

---

### 🛠️ **3. Post-Installation Steps**

#### 📦 **APT vs Aptitude**
- **APT** is the default package manager for Debian, while **Aptitude** offers a more advanced interface and handles dependencies more effectively. Choose **APT** for simplicity, or explore **Aptitude** if you’re interested in advanced package management.  
  - Learn more: [APT vs Aptitude](https://www.fosslinux.com/43884/apt-vs-aptitude.htm)

#### 🔐 **AppArmor vs SELinux**
- Debian uses **AppArmor** by default, which requires fewer kernel modifications compared to **SELinux** and works well with network file systems (NFS). 
  - Learn more: [AppArmor Wiki](https://en.wikipedia.org/wiki/AppArmor)

---

### 🖥️ **4. System Update & Configuration**

1. **System Update**:
   - After installation, it’s crucial to update your system:
     ```bash
     sudo apt update && sudo apt upgrade
     ```

2. **Install Basic Tools**:
   - Install necessary tools:
     ```bash
     sudo apt install vim wget unzip iperf
     ```

3. **Fix Locale Issues (Optional)**:
   - Add the following to your `~/.bashrc` to fix locale problems:
     ```bash
     export LC_ALL=C
     ```

4. **Change Hostname**:
   - Update your hostname to reflect your identity. Replace `user42` with your chosen hostname.
     ```bash
     sudo nano /etc/hostname
     sudo nano /etc/hosts
     ```

---

### 🔐 **5. SSH & Sudo Configuration**

#### 🛡️ **SSH Server Setup**

1. **Install SSH**:
   - Install the **OpenSSH Server**:
     ```bash
     sudo apt install openssh-server
     ```

2. **Change SSH Port**:
   - Change the SSH port from the default (`22`) to `4242` for added security:
     ```bash
     sudo nano /etc/ssh/sshd_config
     # Set: Port 4242
     ```

3. **Disable Root Login**:
   - For additional security, disable root login via SSH:
     ```bash
     PermitRootLogin no
     ```

4. **Restart SSH**:
   - Apply the changes by restarting the SSH service:
     ```bash
     sudo service ssh restart
     ```

---

#### 👤 **Sudo Configuration**

1. **Install Sudo**:
   - Install and configure **sudo** for administrative tasks:
     ```bash
     sudo apt install sudo
     sudo reboot
     ```

2. **Configure Password Policies**:
   - Set up a secure password policy for sudo users:
     - Create the log directory:
       ```bash
       sudo mkdir /var/log/sudo
       ```

     - Add the following configuration in `/etc/sudoers.d/config`:
       ```bash
       Defaults passwd_tries=3
       Defaults badpass_message="Wrong password"
       Defaults logfile="/var/log/sudo/sudo_config"
       Defaults log_input, log_output
       Defaults iolog_dir="/var/log/sudo"
       Defaults requiretty
       Defaults secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
       ```

---

### 🔒 **6. Firewall Setup (UFW)**

1. **Install UFW**:
   - UFW (Uncomplicated Firewall) is a firewall management tool. Install it using:
     ```bash
     sudo apt install ufw
     ```

2. **Enable Firewall**:
   - Enable UFW to secure your server:
     ```bash
     sudo ufw enable
     ```

3. **Allow SSH Port 4242**:
   - Allow traffic on port `4242` for SSH:
     ```bash
     sudo ufw allow 4242
     ```

4. **Check Firewall Status**:
   - Verify that UFW is running and which ports are open:
     ```bash
     sudo ufw status
     ```

---

### 🔑 **7. Strong Password Policy**

1. **Configure Password Expiry**:
   - Edit `/etc/login.defs` to set strong password policies:
     ```bash
     PASS_MAX_DAYS   30
     PASS_MIN_DAYS   2
     PASS_WARN_AGE   7
     ```

2. **Install Password Quality Library**:
   - Install `libpam-pwquality` to enforce password complexity:
     ```bash
     sudo apt install libpam-pwquality
     ```

3. **Enforce Strong Passwords**:
   - Edit `/etc/pam.d/common-password` to enforce the following password rules:
     ```bash
     minlen=10 ucredit=-1 dcredit=-1 lcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root
     ```

---

### 📊 **8. Monitoring Script Setup**

We’ll create a script called `monitoring.sh` that will collect and display system information such as CPU load, memory usage, and network statistics.

1. **Create the Script**:
   - Open a file and copy the following content:
     ```bash
     sudo nano /usr/local/bin/monitoring.sh
     ```

   ```bash
   #!/bin/bash
   echo "Architecture: $(uname -a)"
   echo "CPU Physical: $(grep 'physical id' /proc/cpuinfo | wc -l)"
   echo "Memory Usage: $(free -m | grep Mem | awk '{printf("%s/%sMB (%.2f%%)", $3, $2, ($3/$2)*100)}')"
   ```

2. **Make Script Executable**:
   - Allow the script to be executed:
     ```bash
     sudo chmod +x /usr/local/bin/monitoring.sh
     ```

3. **Set up Cron Job**:
   - Run the script every 10 minutes:
     ```bash
     sudo crontab -e
     ```
   - Add the following line:
     ```bash
     */10 * * * * /usr/local/bin/monitoring.sh | wall
     ```

---

### 🏅 **Bonus Section**

#### 🌐 **Install WordPress**:
   - You can also use this server to install a WordPress website. Follow the steps in the guide to install Lighttpd, MariaDB, and WordPress.

#### 🖥️ **Install Samba (CIFS)**:
   - Install Samba to share files between Linux and Windows systems:
     ```bash
     sudo apt install samba smbclient cifs-utils
     ```

---

## 🎉 **Conclusion**

Congratulations on setting up a secure server with **BornToBeRoot**! You've learned valuable system administration skills such as SSH configuration, firewall setup, password enforcement, and system monitoring. Continue exploring the bonus sections to further enhance your server management expertise.

---
