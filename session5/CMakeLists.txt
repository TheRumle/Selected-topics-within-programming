cmake_minimum_required(VERSION 3.23)
project(session5)

set(CMAKE_CXX_STANDARD 20)

add_executable(session5 main.cpp polymorphic_test/base.h polymorphic_test/base.cpp polymorphic_test/derived.cpp polymorphic_test/derived.h benchmark/Benchmark.cpp benchmark/Benchmark.h benchmark/timer.cpp benchmark/timer.h benchmark/benchmark_result.h benchmark/benchmark_result.cpp)
