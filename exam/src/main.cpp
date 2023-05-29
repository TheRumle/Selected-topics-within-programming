#include "factories/networkFactory.h"
#include "factories/csvFactory.h"
#include "factories/graphvizFactory.h"
//
// Created by rasmus on 5/29/2023.
//

int main(){
    auto network = create1stSimpleNetwork();
    ReactionNetworkSimulator runner {network.first, network.second };
    runner.operator()(1500);
    
    CsvFactory csvFactory{};
    csvFactory.write_state_history_to_csv(runner, "output", ';');
        
        
    GraphVizShower::CreateGraphVizPicture(network.first,"simple_graph.dot");
    return 0;
}