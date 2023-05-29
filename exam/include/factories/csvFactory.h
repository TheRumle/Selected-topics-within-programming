//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_CSVFACTORY_H
#define LAMBDAS_CSVFACTORY_H
#include "reaction_network/ReactionNetworkSimulator.h"
struct CsvFactory {
    static std::string convertToCsvString(const ReactionNetworkSimulator& simulation, char separator) {
        std::stringstream outStream; 
        
        const auto& agents = simulation.getAgents();
        outStream << "Time" << separator;
        const size_t numAgents = agents.size();
        for (size_t i = 0; i < numAgents; ++i) {
            const auto& agent = agents[i];
            outStream << agent->getAgentName();
            if (i != numAgents - 1) {
                outStream << separator;
            }
        }
        
        outStream << "\n";
        for (const auto& value : simulation.getStateHistory()) {
            outStream << value.first << separator;
            const auto& agents = value.second;
            size_t numAgents = agents.size();
            for (size_t i = 0; i < numAgents; ++i) {
                const auto& agent = agents[i];
                outStream << agent.getTotalAmount();
                if (i != numAgents - 1) {
                    outStream << separator;
                }
            }
            outStream << "\n";
        }
        
        return outStream.str();
    }
    
    static void writeStateHistoryToCsv(const ReactionNetworkSimulator& simulation, const std::string& outputFile, char separator) {
        std::ofstream file(outputFile.ends_with(".csv") ? outputFile : outputFile + ".csv");
        file << convertToCsvString(simulation, separator);
    }
};
#endif  // LAMBDAS_CSVFACTORY_H
