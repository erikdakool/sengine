cmake_minimum_required(VERSION 3.15)
project(GLEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(GLEngine main.cpp Cube.cpp Cube.h Matrix.h Matrix.tpp Point.cpp Point.h Vector3D.cpp Vector3D.h Transform.cpp Transform.h)

target_link_libraries(GLEngine sfml-graphics sfml-audio sfml-window sfml-system GL)