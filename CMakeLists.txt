cmake_minimum_required(VERSION 3.0)
project(spaceraft)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

include_directories(src/inc)
add_subdirectory(bgfx.cmake)
find_package(SDL2)

set(SOURCE_FILES src/main.cpp src/viewport.cpp src/inc/viewport.h)
add_executable(spaceraft ${SOURCE_FILES})
target_link_libraries(spaceraft bgfx)
target_link_libraries(spaceraft SDL2)