//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_SIMULATIONMONITORS_H
#define LAMBDAS_SIMULATIONMONITORS_H

#include <vector>
#include "reaction/agents.h"
#include "symbol_table/symbolTable.h"
template<typename TKey, typename TValue>
class SimulationMonitor<TKey, TValue>
{
    symbol_table<TKey, std::vector<TValue>> states{};
    void onStateChange(std::vector<std::shared_ptr<Agent>> agents, ){}
    
    
};

#endif  // LAMBDAS_SIMULATIONMONITORS_H
