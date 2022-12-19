cmake_minimum_required(VERSION 3.19)
project(pawn-template LANGUAGES C CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sdk)
add_subdirectory(network)

include_directories(
		.
		pawn/source
		pawn/source/linux
)

add_definitions(-DHAVE_STDINT_H=1)

add_library(${PROJECT_NAME} SHARED main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

