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
       
    const Agent::P_Container A = Agent::CreateShared("A", 100);
    const Agent::P_Container B = Agent::CreateShared("B", 0);
    const Agent::P_Container C = Agent::CreateShared("C", 1);
    double lambda = 0.001;
    const Agent::P_Container::Composite composite = A + C;
    Reaction reaction{composite >>= C + B,lambda}; //alternatively, A + C is written directly in the reaction
    
    ReactionNetwork simpleNetwork{{reaction}}; //The above is encapsulated in functions createNthSimpleSimulation
    ReactionNetworkSimulator simpleSimulator(simpleNetwork);
    AllStateCopyMonitor monitor{};
    simpleSimulator(1500, monitor); // perform the simulation
    CsvFactory csvFactory{monitor, ';'};
    csvFactory.writeStateHistoryToCsv("simple_simulation1");//Above is encapsulated in simulateAndWriteCsv
    
    
    ReactionNetworkSimulator simpleSimulation2 = create2ndSimpleNetwork();
    simulateAndWriteCsv(simpleSimulation2, 1500, "simple2");
    
    ReactionNetworkSimulator simpleSimulation3 = create3rdSimpleNetwork();
    simulateAndWriteCsv(simpleSimulation3, 1500, "simple3");

    
    ReactionNetworkSimulator covidSimulator1 = createCovidNetworkSimulation(10000);
    simulateAndWriteCsv(covidSimulator1, 100, "covid1");
    GraphVizFactory {covidSimulator1.getNetwork(), "covidSimulator2"}
        .createGraphVizPng();
    
    ReactionNetworkSimulator covidSimulator2 = createCovidNetworkSimulation(20000);
    simulateAndWriteCsv(covidSimulator2, 100, "covid2");
    
    ReactionNetworkSimulator circadianSimulator = createCircadianNetwork();
    simulateAndWriteCsv(circadianSimulator, 100, "circadian");
    GraphVizFactory {circadianSimulator.getNetwork(), "circadian"}
        .createGraphVizPng();
    
    return 0;
}