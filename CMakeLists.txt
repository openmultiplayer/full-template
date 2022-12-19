cmake_minimum_required(VERSION 3.19)
project(pawn-template LANGUAGES C CXX VERSION 0.0.1)

add_subdirectory(sdk)
add_subdirectory(network)

add_library(${PROJECT_NAME} SHARED main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

