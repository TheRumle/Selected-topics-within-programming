//
// Created by rasmus on 5/29/2023.
//


#ifndef LAMBDAS_CSVFACTORY_H
#define LAMBDAS_CSVFACTORY_H
#include "reaction_network/reactionNetworkSimulator.h"

struct CsvFactory {
private:
    static void appendStateHistory(std::stringstream& outStream, const ReactionNetworkSimulator::state_history& history, char separator ){
        for (const auto& pair : history) {
            outStream << pair.first << separator;
            const auto& agents = pair.second;
            const size_t numAgents = agents.size();
            for (size_t i = 0; i < numAgents; ++i) {
                const Agent& agent = agents[i];
                outStream << agent.getTotalAmount();
                if (i != numAgents - 1) {
                    outStream << separator;
                }
            }
            outStream << "\n";
        }
    };
    
    static void appendAgentHeaders(std::stringstream& outStream, const std::vector<std::shared_ptr<Agent>>& agents, char separator){
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
    }
public:
    
    
    static std::string convertToCsvString(const ReactionNetworkSimulator& simulation, char separator) {
        std::stringstream outStream;
        CsvFactory::appendAgentHeaders(outStream, simulation.getAgents(), separator);
        CsvFactory::appendStateHistory(outStream, simulation.getStateHistory(), separator);
        return outStream.str();
    }
    
    static void writeStateHistoryToCsv(const ReactionNetworkSimulator& simulation, const std::string& outputFile, char separator) {
        std::ofstream file(outputFile.ends_with(".csv") ? outputFile : outputFile + ".csv");
        file << convertToCsvString(simulation, separator);
    }
};
#endif  // LAMBDAS_CSVFACTORY_H
