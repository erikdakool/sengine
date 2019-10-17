cmake_minimum_required(VERSION 3.14)
project(UntitledProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(UntitledProject main.cpp)

target_link_libraries(UntitledProject tensorflow jsoncpp sfml-graphics sfml-audio sfml-window sfml-system)