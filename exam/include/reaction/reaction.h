﻿//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H

#include <utility>
#include "construction_rules.h"
class reaction
{
public:
    using state = symbol_table<double>;
    
    reaction(reaction const &reaction) = default;
    
    reaction(reaction& other) = default;
    
    reaction(const LHS& lhs, const RHS& rhs, double lambda)
        : lambda(lambda), reactants(lhs.reactants), products(rhs.products){}
    
    reaction(const std::initializer_list<Agent>& lhs, const std::initializer_list<Agent>& rhs, double lambda)
        : lambda(lambda), reactants(lhs),products(rhs){}
    
    //Move assignment
    reaction operator=(reaction&& other) noexcept{
        this->products = std::move(other.products);
        this->reactants = std::move(other.reactants);
        this->lambda = other.lambda;
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
    std::vector<Agent> reactants{};
    std::vector<Agent> products{};
    reaction(const std::vector<Agent>& reactants, const std::vector<Agent>& products, double lambda)
        : reactants(reactants), products(products), lambda(lambda) {}
    
    void consume_from_state(state& state);
    void produce_to_state(state& state);
    friend reaction create(const std::vector<Agent>& reactants, const std::vector<Agent>& products, double lambda);
};


#endif  // LAMBDAS_CONSTRUCTION_RULES_H
