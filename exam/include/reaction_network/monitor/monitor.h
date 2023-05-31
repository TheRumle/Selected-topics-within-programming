//
// Created by rasmus on 5/30/2023.
//

#ifndef EXAM2023_MONITOR_H
#define EXAM2023_MONITOR_H

#include "reaction_network/reactionNetwork.h"

struct Monitor
{
private:
    symbol_table<double, ReactionNetwork::state> _observations;
protected:
    inline void addObservationVector(double time, 
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
        this->addObservationVector(time, copies);
    }
};


class MaxAgentValueMonitor : public Monitor
{
    symbol_table<std::string, double> store{};
public:
    
    void handleStateChange(double time, const ReactionNetwork::state &state) override {
        for (const auto& agent : state) {
            const auto prev = store.getValue(agent->getAgentName());
            
            if (!prev.has_value()){
                store.store(agent->getAgentName(), agent->getTotalAmountAgent());
                continue ;
            }

            if (prev.value() < agent->getTotalAmountAgent()){ 
                store.update(agent->getAgentName(), agent->getTotalAmountAgent());   
            }
        }
    }

    std::vector <std::pair<std::string, double>> getObservedValues(){
        return store.toPairVector();
    }
};


#endif  // EXAM2023_MONITOR_H
