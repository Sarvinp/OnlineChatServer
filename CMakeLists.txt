cmake_minimum_required(VERSION 3.26)
project(BoostServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BOOST_ROOT "C:/Users/nematpour/Downloads/boost_1_89_0/")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/libs")

#find_package(Boost REQUIRED COMPONENTS system thread)

#if(Boost_FOUND)
    include_directories(${BOOST_INCLUDEDIR})
    add_executable(BoostServer
            main.cpp
            Server.cpp
            Server.h
            Session.cpp
            Session.h
    )
    target_link_libraries(BoostServer ${BOOST_LIBRARYDIR}     ws2_32
            mswsock)
#else()
#    message(FATAL_ERROR "Boost not found")
#endif()
