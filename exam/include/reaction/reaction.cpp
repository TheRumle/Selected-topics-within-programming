//
// Created by rasmus on 5/26/2023.
//

#include "reaction.h"

bool reaction::canBeSatisfied(reaction::state& state)
{
    for (const auto& reactant : reactants){
        auto foundResult = state.tryGetValue(reactant.name);
        if (!foundResult.has_value() || foundResult < reactant.volume) 
            return false;
    }
    return true;
}

double reaction::compute_delay(reaction::state& state)
{
    auto product = 1.0;
    for (const auto& agent : reactants){
        product *= state.tryGetValue(agent.name).value();
    }

    if (product == 0) return std::numeric_limits<double>::max();
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<> exponentialDistribution(product * lambda);
    auto val =  exponentialDistribution(generator);
    return val;
}


reaction create(const std::vector<Agent>& reactants, const std::vector<Agent>& products, double lambda) {
    return {reactants, products, lambda};
}

void reaction::produce_to_state(state& state)
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
void reaction::consume_from_state(state& state)
{
    for (const Agent& reactant : reactants) {
        const auto& previous = state.tryGetValue(reactant.name);
        state.storeOrUpdate(reactant.name, previous.value() - reactant.volume);
    }
}
reaction LHS::operator>>=(const RHS& rhs) {
    return create(this->reactants, rhs.products, rhs.rate);
}

std::ostream& operator<<(std::ostream& s, const reaction& value)
{
    s <<"{ ";
    for (const auto& r : value.reactants){
        s << r << " ";
    }
    s << " ----> ";
    for (const auto& p : value.products)
        s << p << " ";
    s << "}\n  ";
    return s;
}
