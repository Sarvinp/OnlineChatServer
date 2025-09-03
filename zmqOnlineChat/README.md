# 🗨️ ZMQ Chat System

A lightweight cross-language chat system built with [ZeroMQ](https://zeromq.org/) — featuring a C++ server and Python clients. Clients can send messages to the server, which broadcasts them to all other connected clients.

---

## 🚀 Features

- 🔄 Real-time message routing using ZeroMQ's ROUTER/DEALER pattern
- 💬 Multiple Python clients can chat via a C++ server
- 🧵 Real-time messaging with asynchronous Python clients
- 🛑 Graceful shutdown support (type `0` to exit)

---

## 🧱 Architecture

+------------+       +-------------+       +------------+
|  Python    | <---> |  C++ Server | <---> |  Python    |
| Client A   |       |  (ROUTER)   |       | Client B   |
| (DEALER)   |       |             |       | (DEALER)   |
+------------+       +-------------+       +------------+
---

## 🛠 Requirements

### C++ Server
- C++17
- [ZeroMQ C library](https://github.com/zeromq/libzmq)
- CMake ≥ 3.26

### Python Client
- Python ≥ 3.7
- `pyzmq` (`pip install pyzmq`)

---

## ⚙️ Build & Run

### 🔧 C++ Server

```bash
# Configure with CMake
cmake -DZMQ_ROOT="path/to/zeromq" -S . -B build

# Build
cmake --build build

# Run
./build/ZMQServer
