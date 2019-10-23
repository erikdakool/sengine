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
        TextureLoader.cpp
        TextureLoader.h VboIndex.cpp VboIndex.h Renderer.cpp Renderer.h ModelLoader.cpp ModelLoader.h Managers.h)

target_link_libraries(GLEngine GL glfw GLEW)