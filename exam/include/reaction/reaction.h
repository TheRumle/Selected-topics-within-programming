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
private:
public:
    using state = reaction_table<double>;

    reaction(reaction const &reaction) = default;
    reaction(reaction& other) = default;
    reaction(reaction&& other): 
        lambda(std::move(other.lambda)),
        consumptions(std::move(other.consumptions)),
        productions(std::move(other.productions)){}
    ~reaction()= default;;
    
    
    reaction(const LHS& lhs, const RHS& rhs, double lambda)
        : lambda(lambda), consumptions(lhs.reactants), productions(rhs.products){}
    
    reaction(const std::initializer_list<AgentConsumption>& lhs, const std::initializer_list<AgentProduction>& rhs, double lambda)
        : lambda(lambda),
        consumptions(lhs), productions(rhs){}
    
    //Move assignment
    reaction& operator=(reaction&& other) noexcept{
        this->productions = std::move(other.productions);
        this->consumptions = std::move(other.consumptions);
        this->lambda = other.lambda;
        return *this;
    }
    reaction& operator=(const reaction& rhs) noexcept{
        if (&rhs != this) {
            this->consumptions = rhs.consumptions;
            this->productions = rhs.productions;
            this->lambda = rhs.lambda;
        }
        return *this;
    }
    
    [[nodiscard]] double compute_delay(reaction::state& state);
    [[nodiscard]] bool canBeSatisfied(reaction::state& state);
    inline void operator()(state& state) {
        consume_from_state(state);
        produce_to_state(state);
    }
    
    friend std::ostream & operator << (std::ostream& s, const reaction& value);
    
private:
    double lambda;
    std::vector<AgentConsumption> consumptions{};
    std::vector<AgentProduction> productions{};
    
    reaction(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda)
        : lambda(lambda),
        consumptions(reactants), productions(products) {}
    
    void consume_from_state(state& state);
    void produce_to_state(state& state);
    friend reaction create(const std::vector<AgentConsumption>& reactants, const std::vector<AgentProduction>& products, double lambda);
};


#endif  // LAMBDAS_CONSTRUCTION_RULES_H
