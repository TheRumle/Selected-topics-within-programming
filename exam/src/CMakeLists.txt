add_library(doctest OBJECT doctest.cpp covid.cpp)


#test and their executables
add_test(NAME test11 COMMAND test11)
