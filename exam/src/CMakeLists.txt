add_library(doctest OBJECT doctest.cpp)


add_executable(test11 doctest.cpp)
add_test(NAME test11 COMMAND test11)
