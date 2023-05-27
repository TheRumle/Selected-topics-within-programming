//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_SYMBOL_TABLE_H
#define LAMBDAS_SYMBOL_TABLE_H

#include <map>
#include <stdexcept>
template<typename TKey, typename TValue>
struct symbol_table{
public:
    std::map<TKey, TValue> state{};
    
    void store( const TKey key, TValue value) {
        state[key] = value;
        
    };
    
    
    TValue& lookup(const TKey& key){
        auto it = state.find(key);
        if (it == state.end())
            throw std::invalid_argument("Key was not contained in state");
        TValue& res = (it->second);
        return res;
    };
};



#endif  // LAMBDAS_SYMBOL_TABLE_H
