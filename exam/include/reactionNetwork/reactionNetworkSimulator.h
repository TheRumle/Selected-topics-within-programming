//
// Created by rasmus on 5/29/2023.
//

#ifndef EXAM2023_REACTIONNETWORKSIMULATOR_H
#define EXAM2023_REACTIONNETWORKSIMULATOR_H

#include <utility>
#include <vector>
#include "reaction/agents.h"
#include "reaction/reaction.h"
#include "reactionNetwork.h"
#include "meta/monitorConstraint.h"
#include "reactionNetwork/monitor/monitor.h"

class ReactionNetworkSimulator
{
    double time = 0.0;
    ReactionNetwork network{};
    std::optional<std::pair<Reaction, double>>  findFastestValidReaction();
public:
    using state = std::vector<std::shared_ptr<const Agent>>;
    ReactionNetworkSimulator(ReactionNetwork& network) : network(network)
    {
    }
    
    ReactionNetworkSimulator(ReactionNetwork&& network): network(std::move(network))
    {
    }

    
    void operator()(double endTime){
        while (time < endTime){
            const auto res = findFastestValidReaction();
            if (!res.has_value())
                break ;
        
            auto validReactionTimes = res.value();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
        }    
    }
    
    template <MonitorConcept TMonitor>
    void operator()(double endTime, TMonitor& m){
        while (time < endTime){
            const auto res = findFastestValidReaction();
            if (!res.has_value())
                break ;
            
            auto validReactionTimes = res.value();
            time += validReactionTimes.second;
            validReactionTimes.first.operator()();
            m.handleStateChange(time, network.getAgents());
        }
    }
    
    const ReactionNetwork& getNetwork() const;
};

#endif  // EXAM2023_REACTIONNETWORKSIMULATOR_H
