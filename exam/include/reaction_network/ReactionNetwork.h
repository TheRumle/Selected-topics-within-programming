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
private:
    double time = 0.0;
    std::vector<reaction> reactions;
    
public:
    
    ReactionNetwork(const std::initializer_list<reaction>& reactions): reactions(reactions)
            {
        
            }; 
    
    auto begin() { return reactions.begin(); }
    auto end() { return reactions.end(); }
    auto begin() const { return reactions.begin(); }
    auto end() const { return reactions.end(); }
    friend std::ostream & operator << (std::ostream& s, const ReactionNetwork& value);
};


#endif  // LAMBDAS_REACTIONNETWORK_H
