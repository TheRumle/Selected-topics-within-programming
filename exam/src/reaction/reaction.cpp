//
// Created by rasmus on 5/26/2023.
//

#include "reaction.h"


bool reaction::canBeSatisfied(const symbol_table<std::string, Agent>& state) const
{
    for (const auto& reactant : this->rule.reactants){
        const auto currentR = state.lookup(reactant.name);
        auto currentValue = currentR.volume;
        
        if (currentValue < reactant.volume)
            return false;
    }
    return true;
}


[[nodiscard]] double get_distribution(const double lambdaK) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<> exponentialDistribution(lambdaK);
    return exponentialDistribution(generator);
};

double reaction::compute_delay(const symbol_table<std::string, Agent>& state) const
{
    auto lambdaK = 1.0;
    for (const auto& agent : this->rule.reactants)
        lambdaK *= state.lookup(agent.name).volume;

    return get_distribution(lambdaK * lambda);
}
