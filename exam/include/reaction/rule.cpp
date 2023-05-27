#include <vector>
#include "agents.h"
#include "rule.h"
//
// Created by rasmus on 5/26/2023.
//

Rule create(const std::vector<Reactant>& reactants, const std::vector<Product>& products) {
    return Rule(reactants, products);
}
void Rule::produce_to_state(symbol_table<std::string, Agent>& state)
{
    for (auto& product : products) {
        // The products are added to the state
        try{
            auto state_agent = state.lookup(product.name);
            state_agent.volume += product.volume;
        } catch (const std::invalid_argument& e) {
            state.store(product.name, product); 
        }
    }
}
void Rule::consume_from_state(const symbol_table<std::string, Agent>& state) const
{
    for (const auto& reactant : reactants) {
        // For the reactants are consumed from the state
        auto& state_agent = state.lookup(reactant.name);
        state_agent.volume -= reactant.volume;
    }
}
Rule LHS::operator>>=(const RHS& rhs) {
    return create(this->reactants, rhs.products);
}
