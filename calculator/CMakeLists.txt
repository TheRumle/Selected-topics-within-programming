cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF) # Stick with statically linked libraries

include(sanitizers.cmake)
include(doctest.cmake)
    
add_executable(test_calculator test_calculator.cpp terms/const_t.h terms/assign_t.h terms/term_t.h terms/var_t.h terms/binary_t.cpp terms/binary_t.h terms/unary_t.cpp terms/unary_t.h)
target_link_libraries(test_calculator PRIVATE doctest::doctest)

enable_testing()
add_test(NAME test_calculator COMMAND test_calculator)
