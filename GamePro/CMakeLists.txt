cmake_minimum_required(VERSION 3.13)
project(GamePro)

set(CMAKE_CXX_STANDARD 14)

add_executable(GamePro
        main.cpp
        App.cpp
        App.h
        Gameobject.cpp
        Gameobject.h
        Components/Transform.cpp
        Components/Transform.h
        Components/Component.cpp
        Components/Component.h
        Components/RenderCom.cpp
        Components/RenderCom.h
        WindowController.cpp
        WindowController.h
        Manager.h
        Components/Movement.cpp
        Components/Movement.h
        ObjectController.cpp
        ObjectController.h
        Components/Collider.cpp
        Components/Collider.h
        CollisionController.cpp
        CollisionController.h
        Components/PlayerController.cpp
        Components/PlayerController.h
        Components/Physics.cpp
        Components/Physics.h
        AssetController.cpp
        AssetController.h
        ObjectLoader.cpp
        ObjectLoader.h
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
        GraphicsController.cpp
        GraphicsController.h
        ObjectFactory.cpp
        ObjectFactory.h
        )

target_link_libraries (GamePro jsoncpp tgui sfml-graphics sfml-audio sfml-window sfml-system)
