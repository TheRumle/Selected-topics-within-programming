//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_REACTIONNETWORKSIMULATOR_H
#define LAMBDAS_REACTIONNETWORKSIMULATOR_H

#include <utility>
#include <vector>
#include "reaction/agents.h"
#include "reaction/reaction.h"
#include "reactionNetwork.h"
#include "meta/monitorConstraint.h"
#include "reaction_network/monitor/monitor.h"

class ReactionNetworkSimulator
{
public:
    using state = std::vector<std::shared_ptr<const Agent>>;

private:
    double time = 0.0;
    ReactionNetwork network{};
    const state agents{};
    
    
    std::pair<Reaction, double> findFastestValidReaction();

    std::pair<double,std::vector<std::shared_ptr<const Agent>>> executeSimulation(double endTime){
        while (time < endTime){
            auto validReactionTimes = findFastestValidReaction();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
        }
        return {time, this->agents};
    }
    
public:
    using changed_state = std::pair<double,state>;
    ReactionNetworkSimulator(ReactionNetwork& network)
        : network(network), agents(network.getAgents())
    {
    }

    
    ReactionNetworkSimulator(ReactionNetwork&& network)
        : agents(std::move(network.getAgents())), network(std::move(network))
    {
    }

    
    void operator()(double endTime){
        while (time < endTime){
            auto validReactionTimes = findFastestValidReaction();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
        }    
    }
    
    template <MonitorConcept TMonitor>
    void operator()(double endTime, TMonitor& m){
        while (time < endTime){
            auto validReactionTimes = findFastestValidReaction();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
            m.handleStateChange(time, this->agents);
        }
    }
    
    const ReactionNetwork& getNetwork() const;
};

#endif  // LAMBDAS_REACTIONNETWORKSIMULATOR_H
