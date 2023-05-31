//
// Created by rasmus on 5/31/2023.
//
#include "../include/reaction_network/reactionNetworkSimulator.h"
#include "../include/benchmark/benchmark.h"
#include "factories/reactionNetworkFactory.h"

void print_voradic(){}
template<typename First, typename ...Rest>
void print_voradic(First && first, Rest && ...rest)
{
    std::cout << std::forward<First>(first);
    print_voradic(std::forward<Rest>(rest)...);
}

constexpr int NUMBER_OF_BENCHMARKS = 20;
constexpr int NUMBER_OF_SIMULATIONS = 10;
constexpr int COVID_ENDTIME = 100.00;



benchmark_result singleThreadedBenchmark(const std::function<ReactionNetworkSimulator()>&& factory){
    benchmark benchy{};
    std::cout << "--------------------Beginning benchmark--------------------";
    
    //Figure out long it takes to run simulation 10 times, and benchmark this 20 times
    auto res =  benchy.perform_measurements([&factory](){
        for (int i = 0; i < NUMBER_OF_SIMULATIONS; ++i) {
            auto simulation = factory();
            simulation(COVID_ENDTIME);
        }
    }, NUMBER_OF_BENCHMARKS);

    
    std::cout << "----------------------End of Benchmark---------------------";
    return res;
}

std::vector<benchmark_result> benchmarkSimulationMultiThreaded(const std::function<ReactionNetworkSimulator()>&& factory, int numSimulation){
    benchmark benchy{};
    
    
    auto res =  benchy.perform_measurements([&factory](){
        auto simulation = factory();
        simulation(COVID_ENDTIME);
    }, NUMBER_OF_BENCHMARKS);
    return {res};
}

int main(){
    //Benchmarks for how long the simulation algorithm takes. 
    auto n3000= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(18000); });
    std::cout << "\n----------------------3000---------------------\n";
    auto n6000= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(20000); });
    std::cout << "\n----------------------6000---------------------\n";
    auto n8000= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(22000); });
    std::cout << "\n----------------------8000---------------------\n";
    auto n10000= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(25000); });
    std::cout << "\n----------------------10000--------------------\n";
    print_voradic(n3000, n6000, n8000, n10000);
}