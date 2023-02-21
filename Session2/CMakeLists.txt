cmake_minimum_required(VERSION 3.21)
project(Session2)

set(CMAKE_CXX_STANDARD 20)
add_library(libBenchmark SHARED Benchmark.cpp timer.cpp  benchmark_result.cpp types_and_sizes.cpp  endian_test.cpp)
                add_executable(Session2 main.cpp Benchmark.cpp Benchmark.h timer.cpp timer.h benchmark_result.h benchmark_result.cpp types_and_sizes.cpp types_and_sizes.h endian_test.cpp endian_test.h bench_random.cpp bench_random.h)
