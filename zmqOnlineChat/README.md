# 🗨️ ZMQ Chat System

A lightweight cross-language chat system built with [ZeroMQ](https://zeromq.org/) — featuring a C++ server and Python clients. Clients can send messages to the server, which broadcasts them to all other connected clients.

---

## 🚀 Features

- 🔄 Real-time message routing using ZeroMQ's ROUTER/DEALER pattern
- 💬 Multiple Python clients can chat via a C++ server
- 🧵 Asynchronous message handling
- 🛑 Graceful shutdown support (type `0` to exit)

---

## 🧱 Architecture

+------------+ +-------------+ +------------+
| Python | <---> | C++ Server | <---> | Python |
| Client A |          | (ROUTER) |             | Client B |
| (DEALER) |             |        |                 | (DEALER) |
+------------+    +-------------+     +------------+


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
## 🔧 Installing ZeroMQ

ZeroMQ consists of a **core C library (**`libzmq`**)** and **language bindings** like `pyzmq` for Python. Here's how to install it on major platforms:

### 🖥️ For C++ (libzmq)

#### ✅ **Windows (MSYS2 recommended)**

bash

```
# Open MSYS2 terminal and run:
pacman -S mingw-w64-x86_64-zeromq
```

This installs both the headers and compiled libraries (`libzmq.dll.a`, `zmq.h`) for use with MinGW.

> 💡 Make sure your CMake project points to the correct include and lib paths:
> 
> - Include: `C:/msys64/mingw64/include`
>     
> - Lib: `C:/msys64/mingw64/lib`
>     

#### 🐧 **Linux (Debian/Ubuntu)**

bash

```
sudo apt update
sudo apt install libzmq3-dev
```

#### 🍎 **macOS (using Homebrew)**

bash

```
brew install zeromq
```

### 🐍 For Python (Client)

Install the Python binding `pyzmq` via pip:

bash

```
pip install pyzmq
```

This works across Windows, Linux, and macOS. It includes precompiled binaries, so no need to build `libzmq` separately unless you're doing advanced C++ integration.

### 📦 Building from Source (Optional)

If you want to build ZeroMQ manually:

bash

```
git clone https://github.com/zeromq/libzmq.git
cd libzmq
mkdir build && cd build
cmake ..
cmake --build . --target install
```

> 🔐 After installing on Linux, run `sudo ldconfig` to update the linker cache.


## ⚙️ Build & Run

### 🔧 C++ Server

```bash
# Configure with CMake
cmake -DZMQ_ROOT="path/to/zeromq" -S . -B build

# Build
cmake --build build

# Run
./build/ZMQServer
```

### 📚 Resources

- ZeroMQ Downloads
    
- ZeroMQ Installation Guide
