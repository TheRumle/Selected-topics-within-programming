#include <vector>
#include "agents.h"
#include "rule.h"
//
// Created by rasmus on 5/26/2023.
//

Rule create(const std::vector<Agent>& reactants, const std::vector<Agent>& products) {
    return {reactants, products};
}

void Rule::produce_to_state(state& state)
{
    for (auto& product : products) {
        const auto& tableResult = state.tryGetValue(product.name);
        if (tableResult.has_value()){
            auto val = tableResult.value();
            state.storeOrUpdate(product.name, product.volume + val);
        } else{
            state.storeOrUpdate(product.name, product.volume);
        }

    }
}
void Rule::consume_from_state(state& state)
{
    for (const Agent& reactant : reactants) {
        const auto& previous = state.tryGetValue(reactant.name);
        state.storeOrUpdate(reactant.name, previous.value() - reactant.volume);
    }
}
Rule LHS::operator>>=(const RHS& rhs) {
    return create(this->reactants, rhs.products);
}
