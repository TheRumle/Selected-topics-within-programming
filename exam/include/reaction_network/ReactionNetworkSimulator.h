//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_REACTIONNETWORKSIMULATOR_H
#define LAMBDAS_REACTIONNETWORKSIMULATOR_H

#include <vector>
#include "reaction/agents.h"
#include "reaction/reaction.h"
#include "ReactionNetwork.h"
class ReactionNetworkSimulator
{
    using state_history = symbol_table<double, std::vector<Agent>>;
    const std::vector<std::shared_ptr<Agent>> agents;
    double time = 0.0;
    state_history stateHistory{};
    ReactionNetwork network;
    
    std::vector<Agent> copy_agent_state(){
        std::vector<Agent> found{};
        for (const auto& reaction : agents) {
            Agent agent = *reaction.get(); //copy the state_history of the agent
            found.emplace_back(std::move(agent));
        }
        return found;
    }
    
    void addState() {
        stateHistory.store(time, copy_agent_state());
    }
    
    std::pair<reaction, double> findFastestReactionTime(){
        std::vector<std::pair<reaction, double>> validReactionTimes{};
        for (auto& reaction : network) {
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

        return validReactionTimes.front();
    }
    
    friend std::ostream & operator << (std::ostream& s, const ReactionNetworkSimulator& value);

public:
    ReactionNetworkSimulator(ReactionNetwork& network, const std::initializer_list<std::shared_ptr<Agent>>& agents)
        : agents(agents.begin(), agents.end()), network(network)
    {
        const std::vector<Agent> val = copy_agent_state();
        stateHistory.store(time, val);
    }
    ReactionNetworkSimulator(ReactionNetwork& network, const std::vector<std::shared_ptr<Agent>>& agents)
        : agents(agents.begin(), agents.end()), network(network)
    {
        const std::vector<Agent> val = copy_agent_state();
        stateHistory.store(time, val);
    }
    
    void operator()(double endTime){
        while (time < endTime){
            std::vector<std::pair<reaction&, double>> validReactionTimes{};
            for (auto& reaction : network) {
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
            if (validReactionTimes.empty())
                return ; 
            
            time += validReactionTimes.front().second;
            validReactionTimes.front().first.operator()();
            this->addState();
        }
            std::cout << *this;
    }
    const state_history& getStateHistory() const;
    const std::vector<std::shared_ptr<Agent>>& getAgents() const;
};

#endif  // LAMBDAS_REACTIONNETWORKSIMULATOR_H
