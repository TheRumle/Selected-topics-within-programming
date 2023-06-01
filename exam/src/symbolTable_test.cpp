//
// Created by rasmus on 6/1/2023.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "functional"
#include "symbolTable/symbolTable.h"

template<typename T>
concept Throwable = std::is_base_of_v<std::exception, std::decay_t<T>>;

template<Throwable T>
bool DidThrow(std::function<void()>&& f) {
    bool hasThrown = false;
    try {
        f();
    } catch (const T& e) {
        hasThrown = true;
    }
    return hasThrown;
}


template<Throwable T>
bool ThatItDoesNotThrow(std::function<void()>&& f){
    return DidThrow<T>(std::forward<std::function<void()>>(f)) == false;
}

template<Throwable T>
bool ThatItThrows(std::function<void()>&& statements) {
    return DidThrow<T>(std::forward<std::function<void()>>(statements)) == true;
}

TEST_CASE("ADD"){
    SUBCASE("Storing duplicate key does should throw out of range"){
        CHECK(ThatItThrows<std::out_of_range>([]() {
            SymbolTable<int, std::string> table{};
            table.add(1, "bingo");
            table.add(1, "bango");
        }));

    SUBCASE("Does not throw when using StoreOrUpdate")   
        CHECK(ThatItDoesNotThrow<std::out_of_range>([]() {
            SymbolTable<int, std::string> table{};
            table.add(1, "tingo");
            table.storeOrUpdate(1, "tango");
        }));
        
        CHECK(ThatItDoesNotThrow<std::out_of_range>([]() {
            SymbolTable<int, std::string> table{};
            table.storeOrUpdate(1, "flimmary");
            table.storeOrUpdate(1, "flummary");
        }));
    }
}

TEST_CASE("UPDATE"){
    SUBCASE("Updating value that does not exist should add instead of throw"){
        SymbolTable<int, std::string> table{};
        CHECK(ThatItDoesNotThrow<std::exception>([&table]() {
            table.update(2, "flippity!");
        }));

        CHECK(table.get(2).has_value());
    }
    
    SUBCASE("Updating value that does should update"){
        SymbolTable<int, std::string> table{};
        table.add(2, "floppity");
        table.update(2, "frick");
        CHECK(table.get(2).has_value());
        CHECK(table.get(2).value() == "frick");
    }
}

TEST_CASE("GET"){
    SUBCASE("Getting a value that is not in add gives empty optional"){
        SymbolTable<int, std::string> table{};
        CHECK(!table.get(2).has_value());
    }
    
    SUBCASE("Getting a value that is in add gives optional with value"){
        SymbolTable<int, std::string> table{};
        table.add(2, "flip");
        CHECK(table.get(2).has_value());
    }
}

TEST_CASE("REMOVE"){
    SUBCASE("Removing a value that is not in add throws exception."){
        SymbolTable<int, std::string> table{};
        CHECK(ThatItThrows<std::exception>([&table]() {
            table.remove(2);
        }));
    }
    
    SUBCASE("Removing a value that is in add does not throw exception."){
        SymbolTable<int, std::string> table{};
        CHECK(ThatItDoesNotThrow<std::exception>([&table]() {
            table.add(2, "flop");
            table.remove(2);
        }));
    }
    
    SUBCASE("The value is removed from the add"){
        SymbolTable<int, std::string> table{};
        table.add(2, "funky");
        table.remove(2);
        CHECK(!table.get(2).has_value());
    }
}