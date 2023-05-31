//
// Created by rasmus on 5/30/2023.
//

#include "monitor.h"
void MaxAgentValueMonitor::handleStateChange(double time, const ReactionNetwork::state& state)
{
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
void AllStateCopyMonitor::handleStateChange(double time, const ReactionNetwork::state& state)
{
    ReactionNetwork::state copies;
    for (const auto& agent : state)
    {
        const Agent copy = *agent;
        copies.emplace_back(std::make_shared<const Agent>(copy));
    }
    this->addObservationVector(time, copies);
}
