//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_SYMBOLTABLE_H
#define LAMBDAS_SYMBOLTABLE_H

#include <map>
#include <stdexcept>
#include <optional>
#include <unordered_map>
#include <string>

template<typename TKey, typename T>
class symbol_table{
    std::map<TKey, T> table;
    
public:
    void storeOrUpdate(const TKey &symbol, T object) {
        const auto& found = table.find(symbol);
        if(found != table.end()){
            (*found).second = object;
        } else{
            store(symbol, object);
        }
    }
    
    void store(const TKey &symbol, T object){
        table.emplace(symbol, object);
    }
    
    /// Updates the storage if the value exists else does nothing.
    /// \param symbol 
    /// \param object 
    void update(const TKey &symbol, T object){
        const auto& found = table.find(symbol);
        if(found != table.end()){
            (*found).second = object;
        }
    }
    
    [[nodiscard]] size_t size() const {
        return table.size();
    }

    // Iterator support
    auto begin() { return table.begin(); }
    auto end() { return table.end(); }
    auto begin() const { return table.begin(); }
    auto end() const { return table.end(); }
};



#endif  // LAMBDAS_SYMBOLTABLE_H
