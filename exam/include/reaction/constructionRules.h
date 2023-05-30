//
// Created by rasmus on 5/26/2023.
//

/**
 * 1. Use operator overloading to support the Reaction Reaction typesetting directly in C++ code. 
 * This could be done by overloading -, + and cout for consumptions. overload () for the ReactionNetwork
 * 2. Pretty print for ReactionNetwork
 * 
 */


#ifndef EXAM2023_CONSTRUCTIONRULES_H
#define EXAM2023_CONSTRUCTIONRULES_H

#include <memory>
#include <vector>
#include "agents.h"
#include "agentOperations.h"

class Reaction;
namespace ReactionCreation{
    using prod_init = std::initializer_list<AgentProduction>;
    using cons_init = std::initializer_list<AgentConsumption>;
    
    
    struct RHS {
        RHS(const prod_init & products, double rate) : products(products), rate(rate) {}
        const std::vector<AgentProduction> products{};
        const double rate{};
    };


    struct LHS {
        const std::vector<AgentConsumption> reactants{};
        LHS(const cons_init & reactants) : reactants(reactants) {}
        LHS(std::vector<AgentConsumption>& reactants) : reactants(reactants) {}
        Reaction operator>>=(const RHS& rhs);
    };
}



#endif  // EXAM2023_CONSTRUCTIONRULES_H
