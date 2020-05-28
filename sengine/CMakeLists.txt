cmake_minimum_required(VERSION 3.16)
project(sengine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(protobuf CONFIG REQUIRED)

add_executable(sengine
        main.cpp
        test.pb.cc
        )


target_compile_features(sengine
        PRIVATE
        cxx_std_17)

target_compile_options(sengine
        PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

# Any additional include files would go here
#target_include_directories(simple-sfml-cmake-example
#                           PUBLIC
#                           )

target_compile_definitions(sengine
        PRIVATE
        $<$<CONFIG:Debug>:DEBUG>)

target_link_libraries(sengine
        PRIVATE
        GL
        sfml-graphics ${CMAKE_DL_LIBS}
        sfml-window ${CMAKE_DL_LIBS}
        sfml-system ${CMAKE_DL_LIBS}
        sfml-audio ${CMAKE_DL_LIBS}
        protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
        )