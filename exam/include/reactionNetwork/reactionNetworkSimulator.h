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

    std::vector<std::shared_ptr<const Agent>> stochasticSimulation(double endTime);
    
public:
    using state = std::vector<std::shared_ptr<const Agent>>;
    ReactionNetworkSimulator(ReactionNetwork& network) : network(network)
    {
    }
    
    ReactionNetworkSimulator(ReactionNetwork&& network): network(std::move(network))
    {
    }

    
    void operator()(double endTime){ 
        stochasticSimulation(endTime);
    }
    
    //REQ 7
    template <MonitorConcept TMonitor>
    void operator()(double endTime, TMonitor& m){ //Must be lvalue - no monitor if monitor-results won't be used
        m.handleStateChange(time, stochasticSimulation(endTime));
    }
    
    const ReactionNetwork& getNetwork() const;
};

#endif  // EXAM2023_REACTIONNETWORKSIMULATOR_H
