//
// Created by rasmus on 5/26/2023.
//

/**
 * 1. Use operator overloading to support the reaction reaction typesetting directly in C++ code. 
 * This could be done by overloading -, + and cout for reactants. overload () for the ReactionNetwork
 * 2. Pretty print for ReactionNetwork
 * 
 */


#ifndef LAMBDAS_CONSTRUCTION_RULES_H
#define LAMBDAS_CONSTRUCTION_RULES_H
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <random>
#include "agents.h"
#include "symbol_table/symbol_table.h"

//predeclare the reaction struct. 
// A reaction will consist of a RHS denoting the produce of the reaction and a RHS for that denotes what is required for the 
// reaction to be satisfied
struct reaction;
struct RHS {
    RHS(const std::vector<Agent>& products, double rate) :products(products), rate(rate) {}
    RHS(const std::initializer_list<Agent>& products, double rate) : products(products), rate(rate) {}
    
    const std::vector<Agent> products{};
    const double rate{};
};


struct LHS {
    const std::vector<Agent> reactants{};
    LHS(const std::initializer_list<Agent>& reactants) : reactants(reactants) {}
    reaction operator>>=(const RHS& rhs);
};



#endif  // LAMBDAS_CONSTRUCTION_RULES_H
