cmake_minimum_required(VERSION 3.0)
project(ch01)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_COMPILER g++)
set(SOURCES src/disable_copy.cpp)
add_executable(disable_copy ${SOURCES})
