cmake_minimum_required(VERSION 3.15)
project(GLEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
add_executable(GLEngine
        main.cpp
        Camera.cpp
        Camera.h
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
        Components/Collider.h
        CollisionManager.cpp
        CollisionManager.h
        Managers/InputManager.cpp
        Managers/InputManager.h
        Gameobject/Excavator.cpp
        Gameobject/Excavator.h Components/NoclipController.cpp Components/NoclipController.h Object/Block.h Managers/BlockManager.cpp Managers/BlockManager.h Managers/TerrainGenerator.cpp Managers/TerrainGenerator.h Structs/Face.h Object/Block.cpp Managers/PerlinNoise.cpp Managers/PerlinNoise.h Structs/BlockInfo.h Structs/TextureInfo.h)


target_link_libraries(GLEngine PRIVATE GL GLEW glfw glm LinearMath Bullet3Common BulletDynamics BulletSoftBody jsoncpp_lib)
