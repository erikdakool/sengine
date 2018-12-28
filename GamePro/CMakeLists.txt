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
        CollisionController.h Components/PlayerController.cpp Components/PlayerController.h)

target_link_libraries (GamePro jsoncpp sfml-graphics sfml-audio sfml-window sfml-system)
