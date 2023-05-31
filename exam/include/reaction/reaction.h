//
// Created by rasmus on 5/26/2023.
//

#ifndef EXAM2023_REACTION_H
#define EXAM2023_REACTION_H

#include <utility>
#include "constructionRules.h"
#include "memory"
#include "symbol_table/symbolTable.h"
#include "agents.h"

using namespace ReactionCreation;
class Reaction
{
public:
    // Default constructor
    Reaction():
        lambda(0),
        productionActions({}),
        consumptions({}){};

    
    // Constructor with arguments
    Reaction(const std::vector<AgentConsumption>& reactants,
             const std::vector<AgentProduction>& products,
             double lambda)
        : lambda(lambda),
        consumptions(reactants),
        productionActions(products)
    {
    }
    
    
    [[nodiscard]] double compute_delay() const;
    [[nodiscard]] bool canBeSatisfied() const;
    [[nodiscard]] double getLambda() const {return lambda;} ;
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
    friend Reaction create(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda);
};


#endif  // EXAM2023_CONSTRUCTIONRULES_H
