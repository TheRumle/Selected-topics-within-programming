    
add_executable(symbolTable_test symbolTable_test.cpp)
target_link_libraries(symbolTable_test PRIVATE doctest::doctest)
add_test(NAME symbolTable_test COMMAND symbolTable_test.cpp)

#test and their executables
add_test(NAME test11 COMMAND test11)
