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
    std::map<const TKey, TValue&> state{};
    struct KV{
        TKey k;
        TValue v;
        KV(TKey k, TValue v): k(k), v(v) {}
        
    };
    
    void store( const TKey& key, TValue& value) {
        state.emplace(key, value);
    };
    
    
    TValue& lookup(const TKey& key) const{
        auto it = state.find(key);
        if (it == state.end())
            throw std::invalid_argument("Key was not contained in state");
        
        return (it->second);
    };
};



#endif  // LAMBDAS_SYMBOL_TABLE_H
