//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H

#include <utility>

#include "rule.h"
struct reaction
{
    const double lambda;
    Rule rule;
    reaction(reaction const &reaction) = default;
    reaction(reaction& other) = default;
    reaction(Rule& rule, const double lambda): lambda(lambda), rule(rule) {}
    reaction(Rule  rule, double lambda): lambda(lambda), rule(std::move(rule)){}
    
    
    reaction operator= (reaction other){
        return reaction(other);
    }
    
    [[nodiscard]] double compute_delay(const symbol_table<std::string, Agent>& state) const;
    [[nodiscard]] bool canBeSatisfied(const symbol_table<std::string, Agent>& state)const;
    inline void operator()(symbol_table<std::string, Agent>& state){
        this->rule(state);
    }
};


#endif  // LAMBDAS_REACTION_H
