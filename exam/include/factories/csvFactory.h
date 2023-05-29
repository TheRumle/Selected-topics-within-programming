//
// Created by rasmus on 5/29/2023.
//

#ifndef LAMBDAS_CSVFACTORY_H
#define LAMBDAS_CSVFACTORY_H
#include "reaction_network/ReactionNetworkSimulator.h"

struct CsvFactory {
    
    static std::string convert_to_csv_string(const ReactionNetworkSimulator& simulation, char seperator){
        std::stringstream outStream; 
        
        const auto& agents = simulation.getAgents();
        outStream << "Time" << seperator;
        const size_t numAgents = agents.size();
        for (size_t i = 0; i < numAgents; ++i) {
            const auto& agent = agents[i];
            outStream << agent->getAgentName();
            if (i != numAgents - 1) {
                outStream << seperator;
            }
        }
        
        outStream << "\n";
        for (const auto& value : simulation.getStateHistory()) {
            outStream << value.first << seperator;
            const auto& agents = value.second;
            size_t numAgents = agents.size();
            for (size_t i = 0; i < numAgents; ++i) {
                const auto& agent = agents[i];
                outStream << agent.total_amount();
                if (i != numAgents - 1) {
                    outStream << seperator;
                }
            }
            outStream << "\n";
        }
        
        return outStream.str();
    }
    

    static void write_state_history_to_csv(const ReactionNetworkSimulator& simulation, const std::string&outputFile, char seperator) {
        std::ofstream file(outputFile.ends_with(".csv")? outputFile : outputFile + ".csv");
        file << convert_to_csv_string(simulation, seperator);
    }

};

#endif  // LAMBDAS_CSVFACTORY_H
