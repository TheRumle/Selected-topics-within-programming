//
// Created by rasmus on 5/30/2023.
//

#ifndef LAMBDAS_MONITOR_H
#define LAMBDAS_MONITOR_H

#include "reaction_network/reactionNetwork.h"

struct Monitor
{
private:
    symbol_table<double, ReactionNetwork::state> _observations;
protected:
    void addObservation(double time,
                        const ReactionNetwork::state& agents,
                        const std::function<bool(const std::shared_ptr<const Agent>&)>& filter) {
        
        ReactionNetwork::state filtered{};
        for (const auto& agentP : agents) {
            if (filter(agentP)){
                filtered.emplace_back(agentP);
            }
        }
        
        for (const auto& element: filtered) {
            _observations.storeOrUpdate(time,filtered);
        }
    }
    
    inline void addObservation(double time, 
                               const ReactionNetwork::state& agents) {
        _observations.storeOrUpdate(time,agents);
    }
    
    
    
public:
    using observations = std::vector<std::pair<double, std::vector<std::shared_ptr<const Agent>>>>;
    std::vector<std::pair<double, std::vector<std::shared_ptr<const Agent>>>> getObservations() const {
        return _observations.toPairVector();
    }
    
    virtual void handleStateChange(double time, const ReactionNetwork::state& state) = 0;
    virtual ~Monitor() = default;
};

class AllStateCopyMonitor : public Monitor
{
                                        
public:
    void handleStateChange(double time, const ReactionNetwork::state &state) override {
        ReactionNetwork::state copies;
        for (const auto& agent : state)
        {
            const Agent copy = *agent;
            copies.emplace_back(std::make_shared<const Agent>(copy));
        }
        this->addObservation(time,copies);
    }
};


class MaxAgentValueMonitor : public Monitor
{
    symbol_table<std::shared_ptr<const Agent>, double> maxAgents{};
    void updateIfMoreAgent(const std::shared_ptr<const Agent>& agent);
public:
    void handleStateChange(double time, const ReactionNetwork::state &state) override {
        for (const auto& agent : state)
            this->updateIfMoreAgent(agent);
        
    }
    
    std::vector<std::pair<Agent, double>> getMaxValues() const {
        std::vector<std::pair<Agent, double>> maxValues;
        for (const auto& entry : maxAgents) {
            const std::shared_ptr<const Agent>& agent = entry.first; //copy assignment!
            double maxValue = entry.second;
            maxValues.emplace_back(*agent, maxValue); 
        }
        return maxValues;
    };
    
    
};


#endif  // LAMBDAS_MONITOR_H
