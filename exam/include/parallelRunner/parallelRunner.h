//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_PARALLELRUNNER_H
#define LAMBDAS_PARALLELRUNNER_H
#include "reaction_network/reactionNetworkSimulator.h"
#include <future>

class ParallelSimulationRunner
{
    using factoryFunction = std::function<ReactionNetworkSimulator()>;

    void run(const factoryFunction& factory, int nThreads, double maxTime)
    {
        std::vector<std::future<void>> simulationFutures;
        simulationFutures.reserve(nThreads);

        for (int i = 0; i < nThreads; ++i) {
            ReactionNetworkSimulator simulator = factory();
            simulationFutures.emplace_back(
                std::async(std::launch::async, 
                           [&simulator, maxTime]() { simulator.operator()(maxTime); })
                );
        }
    }
};


#endif  // LAMBDAS_PARALLELRUNNER_H
