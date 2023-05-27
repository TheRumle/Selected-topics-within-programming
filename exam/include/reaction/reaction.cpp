//
// Created by rasmus on 5/26/2023.
//

#include "reaction.h"


bool reaction::canBeSatisfied(Rule::state& state)
{
    for (const auto& reactant : this->rule.getReactants()){
        auto foundResult = state.tryGetValue(reactant.name);
        if (!foundResult.has_value() || foundResult < reactant.volume) 
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

double reaction::compute_delay(Rule::state& state)
{
    auto lambdaK = 1.0;
    const auto& reactants = this->rule.getReactants();
    for (auto& agent : reactants){
        lambdaK *= state.tryGetValue(agent.name).value();
    }

    auto res = get_distribution(lambdaK * lambda);
    return res;
}
