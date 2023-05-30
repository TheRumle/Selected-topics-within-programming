//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H

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
    Reaction() = default;
    
    // Copy constructor
    Reaction(const Reaction& other) = default;
    
    // Move constructor
    Reaction(Reaction&& other) noexcept
        : lambda(std::move(other.lambda)),
        consumptions(std::move(other.consumptions)),
        productionActions(std::move(other.productionActions))
    {
    }
    
    // Constructor with arguments
    Reaction(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda)
        : lambda(lambda),
        consumptions(reactants),
        productionActions(products)
    {
    }
    
    // Copy assignment operator
    Reaction& operator=(const Reaction& rhs) = default;
    
    // Move assignment operator
    Reaction& operator=(Reaction&& other) noexcept
    {
        if (this != &other) {
            lambda = std::move(other.lambda);
            consumptions = std::move(other.consumptions);
            productionActions = std::move(other.productionActions);
        }
        return *this;
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


#endif  // LAMBDAS_CONSTRUCTIONRULES_H
