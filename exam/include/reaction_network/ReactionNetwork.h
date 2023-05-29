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
    
};

#endif  // LAMBDAS_REACTIONNETWORK_H
