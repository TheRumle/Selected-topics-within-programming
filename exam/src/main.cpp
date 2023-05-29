#include "factories/reactionNetworkFactory.h"
#include "factories/csvFactory.h"
#include "factories/graphvizFactory.h"
//
// Created by rasmus on 5/29/2023.
//

int main(){
    ReactionNetworkSimulator simpleSimulation = create1stSimpleSimulation();
    GraphVizFactory {simpleSimulation.getNetwork(), "simple_simulation"}
             .createGraphVizPng();

    simpleSimulation.operator()(1500);
    CsvFactory csvFactory{simpleSimulation, ';'};
    csvFactory.writeStateHistoryToCsv("simple_simulation");
    

    return 0;
}