cmake_minimum_required(VERSION 3.7)
project(spaceraft)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /Users/rwblickhan/Developer/Qt5.9/5.9.1/clang_64)

include_directories(include)
add_subdirectory(bgfx.cmake)
find_package(Qt5Widgets)

set(SOURCE_FILES src/main.cpp src/viewport.cpp include/viewport.h)
add_executable(spaceraft ${SOURCE_FILES})
target_link_libraries(spaceraft bgfx)
target_link_libraries(spaceraft Qt5::Widgets)