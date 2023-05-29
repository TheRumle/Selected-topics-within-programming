
//
// Created by rasmus on 5/29/2023.
//

#include "../include/reaction_network/reactionNetworkSimulator.h"
#include "../include/factories/csvFactory.h"
#include "../include/factories/reactionNetworkFactory.h"
#include "../include/factories/graphvizFactory.h"

void simulateAndWriteCsv(ReactionNetworkSimulator& simpleSimulation, double endTime, const std::string& name){
    simpleSimulation.operator()(endTime);
    CsvFactory csvFactory{simpleSimulation, ';'};
    csvFactory.writeStateHistoryToCsv(name);
}

int main(){
    ReactionNetworkSimulator simpleSimulation1 = create1stSimpleSimulation();
    ReactionNetworkSimulator simpleSimulation2 = create1stSimpleSimulation();
    ReactionNetworkSimulator simpleSimulation3 = create1stSimpleSimulation();
    ReactionNetworkSimulator circadianSimulator = createCircadianNetwork();
    ReactionNetworkSimulator covidSimulator = createCovidNetworkSimulation();
    
    simulateAndWriteCsv(simpleSimulation1, 1500, "simple1");
    simulateAndWriteCsv(simpleSimulation2, 1500, "simple2");
    simulateAndWriteCsv(simpleSimulation3, 1500, "simple3");
    simulateAndWriteCsv(circadianSimulator, 100, "circadian");
    simulateAndWriteCsv(covidSimulator, 100, "covid");
    
    GraphVizFactory {simpleSimulation1.getNetwork(), "simple_simulation1"}
        .createGraphVizPng();
    
    GraphVizFactory {simpleSimulation2.getNetwork(), "simple_simulation2"}
        .createGraphVizPng();
    
    GraphVizFactory {simpleSimulation3.getNetwork(), "simple_simulation3"}
        .createGraphVizPng();
    
    GraphVizFactory {circadianSimulator.getNetwork(), "circadian"}
        .createGraphVizPng();
    
    GraphVizFactory {covidSimulator.getNetwork(), "covidSimulator"}
        .createGraphVizPng();


    return 0;
}