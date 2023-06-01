//
// Created by rasmus on 5/29/2023.
//

#include "../include/reactionNetwork/reactionNetworkSimulator.h"
#include "../include/factories/csvFactory.h"
#include "../include/factories/reactionNetworkFactory.h"
#include "../include/factories/graphvizFactory.h"

void simulateAndWriteCsv(ReactionNetworkSimulator& simpleSimulation, double endTime, const std::string& name){
    AllStateCopyMonitor monitor{};
    simpleSimulation(endTime, monitor);
    CsvFactory csvFactory{monitor, ';'};
    csvFactory.writeStateHistoryToCsv(name);
}

int main(){
    ReactionNetworkSimulator simpleSimulation1 = create1stSimpleSimulation();
    simulateAndWriteCsv(simpleSimulation1, 1500, "simple1");
    GraphVizFactory {simpleSimulation1.getNetwork(), "simple_simulation1"}
        .createGraphVizPng();
    
    ReactionNetworkSimulator simpleSimulation2 = create2ndSimpleNetwork();
    simulateAndWriteCsv(simpleSimulation2, 1500, "simple2");
    GraphVizFactory {simpleSimulation2.getNetwork(), "simple_simulation2"}
        .createGraphVizPng();
    
    ReactionNetworkSimulator simpleSimulation3 = create3rdSimpleNetwork();
    simulateAndWriteCsv(simpleSimulation3, 1500, "simple3");
    GraphVizFactory {simpleSimulation3.getNetwork(), "simple_simulation3"}
        .createGraphVizPng();
    
    
    
    ReactionNetworkSimulator circadianSimulator = createCircadianNetwork();
    simulateAndWriteCsv(circadianSimulator, 100, "circadian");
    GraphVizFactory {circadianSimulator.getNetwork(), "circadian"}
        .createGraphVizPng();
    
    ReactionNetworkSimulator covidSimulator1 = createCovidNetworkSimulation(10000);
    simulateAndWriteCsv(covidSimulator1, 100, "covid1");
    GraphVizFactory {covidSimulator1.getNetwork(), "covidSimulator2"}
        .createGraphVizPng();
    
    ReactionNetworkSimulator covidSimulator2 = createCovidNetworkSimulation(20000);
    simulateAndWriteCsv(covidSimulator2, 100, "covid2");
    GraphVizFactory {covidSimulator1.getNetwork(), "covidSimulator2"}
        .createGraphVizPng();


    return 0;
}