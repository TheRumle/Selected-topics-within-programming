//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_SYMBOL_TABLE_H
#define LAMBDAS_SYMBOL_TABLE_H

#include <map>
#include <stdexcept>
#include <optional>
#include <unordered_map>
#include <string>
template<typename T>
    class symbol_table{
        std::unordered_map<std::string, T> table;

    public:
        void storeOrUpdate(const std::string &symbol, T object) {
            const auto& found = table.find(symbol);
            if(found != table.end()){
                (*found).second = object;
            } else{
                store(symbol, object);
            }
        }
        
        void store(const std::string &symbol, T object){
            table.emplace(symbol, object);
        }
        
        /// Updates the storage if the value exists else does nothing.
        /// \param symbol 
        /// \param object 
        void update(const std::string &symbol, T object){
            const auto& found = table.find(symbol);
            if(found != table.end()){
                (*found).second = object;
            }
        }

        std::optional<T> tryGetValue(const std::string symbol) {
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


#endif  // LAMBDAS_SYMBOL_TABLE_H
