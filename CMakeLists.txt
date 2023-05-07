cmake_minimum_required(VERSION 3.21)
project(exec)

set(CMAKE_CXX_STANDARD 17)
#add_subdirectory(udp1)

add_executable(exec main.cpp UDPSocket.cpp)
target_link_libraries(exec ws2_32)
