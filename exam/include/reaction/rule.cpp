#include <vector>
#include "agents.h"
#include "rule.h"
//
// Created by rasmus on 5/26/2023.
//

Rule create(const std::vector<Agent>& reactants, const std::vector<Agent>& products) {
    return Rule(reactants, products);
}
void Rule::produce_to_state(symbol_table<std::string,double>& state)
{
    for (auto& product : products) {
        // The products are added to the state
        try{
            const auto& previous = state.lookup(product.name);
            state.store(product.name, previous+product.volume);
        } catch (const std::invalid_argument& e) {
            state.store(product.name, product.volume); 
        }
    }
}
void Rule::consume_from_state(symbol_table<std::string, double >& state)
{
    for (const auto& reactant : reactants) {
        const auto& previous = state.lookup(reactant.name);
        state.store(reactant.name, previous-reactant.volume);
    }
}
Rule LHS::operator>>=(const RHS& rhs) {
    return create(this->reactants, rhs.products);
}
