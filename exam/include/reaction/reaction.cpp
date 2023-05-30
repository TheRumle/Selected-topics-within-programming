//
// Created by rasmus on 5/26/2023.
//

#include <random>
#include "reaction.h"

bool Reaction::canBeSatisfied() const
{
    for (const auto& consumptionAction : consumptions){
        if (!consumptionAction.canBePerformed()) return false;
    }
    return true;
}

double Reaction::compute_delay() const
{
    auto product = 1.0;
    for (const auto& consumptionAction : consumptions){
        product *= consumptionAction.getAgentAmount();
    }

    if (product == 0) return 1000000000000;
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<> exponentialDistribution(product * lambda);
    auto val =  exponentialDistribution(generator);
    return val;
}

Reaction create(const std::vector<AgentConsumption>& reactants,
                const std::vector<AgentProduction>& products,
                double lambda) {
    return {reactants, products, lambda};
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
Reaction LHS::operator>>=(const RHS& rhs) {
    return create(this->reactants, rhs.products, rhs.rate);
}

std::ostream& operator<<(std::ostream& s, const Reaction& value)
{
    s <<"";
    for (const auto& r : value.consumptions){
        s << r;
    }
    s << " ----> ";
    for (const auto& p : value.productionActions)
        s << p << " ";
    s << "";
    return s;
}
const std::vector<AgentConsumption>& Reaction::getConsumptions() const { return consumptions; }
const std::vector<AgentProduction>& Reaction::getProductionActions() const { return productionActions; }
