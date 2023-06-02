//
// Created by rasmus on 5/26/2023.
//

#include <random>
#include "reaction.h"

bool Reaction::canBeSatisfied() const
{
    return std::all_of(consumptions.begin(), consumptions.end(), [](const AgentConsumption& consumptionAction){
        return consumptionAction.canBePerformed(); 
    });
}

double Reaction::compute_delay() const
{
    auto product = 1.0;
    for (const auto& consumptionAction : consumptions){
        product *= consumptionAction.getAgentAmount();
    }

    if (product == 0) return 0;
    
    std::exponential_distribution<> exponentialDistribution(product * lambda);
    std::random_device rd;
    std::mt19937 generator(rd());
    auto val =  std::move(exponentialDistribution(generator));
    return val;
}
void Reaction::produce_to_state()
{
    for (auto& product : productionActions) {
        product();
    }
}
void Reaction::consume_from_state()
{
    for (const auto& reactant : consumptions) {
       reactant.operator()();
    }
}


std::ostream& operator<<(std::ostream& s, const Reaction& value)
{
    s <<"{";
    for (const auto& r : value.consumptions){
        s << r;
    }
    s << " ----> ";
    for (const auto& p : value.productionActions)
        s << p << " ";
    s << "}";
    return s;
}
const std::vector<AgentConsumption>& Reaction::getConsumptions() const { return consumptions; }
const std::vector<AgentProduction>& Reaction::getProductionActions() const { return productionActions; }
