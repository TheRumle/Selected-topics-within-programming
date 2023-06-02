#include <random>
#include "reaction.h"
#include "meta/agentConstraint.h"

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

    if (product == 0) return std::numeric_limits<double>::max();
    std::exponential_distribution<> exponentialDistribution(product * lambda);
    std::mt19937 generator(std::random_device {}());
    return exponentialDistribution(generator);
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

template <AgentActionConcept T>
void appendPlusSeparate(std::ostream& s, std::vector<T> value){
    for (size_t i = 0; i < value.size(); ++i) {
       s << value[i];
       if (i != value.size() - 1) {
           s << "+ ";
       }
    }
}

std::ostream& operator<<(std::ostream& s, const Reaction& value)
{
    s <<"{";
    appendPlusSeparate(s, value.consumptions);
    s << "----> ";
    appendPlusSeparate(s, value.productionActions);
    return s << "}";
}
const std::vector<AgentConsumption>& Reaction::getConsumptions() const { return consumptions; }
const std::vector<AgentProduction>& Reaction::getProductionActions() const { return productionActions; }
