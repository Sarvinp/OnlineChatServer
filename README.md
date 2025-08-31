# OnlineChatServer
# C++ Server & Python Client

This project demonstrates a **C++ TCP server** built with [Boost.Asio](https://www.boost.org/doc/libs/release/doc/html/boost_asio.html) and a **Python client** for testing and interaction.

## 📦 Requirements

### Server (C++)
- C++17 or later
- [Boost](https://www.boost.org/) (system, thread components)
- CMake 3.16+

### Client (Python)
- Python 3.8+
- `pyzmq` or `socket` (depending on your client implementation)

---

## 🔧 Building the Server

### 1. Install Boost
You can install Boost via your package manager or manually:

**Linux (apt example):**
```bash
sudo apt install libboost-all-dev
```


**Windows (vcpkg example):**
```bash
vcpkg install boost-system boost-thread
```

### 2. Configure CMake
**Option A – Use find_package**
If Boost is installed in a standard location:
```cmake
find_package(Boost REQUIRED COMPONENTS system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()
```

**Option B – Manually add Boost with add_library**
If you have Boost built locally and want to link manually:
```cmake
add_library(boost_system STATIC IMPORTED)
set_target_properties(boost_system PROPERTIES
    IMPORTED_LOCATION "/path/to/boost/stage/lib/libboost_system.a"
    INTERFACE_INCLUDE_DIRECTORIES "/path/to/boost"
)

add_library(boost_thread STATIC IMPORTED)
set_target_properties(boost_thread PROPERTIES
    IMPORTED_LOCATION "/path/to/boost/stage/lib/libboost_thread.a"
    INTERFACE_INCLUDE_DIRECTORIES "/path/to/boost"
)

target_link_libraries(${PROJECT_NAME} boost_system boost_thread)
```

### 3. Build
```bash
cmake -B build
cmake --build build
```

## ▶ Running
Start the server:
```bash
./BoostServer 12345
Run the Python client:
python main.py
```


## 📚 Notes
The server uses Boost.Asio for asynchronous networking.

The Python client can be adapted to send/receive messages in your chosen protocol.

On Windows, you may need to link ws2_32 and mswsock:
```cmake
target_link_libraries(${PROJECT_NAME} ws2_32 mswsock)
```
