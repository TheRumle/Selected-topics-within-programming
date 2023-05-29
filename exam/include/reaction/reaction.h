﻿//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H

#include <utility>
#include "constructionRules.h"
#include "memory"
#include "symbol_table/reaction_table.h"
#include "agents.h"

using namespace ReactionCreation;
class reaction
{
public:
    // Default constructor
    reaction() = default;
    
    // Copy constructor
    reaction(const reaction& other) = default;
    
    // Move constructor
    reaction(reaction&& other) noexcept
        : lambda(std::move(other.lambda)),
        consumptions(std::move(other.consumptions)),
        productionActions(std::move(other.productionActions))
    {
    }
    
    // Constructor with arguments
    reaction(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda)
        : lambda(lambda),
        consumptions(reactants),
        productionActions(products)
    {
    }
    
    // Copy assignment operator
    reaction& operator=(const reaction& rhs) = default;
    
    // Move assignment operator
    reaction& operator=(reaction&& other) noexcept
    {
        if (this != &other) {
            lambda = std::move(other.lambda);
            consumptions = std::move(other.consumptions);
            productionActions = std::move(other.productionActions);
        }
        return *this;
    }
    
    [[nodiscard]] double compute_delay() const;
    [[nodiscard]] bool canBeSatisfied();
    [[nodiscard]] double getLambda(){return lambda;};
    inline void operator()() {
        consume_from_state();
        produce_to_state();
    }
    
    friend std::ostream & operator << (std::ostream& s, const reaction& value);
    const std::vector<AgentConsumption>& getConsumptions() const;
    const std::vector<AgentProduction>& getProductionActions() const;

private:
    double lambda;
    std::vector<AgentConsumption> consumptions{};
    std::vector<AgentProduction> productionActions{};
    
    void consume_from_state();
    void produce_to_state();
    friend reaction create(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda);
};


#endif  // LAMBDAS_CONSTRUCTIONRULES_H
