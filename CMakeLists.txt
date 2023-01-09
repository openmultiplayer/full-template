cmake_minimum_required(VERSION 3.19)
project(full-template LANGUAGES C CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sdk)
add_subdirectory(network)

include_directories(
	.
	pawn/source
	pawn/source/linux
)

add_definitions(
	-DHAVE_STDINT_H=1
	-DPAWN_CELL_SIZE=32
)

add_library(${PROJECT_NAME} SHARED
	api.cpp
	main.cpp
	natives.cpp
	weather-component.cpp
	weather-extension.cpp
	weather-region.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

