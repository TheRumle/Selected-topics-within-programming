    
add_executable(symbolTable_test symbolTable_test.cpp)
target_link_libraries(symbolTable_test PRIVATE doctest::doctest)
add_test(NAME symbolTable_test COMMAND symbolTable_test.cpp)
