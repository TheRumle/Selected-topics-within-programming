#ifndef EXAM2023_SYMBOLTABLE_H
#define EXAM2023_SYMBOLTABLE_H

#include <map>
#include <stdexcept>
#include <optional>
#include <vector>

template<typename TKey, typename T>
class SymbolTable
{
    std::map<TKey, T> table;
    
public:
    std::optional<T> get(const TKey &symbol) noexcept {
        try {
            const auto it = table.find(symbol);
        
            if (it != table.end()) {
                return it->second;
            }
            return std::nullopt;
        } catch (const std::exception& any){
            return std::nullopt;
        }
    }
    
    void storeOrUpdate(const TKey &symbol, T object) {
        const auto& found = table.find(symbol);
        if(found != table.end()){
            (*found).second = object;
        } else{
            add(symbol, object);
        }
    }
    
    void add(const TKey & key, T item){
        if (table.contains(key))
            throw std::out_of_range("Duplicate key! ");
        
        table.emplace(key, item);
    }
    
    /// Updates the storage if the value exists else adds it.
    /// \param symbol 
    /// \param object 
    void update(const TKey &symbol, T object){
        const auto& found = table.find(symbol);
        if(found != table.end()){
            (*found).second = object;
        } else{
            this->add(symbol, object);
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
    
    std::vector<std::pair<TKey, T>> toPairVector() const {
        std::vector<std::pair<TKey, T>> res{};
        for (const auto& entry : this->table) {
            res.emplace_back(std::pair{entry.first, entry.second});
        }
        return res;
    }
    void remove(const TKey& key) {
        if (!this->table.contains(key)) 
            throw std::out_of_range("No element with that key is in add, so it cannot be removed");
        table.erase(key);
    }
};



#endif  // EXAM2023_SYMBOLTABLE_H
