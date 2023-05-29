//
// Created by rasmus on 5/29/2023.
//


#ifndef LAMBDAS_CSVFACTORY_H
#define LAMBDAS_CSVFACTORY_H
#include "reaction_network/reactionNetworkSimulator.h"

struct CsvFactory {
private:
    const char separator;
    const ReactionNetworkSimulator& simulation;
    
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
    CsvFactory(const ReactionNetworkSimulator& simulation) : simulation(simulation), separator(';'){
    }
    
    CsvFactory(const ReactionNetworkSimulator& simulation, const char separator) : simulation(simulation), separator(separator){
    }
    
    std::string convertToCsvString() {
        std::stringstream outStream;
        CsvFactory::appendAgentHeaders(outStream, simulation.getAgents(), separator);
        CsvFactory::appendStateHistory(outStream, simulation.getStateHistory(), separator);
        return outStream.str();
    }
    
    void writeStateHistoryToCsv(const std::string& outputFile) {
        std::ofstream file(outputFile.ends_with(".csv") ? outputFile : outputFile + ".csv");
        file << convertToCsvString();
    }
};
#endif  // LAMBDAS_CSVFACTORY_H
