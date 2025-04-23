# LINUX_IPC_MECHANISM

This project demonstrates various **Inter-Process Communication (IPC)** mechanisms available in Linux. IPC allows processes to communicate and synchronize with each other. This repository includes practical examples and code implementations of:

- **D-Bus**
- **Sockets**
- **Message Queues**
- **Shared Memory**
- **Pipelines (Pipes & FIFOs)**

---

## 🧠 IPC Mechanisms Explained

### 1. **D-Bus**
D-Bus is a message bus system that allows applications to communicate with one another. It's commonly used in desktop environments and system services.

- Uses: System-level messaging (e.g., NetworkManager, Bluetooth)
- Features: High-level abstraction, security, object-oriented

### 2. **Sockets**
Sockets are endpoints for sending and receiving data across a network. They can be used for local or network IPC.

- Types: TCP, UDP, UNIX domain sockets
- Use cases: Client-server models, network applications

### 3. **Message Queues**
Message queues allow asynchronous communication by sending messages between processes through a queue.

- Two types: POSIX and System V
- Good for decoupled systems

### 4. **Shared Memory**
Shared memory allows multiple processes to access the same memory space, enabling fast communication.

- High performance
- Needs synchronization (semaphores, mutexes)

### 5. **Pipelines (Pipes & FIFOs)**
Pipes and FIFOs are unidirectional data channels used for communication between processes.

- Pipes: For parent-child communication
- FIFOs (named pipes): For unrelated processes

---

## 🚀 How to Run

Each folder contains:
- Source code (`.c`, `.cpp`, `.py`, etc.)
- Build/run instructions (Makefile or command line)

Example (for C programs):
```bash
cd message_queue
make
./sender
./receiver


