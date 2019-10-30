cmake_minimum_required(VERSION 3.15)
project(GLEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(GLEngine
        main.cpp
        Camera.cpp
        Camera.h
        Gameobject/Triangle.cpp
        Gameobject/Triangle.h
        Managers/shader.cpp
        Managers/shader.hpp
        Gameobject/Point.cpp
        Gameobject/Point.h
        Transform.cpp
        Transform.h
        Gameobject/Cube.cpp
        Gameobject/Cube.h
        Managers/TextureLoader.cpp
        Managers/TextureLoader.h
        Managers/VboIndex.cpp
        Managers/VboIndex.h
        Components/Renderer.cpp
        Components/Renderer.h
        Managers/ModelLoader.cpp
        Managers/ModelLoader.h
        Managers.h
        Components/Physics.cpp
        Components/Physics.h
        Gameobject/Gameobject.cpp
        Gameobject/Gameobject.h
        Object/Object.cpp
        Object/Object.h
        Components/Component.cpp
        Components/Component.h
        Managers/ObjectManager.cpp
        Managers/ObjectManager.h
        Components/Collider.cpp
        Components/Collider.h CollisionManager.cpp CollisionManager.h)
target_link_libraries(GLEngine GL glfw GLEW reactphysics3d)