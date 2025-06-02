cmake_minimum_required(VERSION 3.10.0)
project(poubelleTankTrouble VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW) # CMake 3.12+ policy to use the new behavior for find_package

include_directories(src)

#find GLFW package
find_package(glfw3 REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(poubelleTankTrouble 
    src/main.cpp 
    src/glad/glad.h 
    src/glad.c
    src/server.hpp
    src/server.cpp
    src/client.hpp
    src/client.cpp
    src/message.hpp
    src/shader_tools.hpp
    src/shader_tools.cpp
    src/game.hpp
    src/game.cpp
)

target_link_libraries(poubelleTankTrouble 
    glfw
    OpenGL::GL
    )