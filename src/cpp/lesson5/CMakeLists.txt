cmake_minimum_required(VERSION 3.6)
project(lesson5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BigInt.cpp BigInt.h)
add_executable(lesson5 ${SOURCE_FILES})