//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTIONNETWORK_H
#define LAMBDAS_REACTIONNETWORK_H

#include <functional>
#include <iostream>
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"


class ReactionNetwork
{
    using state_history = symbol_table<double, std::vector<Agent>>;
private:
    double time = 0.0;
    std::vector<reaction> reactions;
    
public:
    
    ReactionNetwork(const std::initializer_list<reaction>& reactions): reactions(reactions)
            {
        
            }; 
    friend std::ostream & operator << (std::ostream& s, const ReactionNetwork& value);
    
    auto begin() { return reactions.begin(); }
    auto end() { return reactions.end(); }
    auto begin() const { return reactions.begin(); }
    auto end() const { return reactions.end(); }
};


#endif  // LAMBDAS_REACTIONNETWORK_H
