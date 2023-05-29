
//
// Created by rasmus on 5/29/2023.
//
#include "factories/reactionNetworkFactory.h"
#include "factories/csvFactory.h"
#include "factories/graphvizFactory.h"

void simulateAndWriteCsv(ReactionNetworkSimulator& simpleSimulation, double endTime, const std::string& name){
    simpleSimulation.operator()(endTime);
    CsvFactory csvFactory{simpleSimulation, ';'};
    csvFactory.writeStateHistoryToCsv(name);
}

int main(){
    ReactionNetworkSimulator simpleSimulation = create1stSimpleSimulation();
    ReactionNetworkSimulator circadianSimulator = createCircadianNetwork();
    ReactionNetworkSimulator covidSimulator = createCovidNetworkSimulation();
    
    simulateAndWriteCsv(simpleSimulation, 1500, "simple");
    simulateAndWriteCsv(circadianSimulator, 100, "circadian");
    simulateAndWriteCsv(covidSimulator, 100, "covid");
    
  
    return 0;
}