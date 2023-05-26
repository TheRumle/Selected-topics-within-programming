add_library(doctest OBJECT doctest.cpp)


#test and their executables
add_executable(test11 doctest.cpp reaction/Reaction.h)
add_test(NAME test11 COMMAND test11)
