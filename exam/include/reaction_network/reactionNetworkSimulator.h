//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_REACTIONNETWORKSIMULATOR_H
#define LAMBDAS_REACTIONNETWORKSIMULATOR_H

#include <vector>
#include "reaction/agents.h"
#include "reaction/reaction.h"
#include "reactionNetwork.h"
class ReactionNetworkSimulator
{
public:
    using state_history = symbol_table<double, std::vector<Agent>>;
private:
    const std::vector<std::shared_ptr<Agent>> agents;
    double time = 0.0;
    state_history stateHistory{};
    ReactionNetwork network;
    
    const std::vector<Agent> copy_agent_state(){
        std::vector<Agent> found{};
        for (const auto& reaction : agents) {
            const Agent agent = *reaction; //copy the state_history of the agent
            found.emplace_back(std::move(agent));
        }
        return found;
    }
    
    void addState() {
        stateHistory.store(time, );
    }
    
    std::pair<Reaction, double> findFastestValidReaction(){
        std::vector<std::pair<Reaction, double>> validReactionTimes{};
        
        for (const auto& reaction : network) {
            if (reaction.canBeSatisfied())
                validReactionTimes.emplace_back(reaction, reaction.compute_delay());
        }
        
        std::sort(validReactionTimes.begin(), validReactionTimes.end(),
                  [](const std::pair<Reaction, double>& lhs, const std::pair<Reaction, double>& rhs)
                  {
            return lhs.second < rhs.second;
        });
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
    
    ReactionNetworkSimulator(ReactionNetwork&& network, const std::vector<std::shared_ptr<Agent>>& agents)
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
    
    ReactionNetworkSimulator(ReactionNetworkSimulator&& other) noexcept
        : agents(other.agents), network(std::move(other.network)), stateHistory(std::move(other.stateHistory))
    {
    }
    
    void operator()(double endTime,  std::function<void(const std::vector<Agent> stateChange)> stateMonitor){
        while (time < endTime){
            auto validReactionTimes = findFastestValidReaction();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
            
            
            
            
            std::vector<Agent> found{};
            for (const auto& reaction : agents) {
                const Agent agent = *reaction; //copy the state_history of the agent
                found.emplace_back(std::move(agent));
            }
            stateMonitor(found);
        }
        std::cout << *this;
    }
    
    void operator()(double endTime){
        while (time < endTime){
            auto validReactionTimes = findFastestValidReaction();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
            this->addState();
        }
    }
    
    const state_history& getStateHistory() const;
    const std::vector<std::shared_ptr<Agent>>& getAgents() const;
    const ReactionNetwork& getNetwork() const;
};

#endif  // LAMBDAS_REACTIONNETWORKSIMULATOR_H
