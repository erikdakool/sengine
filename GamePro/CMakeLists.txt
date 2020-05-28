cmake_minimum_required(VERSION 3.13)
project(GamePro)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS system window graphics audio system REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)

add_executable(
        GamePro
        main.cpp
        App.cpp
        App.h
        Gameobjects/Gameobject.cpp
        Gameobjects/Gameobject.h
        Components/Transform.cpp
        Components/Transform.h
        Components/Component.cpp
        Components/Component.h
        Components/RenderCom.cpp
        Components/RenderCom.h
        Controllers/WindowController.cpp
        Controllers/WindowController.h
        Manager.h
        Components/Movement.cpp
        Components/Movement.h
        Controllers/ObjectController.cpp
        Controllers/ObjectController.h
        Components/Collider.cpp
        Components/Collider.h
        Controllers/CollisionController.cpp
        Controllers/CollisionController.h
        Components/PlayerController.cpp
        Components/PlayerController.h
        Components/Physics.cpp
        Components/Physics.h
        Controllers/AssetController.cpp
        Controllers/AssetController.h
        Controllers/ObjectLoader.cpp
        Controllers/ObjectLoader.h
        Components/InputController.cpp
        Components/InputController.h
        Components/AnimationController.cpp
        Components/AnimationController.h
        Components/AudioCom.cpp
        Components/AudioCom.h
        DataTypes/TextureRect.cpp
        DataTypes/TextureRect.h
        DataTypes/Animation.cpp
        DataTypes/Animation.h
        Controllers/GraphicsController.cpp
        Controllers/GraphicsController.h
        Controllers/ObjectFactory.cpp
        Controllers/ObjectFactory.h
        SceneVariables.h)

target_link_libraries (GamePro PRIVATE OpenAL::OpenAL jsoncpp_lib sfml-graphics sfml-audio sfml-window sfml-system)
