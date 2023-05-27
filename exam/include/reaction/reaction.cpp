//
// Created by rasmus on 5/26/2023.
//

#include <random>
#include "reaction.h"

bool reaction::canBeSatisfied(reaction::state& state)
{
    for (const auto& reactant : consumptions){
        auto foundResult = state.tryGetValue(reactant.name);
        if (!foundResult.has_value() || foundResult.value() < reactant.amount) 
            return false;
    }
    return true;
}

double reaction::compute_delay(reaction::state& state)
{
    auto product = 1.0;
    for (const auto& agent : consumptions){    
        product *= state.tryGetValue(agent.name).value();
    }

    if (product == 0) return 0;
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<> exponentialDistribution(product * lambda);
    auto val =  exponentialDistribution(generator);
    return val;
}


reaction create(const std::vector<AgentConsumption>& reactants,
                const std::vector<AgentProduction>& products,
                double lambda) {
    return {reactants, products, lambda};
}

void reaction::produce_to_state(state& state)
{
    for (auto& product : productions) {
        const auto& tableResult = state.tryGetValue(product.name);
        if (tableResult.has_value()){
            auto val = tableResult.value();
            state.storeOrUpdate(product.name, product.amount + val);
        } else{
            state.storeOrUpdate(product.name, product.amount);
        }

    }
}
void reaction::consume_from_state(state& state)
{
    for (const auto& reactant : consumptions) {
        const auto& previous = state.tryGetValue(reactant.name);
        state.storeOrUpdate(reactant.name, previous.value() - reactant.amount);
    }
}
reaction LHS::operator>>=(const RHS& rhs) {
    return create(this->reactants, rhs.products, rhs.rate);
}

std::ostream& operator<<(std::ostream& s, const reaction& value)
{
    s <<"{ ";
    for (const auto& r : value.consumptions){
        s << r << " ";
    }
    s << " ----> ";
    for (const auto& p : value.productions)
        s << p << " ";
    s << "}\n  ";
    return s;
}
