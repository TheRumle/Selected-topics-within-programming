cmake_minimum_required(VERSION 3.23)
project(wordle)

set(CMAKE_CXX_STANDARD 20)

add_executable(wordle main.cpp word_reader.cpp word_reader.h filter.cpp filter.h parse_js.cpp parse_js.h word_search.cpp word_search.h)
