//
// Created by rasmus on 5/30/2023.
//

#include "monitor.h"
void MaxAgentValueMonitor::updateIfMoreAgent(const std::shared_ptr<const Agent>& agent)
{
    const auto& found = maxAgents.getValue(agent);
    if(!found.has_value()) {
        maxAgents.store(agent, agent->getTotalAmountAgent());
        return;
    }

    const auto oldAmount = found.value();
    const auto newAmount = agent->getTotalAmountAgent();

    if (oldAmount < newAmount){
        maxAgents.update(agent, agent->getTotalAmountAgent());
    }
}
