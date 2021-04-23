cmake_minimum_required(VERSION 3.2)
project(CFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_FILES
    src/main.cpp
    src/color_manager.cpp
    src/api.cpp
)

add_executable(cff ${SOURCE_FILES})
