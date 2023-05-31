//
// Created by rasmus on 5/31/2023.
//
#include <future>
#include "../include/reaction_network/reactionNetworkSimulator.h"
#include "../include/benchmark/benchmark.h"
#include "../include/factories/reactionNetworkFactory.h"

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

void create_and_partition_threads(const std::function<ReactionNetworkSimulator()>& factory, int numThreads){
    const int numSimulations = NUMBER_OF_SIMULATIONS;
    const int simulationsPerThread = numSimulations / numThreads;
    const int remainder = numSimulations % numThreads;
    
    auto simulationTask = [factory](int start, int end) {
        for (int i = start; i < end; ++i) {
            auto simulation = factory();
            simulation(COVID_ENDTIME);
        }
    };
    
    std::vector<std::future<void>> futures;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * simulationsPerThread;
        int end = start + simulationsPerThread;
        if (i == numThreads - 1) {
            // Add remaining simulations to the last thread
            end += remainder;
        }

        futures.emplace_back(std::async(std::launch::async, simulationTask, start, end));
    }

    // Wait for all the futures to complete
    for (auto& future : futures) {
        future.get();
    }
}

benchmark_result multiThreadedBenchmark(const std::function<ReactionNetworkSimulator()>&& factory, int numThreads){
    std::cout << "--------------Beginning benchmark--------------";
    benchmark benchy{};
    benchmark_result result = benchy.perform_measurements([&factory, numThreads]() {
        create_and_partition_threads(factory,numThreads);
    }, NUMBER_OF_BENCHMARKS);
    
    std::cout << "--------------End of Benchmark--------------";
    return result;
}
int main(){
    //Benchmarks for how long the simulation algorithm takes. 
    //auto n1= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(3000); });
    //auto n2= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(6000); });
    //auto n3= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(8000); });
    //auto n4= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(10000); });
    //auto n5= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(15000); });
    //auto n6= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(18000); });
    //auto n7= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(20000); });
    //auto n8= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(22000); });
    //auto n9= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(25000); });
    //print_voradic(n1,n2,n3,n4,n5,n6,n7,n8,n9);
    
    std::cout << "\n\nMMM\n";
    auto m1= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 2 );
    auto m2= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 3 );
    auto m3= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 4 );
    auto m4= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 6 );
    auto m5= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 8 );
    auto m6= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 10 );
    auto m7= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(3000);}, 12 );
    print_voradic(m1, m2, m3, m4, m5, m6, m7);
    
    std::cout << "\n\nQQQQ\n";
    auto Q1= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 2);
    auto Q2= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 3);
    auto Q3= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 4);
    auto Q4= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 6);
    auto Q5= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 8);
    auto Q6= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 10);
    auto Q7= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(10000);}, 12);
    print_voradic(Q1,Q2,Q3,Q4,Q5,Q6,Q7);
    
    std::cout << "\n\nFFF\n";
    auto F1= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 2);
    auto F2= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 3);
    auto F3= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 4);
    auto F4= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 6);
    auto F5= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 8);
    auto F6= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 10);
    auto F7= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(15000);}, 12);
    print_voradic(F1,F2,F3,F4,F5,F6,F7);
    std::cout << "\n\nHHH\n";
    auto H1= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 2);
    auto H2= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 3);
    auto H3= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 4);
    auto H4= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 6);
    auto H5= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 8);
    auto H6= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 10);
    auto H7= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(20000);}, 12);
    print_voradic(H1,H2,H3,H4,H5,H6,H7);
    
    std::cout << "\n\nPPPP\n";
    auto P1= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 2);
    auto P2= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 3);
    auto P3= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 4);
    auto P4= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 6);
    auto P5= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 8);
    auto P6= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 10);
    auto P7= multiThreadedBenchmark([]() { return createCovidNetworkSimulation(25000);}, 12);
    print_voradic(P1,P2,P3,P4,P5,P6,P7);
}