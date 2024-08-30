cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(Ball LANGUAGES CXX)

find_package(SDL2)

add_executable(Ball
    "src/main.cpp"
    "src/Render.h"
    "src/Vector.h"
    "src/Ball.h"
    "src/Type.h"
)

if(TARGET SDL2::SDL2main)
    target_link_libraries(Ball PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(Ball
    PRIVATE SDL2::SDL2
)
