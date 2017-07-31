cmake_minimum_required(VERSION 3.0)
project(spaceraft)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
# nasty hack to get this working with travis, should fix later
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(CMAKE_PREFIX_PATH /Users/rwblickhan/Developer/Qt5.9/5.9.1/clang_64)
else()
    set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu)
endif()

include_directories(include)
add_subdirectory(bgfx.cmake)
find_package(Qt5Widgets)

set(SOURCE_FILES src/main.cpp src/viewport.cpp include/viewport.h)
add_executable(spaceraft ${SOURCE_FILES})
target_link_libraries(spaceraft bgfx)
target_link_libraries(spaceraft Qt5::Widgets)