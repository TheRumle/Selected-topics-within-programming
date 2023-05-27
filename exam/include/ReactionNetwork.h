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
    const std::vector<std::shared_ptr<Agent>> agents;

    
    std::vector<Agent> copy_agent_state(){
        std::vector<Agent> found{};
        for (const auto& reaction : agents) {
            Agent agent = *reaction.get(); //copy the state_history of the agent
            found.emplace_back(std::move(agent));
        }
        return found;
    }

public:
    std::vector<reaction> reactions;
    state_history stateHistory;

    ReactionNetwork(const std::initializer_list<reaction>& reactions, const std::initializer_list<std::shared_ptr<Agent>>& agents)
        : agents(agents.begin(), agents.end()), reactions(reactions)
    {
        std::vector<Agent> val = copy_agent_state();
        stateHistory.store(time, val);
    };
    
    friend std::ostream & operator << (std::ostream& s, const ReactionNetwork& value);
    inline void print(const ReactionNetwork& s){
        std::cout << s;
    }

    void addState() { stateHistory.store(time, copy_agent_state());}
    
    void operator()(double endTime){
        while (time < endTime){
            std::vector<std::pair<reaction, double>> validReactionTimes{};
            
            for (auto& reaction :reactions) {
                if (reaction.canBeSatisfied())
                    validReactionTimes.emplace_back(reaction, reaction.compute_delay());
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
            addState();
            fastestReaction.first.operator()();
        }
        print(*this);
    }
    
};

#endif  // LAMBDAS_REACTIONNETWORK_H
