#ifndef EXAM2023_REACTION_H
#define EXAM2023_REACTION_H

#include <utility>
#include "memory"
#include "symbolTable/symbolTable.h"
#include "agents.h"
#include "agentOperations.h"

class Reaction
{
public:
    // Default constructor
    Reaction():
        lambda(0),
        productionActions({}),
        consumptions({}){};
    
    // A + C >>= C + B, lambda
    Reaction(const Agent::P_Container::Rule& rule, double lambda)
        : lambda(lambda), 
        consumptions(AgentAction::FromRule<AgentConsumption>(rule.lhs)),
        productionActions(AgentProduction::FromRule<AgentProduction>(rule.rhs))
    {}

    
    // Constructor with arguments
    Reaction(const std::vector<AgentConsumption>& reactants,
             const std::vector<AgentProduction>& products,
             double lambda)
        : lambda(lambda),
        consumptions(reactants),
        productionActions(products)
    {
    }
    
    
    double compute_delay() const;
    bool canBeSatisfied() const;
    double getLambda() const {return lambda;} ;
    inline void operator()() {
        consume_from_state();
        produce_to_state();
    }
    
    friend std::ostream & operator << (std::ostream& s, const Reaction& value);
    const std::vector<AgentConsumption>& getConsumptions() const;
    const std::vector<AgentProduction>& getProductionActions() const;

private:
    double lambda;
    std::vector<AgentConsumption> consumptions{};
    std::vector<AgentProduction> productionActions{};
    
    void consume_from_state();
    void produce_to_state();
};


#endif  // EXAM2023_CONSTRUCTIONRULES_H
