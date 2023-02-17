cmake_minimum_required(VERSION 3.23)
project(numberSeries)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-IC:/Users/rasmu/CLionProjects/Selected-topics-within-programming/Session2)
add_link_options(-LC:/Users/rasmu/CLionProjects/Selected-topics-within-programming/Session2/cmake-build-debug/Session2.dir/Debug)
add_executable(numberSeries main.cpp NumberSeries.cpp NumberSeries.h Client.cpp Client.h)
target_link_libraries(numberSeries PRIVATE C:/Users/rasmu/CLionProjects/Selected-topics-within-programming/Session2/cmake-build-debug/Session2.dir/Debug/Benchmark.obj)