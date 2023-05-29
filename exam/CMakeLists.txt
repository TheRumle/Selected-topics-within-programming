cmake_minimum_required(VERSION 3.15)
project(exam CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(UBSAN "Undefined Behavior Sanitizer" OFF)
option(ASAN "Address Sanitizer" OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wpedantic -Wall -Wextra -Wconversion -Wdangling-else)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

if (UBSAN)
    if (UNIX)
        # Linux/Mac: GCC/Clang/Apple_Clang have the same options
        add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
        add_link_options(-fsanitize=undefined)
    elseif(WIN32)
        if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
            add_link_options(-fsanitize=undefined)
            message(STATUS "Address sanitizer is probably not supported by GCC/Clang on Windows")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            add_compile_options(/fsanitize=undefined)
            add_link_options(/fsanitize=undefined)
        endif()
    endif()
endif()

if (ASAN)
    if (UNIX)
        # Linux/Mac: GCC/Clang/Apple_Clang have the same options
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    elseif(WIN32)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
            add_link_options(-fsanitize=address)
            message(STATUS "Address sanitizer is probably not supported by GCC/Clang on Windows")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            add_compile_options(/fsanitize=address)
            add_link_options(/fsanitize=address)
        endif()
    endif()
endif()


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

include_directories(include)

enable_testing()

add_subdirectory(src)

add_executable(main src/main.cpp include/symbol_table include/reaction/agents.h include/reaction/construction_rules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/ReactionNetwork.h include/reaction_network/ReactionNetwork.cpp)
add_executable(simple src/simple.cpp include/symbol_table include/reaction/agents.h include/reaction/construction_rules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/ReactionNetwork.h include/reaction_network/ReactionNetwork.cpp include/reaction_network/ReactionNetworkRunner.cpp include/reaction_network/ReactionNetworkRunner.h)
add_executable(circadian src/circadian.cpp include/symbol_table include/reaction/agents.h include/reaction/construction_rules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/ReactionNetwork.h include/reaction_network/ReactionNetwork.cpp include/reaction_network/ReactionNetworkRunner.cpp include/reaction_network/ReactionNetworkRunner.h)
add_executable(figure3 src/covid.cpp include/symbol_table include/reaction/agents.h include/reaction/construction_rules.h include/reaction/reaction.cpp include/reaction/reaction.h include/reaction_network/ReactionNetwork.h include/reaction_network/ReactionNetwork.cpp include/reaction_network/ReactionNetworkRunner.cpp include/reaction_network/ReactionNetworkRunner.h)
