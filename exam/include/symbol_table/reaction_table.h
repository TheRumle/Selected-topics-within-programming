//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_TABLE_H
#define LAMBDAS_REACTION_TABLE_H

#include <map>
#include <stdexcept>
#include <optional>
#include <unordered_map>
#include <string>

template<typename TKey, typename T>
class symbol_table{
    std::unordered_map<TKey, T> table;
    
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

    std::optional<T> tryGetValue(const TKey symbol) {
        try{
            auto it = table.find(symbol);
            
            if (it != table.end()) {
                return it->second;
            }

            return std::nullopt;
        } catch (...) {
            auto q = 2;
            
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

template<typename T>
class reaction_table : public  symbol_table<std::string, T>
{

public:
};




#endif  // LAMBDAS_REACTION_TABLE_H
