cmake_minimum_required(VERSION 3.24)
project(exam)
include_directories(include)
set(CMAKE_CXX_STANDARD 20)

add_executable(exam src/main.cpp include/benchmark/benchmark.cpp)
