//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H

#include <utility>
#include "construction_rules.h"
#include "memory"
#include "symbol_table/reaction_table.h"

using namespace ReactionCreation;
class reaction
{
public:
    reaction(reaction const &reaction) = default;
    reaction(reaction& other) = default;
    reaction(reaction&& other): 
        lambda(std::move(other.lambda)),
        consumptions(std::move(other.consumptions)),
        productionActions(std::move(other.productionActions)){}
    ~reaction()= default;;
    
    
    reaction(const LHS& lhs, const RHS& rhs, double lambda)
        : lambda(lambda), consumptions(lhs.reactants), productionActions(rhs.products){}
    
    reaction(const std::initializer_list<AgentConsumption>& lhs, const std::initializer_list<AgentProduction>& rhs, double lambda)
        : lambda(lambda),
        consumptions(lhs), productionActions(rhs){}
    
    //Move assignment
    reaction& operator=(reaction&& other) noexcept{
        this->productionActions = std::move(other.productionActions);
        this->consumptions = std::move(other.consumptions);
        this->lambda = other.lambda;
        return *this;
    }
    reaction& operator=(const reaction& rhs) noexcept{
        if (&rhs != this) {
            this->consumptions = rhs.consumptions;
            this->productionActions = rhs.productionActions;
            this->lambda = rhs.lambda;
        }
        return *this;
    }
    
    [[nodiscard]] double compute_delay();
    [[nodiscard]] bool canBeSatisfied();
    inline void operator()() {
        consume_from_state();
        produce_to_state();
    }
    
    friend std::ostream & operator << (std::ostream& s, const reaction& value);
    
private:
    double lambda;
    std::vector<AgentConsumption> consumptions{};
    std::vector<AgentProduction> productionActions{};
    
    reaction(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda)
        : lambda(lambda),
        consumptions(reactants), productionActions(products) {}
    
    void consume_from_state();
    void produce_to_state();
    friend reaction create(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda);
};


#endif  // LAMBDAS_CONSTRUCTION_RULES_H
