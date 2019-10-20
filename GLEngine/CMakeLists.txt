cmake_minimum_required(VERSION 3.15)
project(GLEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(GLEngine
        main.cpp
        Camera.cpp
        Camera.h
        Triangle.cpp
        Triangle.h
        shader.cpp
        shader.hpp
        Point.cpp
        Point.h
        Transform.cpp
        Transform.h
        Cube.cpp
        Cube.h
        AssetController.cpp
        AssetController.h)

target_link_libraries(GLEngine sfml-graphics sfml-audio sfml-window sfml-system GL glfw GLEW)