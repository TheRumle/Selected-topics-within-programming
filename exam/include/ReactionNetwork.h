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

public:
    std::vector<reaction> reactions;
    reaction::state state;

    ReactionNetwork(const std::initializer_list<reaction>& reactions, reaction::state& agentValues):
        reactions(reactions), state(agentValues)
    {};
    friend std::ostream & operator << (std::ostream& s, const ReactionNetwork& value);
    inline void print(const ReactionNetwork& s, reaction& fastestReaction){
        std::cout << s << " by doing " << fastestReaction;
    }
    
    void operator()(double endTime){
        while (time < endTime){
            std::vector<std::pair<reaction, double>> validReactionTimes{};
            for (auto& reaction :reactions) {
                if (reaction.canBeSatisfied(state))
                    validReactionTimes.emplace_back(reaction, reaction.compute_delay(state));
            }
            
            for (auto it = validReactionTimes.begin(); it != validReactionTimes.end(); ++it) {
                for (auto innerIt = validReactionTimes.begin(); innerIt != validReactionTimes.end() - 1; ++innerIt) {
                    auto& lhs = *innerIt;
                    auto& rhs = *(innerIt + 1);
        
                    if (lhs.second > rhs.second) {
                        std::swap(lhs, rhs);
                    }
                }
            }

            
            auto& fastestReaction = validReactionTimes.front();
            time += fastestReaction.second;
            fastestReaction.first.operator()(state);
            print(*this, fastestReaction.first);
        }
    }
};

#endif  // LAMBDAS_REACTIONNETWORK_H
