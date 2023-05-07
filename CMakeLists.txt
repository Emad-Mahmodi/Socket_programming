cmake_minimum_required(VERSION 3.21)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# Create a library for the server and client classes
add_library(MyLib SHARED
        clien_server_class/server.cpp
        clien_server_class/client.cpp
        )
target_include_directories(MyLib PUBLIC clien_server_class)

# Link the library against the required Winsock library
target_link_libraries(MyLib PRIVATE ws2_32)

# Add the executables
add_executable(Server main.cpp)
target_link_libraries(Server PRIVATE MyLib)

add_executable(Client main_s.cpp)
target_link_libraries(Client PRIVATE MyLib)

# Add compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()