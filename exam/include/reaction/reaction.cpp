//
// Created by rasmus on 5/26/2023.
//

#include <random>
#include "reaction.h"

bool reaction::canBeSatisfied(reaction::state& state)
{
    for (const auto& reactant : consumptions){
        auto foundResult = state.tryGetValue(reactant.getName());
        if (!foundResult.has_value() || foundResult.value() < reactant.getAmount()) 
            return false;
    }
    return true;
}

double reaction::compute_delay(reaction::state& state)
{
    auto product = 1.0;
    for (const auto& agent : consumptions){    
        product *= state.tryGetValue(agent.getName()).value();
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
        const auto& tableResult = state.tryGetValue(product.getName());
        if (tableResult.has_value()){
            auto val = tableResult.value();
            state.storeOrUpdate(product.getName(), product.getAmount() + val);
        } else{
            state.storeOrUpdate(product.getName(), product.getAmount());
        }

    }
}
void reaction::consume_from_state(state& state)
{
    for (const auto& reactant : consumptions) {
        
        
        const auto& previous = state.tryGetValue(reactant.getName());
        state.storeOrUpdate(reactant.getName(), previous.value() - reactant.getAmount());
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
