
# 🌐 **NetPractice** - Network Configuration Challenge

**NetPractice** is a project designed to sharpen your networking skills. You will work through 10 levels of networking challenges, where you need to configure networks by editing IP addresses, subnet masks, and gateways. Each level contains a different network configuration problem, and your task is to solve these issues to ensure seamless communication within the network. 🚀

---

## 🎯 **Project Overview**

The goal of **NetPractice** is to correct and configure network setups across 10 different levels. Each level provides a broken network diagram with issues like incorrect IP addresses, subnet masks, or gateway configurations. Your task is to diagnose and fix these issues.

---

## 🚀 **Getting Started**

1. **Download the Files**:
   - The project includes JSON files for each level (`level1.json` through `level10.json`). These files represent the configurations for each level.

2. **Launch the Interface**:
   - The exercise is completed using a web-based interface. You can either use the provided levels or load these `.json` files into the interface to review or adjust configurations.

3. **Modify and Solve**:
   - Each `.json` file corresponds to a level's network configuration. You will adjust the IP addresses, subnet masks, and routing details in these files to solve the issues.

---

## 📋 **How to Work with the Files**

Each `.json` file contains the network configurations for that particular level. You will need to:

1. **Identify the Problems**:
   - Open the `.json` file and review the provided IP addresses, subnet masks, and gateway configurations.
   
2. **Fix the Configuration**:
   - Adjust the configuration parameters like IP addresses, subnets, and gateways to ensure all devices in the network can communicate.

3. **Test the Network**:
   - Once the changes are made, you can load the file into the web interface to test the configuration and check if the network issues are resolved.

---

## 🛠️ **Understanding the JSON Files**

Each level is represented by a `.json` file that looks like this:

```json
{
  "routers": [
    {
      "name": "Router 1",
      "interfaces": [
        {
          "ip": "192.168.1.1",
          "subnet_mask": "255.255.255.0"
        }
      ]
    }
  ],
  "hosts": [
    {
      "name": "Host 1",
      "ip": "192.168.1.2",
      "gateway": "192.168.1.1"
    }
  ]
}
```

- **Routers**: Lists the routers in the network, their interfaces, and the respective IP addresses and subnet masks.
- **Hosts**: Lists the end devices (like computers) connected to the network, their IP addresses, and their default gateways.

---

## 📂 **Project Structure**

```bash
netpractice/
│
├── level1.json          # Configuration for level 1
├── level2.json          # Configuration for level 2
├── level3.json          # Configuration for level 3
├── level4.json          # Configuration for level 4
├── level5.json          # Configuration for level 5
├── level6.json          # Configuration for level 6
├── level7.json          # Configuration for level 7
├── level8.json          # Configuration for level 8
├── level9.json          # Configuration for level 9
└── level10.json         # Configuration for level 10
```

---

## 🔍 **Tips for Solving Levels**

- **IP Addressing**: Ensure all IP addresses belong to the same subnet if devices need to communicate directly.
- **Subnet Masks**: Make sure subnet masks are configured correctly to allow communication across different segments of the network.
- **Gateways**: Verify that all hosts point to the correct default gateway for external communication.
- **Routing**: For levels involving multiple routers, make sure the routes between subnets are properly defined.

---

## 🔑 **How to Solve a Typical Level**

1. **Open the Level's `.json` File**: 
   - For example, open `level1.json` to view the network configuration.

2. **Check IP and Subnet Configurations**: 
   - Make sure the IP addresses and subnet masks are configured to allow proper communication within the network.

3. **Fix Gateways**:
   - Set the correct gateway for each device to ensure they can communicate with routers or external networks.

4. **Test the Network**:
   - Once the configurations are corrected, load the `.json` file into the interface and check if the issue is resolved.

---

## 🏅 **Evaluation**

During the defense, you will be asked to solve 3 random levels. You must correctly configure the network based on the information given in the `.json` files.

Be prepared to explain:
- How you diagnosed the problem.
- The changes you made to resolve the network configuration issues.

---

## 🏆 **Conclusion**

By completing the **NetPractice** project, you will have developed a deeper understanding of networking principles, particularly around IP addressing, subnetting, and routing. This hands-on experience will be invaluable as you continue to build your networking skills.

---
