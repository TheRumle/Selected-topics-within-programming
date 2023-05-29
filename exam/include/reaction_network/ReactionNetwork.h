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
    // Constructor taking an initializer list of reactions
    ReactionNetwork(const std::initializer_list<reaction>& reactions) : reactions(reactions)
    {
        
    }

    // Default constructor
    ReactionNetwork() = default;

    // Copy constructor
    ReactionNetwork(const ReactionNetwork& other) : time(other.time), reactions(other.reactions)
    {

    }

    // Move constructor
    ReactionNetwork(ReactionNetwork&& other) noexcept : time(std::move(other.time)), reactions(std::move(other.reactions))
    {

    }
    // Destructor
    ~ReactionNetwork() = default;

    // Copy assignment operator
    ReactionNetwork& operator=(const ReactionNetwork& other)
    {
        if (this != &other)
        {
            time = other.time;
            reactions = other.reactions;
        }
        return *this;
    }

    // Move assignment operator
    ReactionNetwork& operator=(ReactionNetwork&& other) noexcept
    {
        if (this != &other)
        {
            time = std::move(other.time);
            reactions = std::move(other.reactions);
        }
        return *this;
    }
    auto begin() { return reactions.begin(); }
    auto end() { return reactions.end(); }
    auto begin() const { return reactions.begin(); }
    auto end() const { return reactions.end(); }

    friend std::ostream& operator<<(std::ostream& s, const ReactionNetwork& value);
};



#endif  // LAMBDAS_REACTIONNETWORK_H
