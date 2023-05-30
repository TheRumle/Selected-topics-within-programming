//
// Created by rasmus on 5/29/2023.
//


#ifndef LAMBDAS_CSVFACTORY_H
#define LAMBDAS_CSVFACTORY_H
#include <set>
#include "reaction_network/reactionNetworkSimulator.h"

struct CsvFactory {
private:
    char separator;    
    AllStateCopyMonitor monitor{};
    
    static void appendStateHistory(std::stringstream& outStream,
                                   const Monitor::observations& observations, char separator ){
        for (const auto& pair : observations) {
            outStream << pair.first << separator;
            const ReactionNetwork::state& agents = pair.second;
            const size_t numAgents = agents.size();
            for (size_t i = 0; i < numAgents; ++i) {
                const std::shared_ptr<const Agent>& agent = agents[i];
                outStream << agent->getTotalAmountAgent();
                if (i != numAgents - 1) {
                    outStream << separator;
                }
            }
            outStream << "\n";
        }
    };
    
    static void writeHeaders(std::stringstream& outStream,
                             const Monitor::observations& observations, char separator){
        const auto& agents = observations.front().second;
        
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
    CsvFactory(const AllStateCopyMonitor& monitor, const char separator) 
        : monitor(monitor), separator(separator)
    {
    }
    
    std::string convertToCsvString() {
        std::stringstream outStream;

        CsvFactory::writeHeaders(outStream, monitor.getObservations(), separator);
        CsvFactory::appendStateHistory(outStream, monitor.getObservations(), separator);
        return outStream.str();
    }
    
    void writeStateHistoryToCsv(const std::string& outputFile) {
        std::ofstream file(outputFile.ends_with(".csv") ? outputFile : outputFile + ".csv");
        file << convertToCsvString();
    }
};
#endif  // LAMBDAS_CSVFACTORY_H
