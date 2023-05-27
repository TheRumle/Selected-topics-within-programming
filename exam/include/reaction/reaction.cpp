//
// Created by rasmus on 5/26/2023.
//

#include "reaction.h"


bool reaction::canBeSatisfied(symbol_table<std::string, double>& state)
{
    for (auto& reactant : this->rule.reactants){
        auto amount = state.lookup(reactant.name);
        if (amount < reactant.volume)
            return false;
    }
    return true;
}


[[nodiscard]] double get_distribution(const double lambdaK) {
    if (lambdaK == 0) return 0;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<> exponentialDistribution(lambdaK);
    return exponentialDistribution(generator);
}

double reaction::compute_delay(symbol_table<std::string, double>& state)
{
    auto lambdaK = 1.0;
    for (auto& agent : this->rule.reactants)
        lambdaK *= state.lookup(agent.name);

    auto res = get_distribution(lambdaK * lambda);
    return res;
}
