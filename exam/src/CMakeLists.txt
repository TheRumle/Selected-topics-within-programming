    
add_executable(symbolTable_test symbolTableTest.cpp)
target_link_libraries(symbolTable_test PRIVATE doctest::doctest)
add_test(NAME symbolTable_test COMMAND symbolTableTest.cpp)
