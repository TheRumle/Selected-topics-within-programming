//
// Created by rasmus on 5/26/2023.
//

/**
 * 1. Use operator overloading to support the Rule Rule typesetting directly in C++ code. 
 * This could be done by overloading -, + and cout for reactants. overload () for the simulation
 * 2. Pretty print for simulation
 * 
 */


#ifndef LAMBDAS_RULE_H
#define LAMBDAS_RULE_H
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <random>
#include "agents.h"
#include "symbol_table/symbol_table.h"

//predeclare the rule struct. 
// A rule will consist of a RHS denoting the produce of the rule and a RHS for that denotes what is required for the 
// rule to be satisfied
struct Rule;
struct RHS {
    RHS(const std::vector<Agent>& products) : products(products) {}
    const std::vector<Agent> products{};
};


struct LHS {
    const std::vector<Agent> reactants{};
    LHS(const std::vector<Agent>& reactants) : reactants(reactants) {}
    Rule operator>>=(const RHS& rhs);
};

struct Rule
{
    //A rule can be applied to some state (symbol table) to modify it
    void operator()(symbol_table<std::string, Agent>& state) {
        consume_from_state(state);
        produce_to_state(state);
        for (const auto& r : products) {
            // For the state of the system, remove state
            auto state_agent = state.lookup(r.name);
            state_agent.volume += r.volume;
        }
    }

    const std::vector<Agent> reactants{};
    std::vector<Agent> products{};
private:
    Rule(const std::vector<Agent>& reactants, const std::vector<Agent>& products)
        : reactants(reactants), products(products) {}
    
    void consume_from_state(const symbol_table<std::string, Agent>& state) const;
    void produce_to_state(symbol_table<std::string, Agent>& state);
    friend Rule create(const std::vector<Agent>& reactants, const std::vector<Agent>& products);
};




#endif  // LAMBDAS_RULE_H
