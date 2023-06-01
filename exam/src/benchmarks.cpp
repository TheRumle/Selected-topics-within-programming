//
// Created by rasmus on 5/31/2023.
//
#include <future>
#include "../include/reactionNetwork/reactionNetworkSimulator.h"
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


int BenchMultiThread(int N){
    auto m1= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 2 );
    auto m2= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 3 );
    auto m3= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 4 );
    auto m4= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 6 );
    auto m5= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 8 );
    auto m6= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 10 );
    auto m7= multiThreadedBenchmark([N]() { return createCovidNetworkSimulation(N);}, 12 );
    print_voradic(m1, m2, m3, m4, m5, m6, m7);
}


int main(){
    //Benchmarks for how long the simulation algorithm takes. 
    auto n1= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(3000); });
    auto n2= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(6000); });
    auto n3= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(8000); });
    auto n4= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(10000); });
    auto n5= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(15000); });
    auto n6= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(18000); });
    auto n7= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(20000); });
    auto n8= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(22000); });
    auto n9= singleThreadedBenchmark([]() { return createCovidNetworkSimulation(25000); });
    print_voradic(n1,n2,n3,n4,n5,n6,n7,n8,n9);
    
    std::cout << "\n\nMMM\n";
    BenchMultiThread(3000);
    std::cout << "\n\nQQQQ\n";
    BenchMultiThread(10000);
    
    std::cout << "\n\nFFF\n";
    BenchMultiThread(15000);
    std::cout << "\n\nHHH\n";
    BenchMultiThread(20000);
    
    std::cout << "\n\nPPPP\n";  
    BenchMultiThread(25000);
}