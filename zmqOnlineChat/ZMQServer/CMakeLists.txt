cmake_minimum_required(VERSION 3.26)
project(ZMQServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow user to specify ZeroMQ root directory externally
set(ZMQ_ROOT "" CACHE PATH "Path to ZeroMQ installation")

# Define include and lib directories based on ZMQ_ROOT
set(ZMQ_INCLUDE_DIR "${ZMQ_ROOT}/include")
set(ZMQ_LIB_DIR "C:/msys64/mingw64/libzmq/build/lib")

# Add to module path if you have custom Find scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include and link directories
include_directories(${ZMQ_INCLUDE_DIR})
link_directories(${ZMQ_LIB_DIR})

# Executable
add_executable(ZMQServer main.cpp ChatServer.cpp)

# Link against ZeroMQ
target_link_libraries(ZMQServer PRIVATE libzmq)
