#include <iostream>
#include <future>
#include <numeric>
#include "reactionNetwork/reactionNetworkSimulator.h"
#include "factories/reactionNetworkFactory.h"

double findMean(std::vector<std::future<double>>& futures) {
    std::vector<double> values;
    values.reserve(futures.size());
    
    // Wait for the futures to complete and collect the results
    for (auto& future : futures) {
        values.push_back(future.get());
    }

    // Calculate the mean
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

double computeAndGetMeanHospitalizedForN(int n){
    std::vector<std::future<double>> results{};
    for (int i = 0; i < 20; ++i) {
        results.emplace_back(std::async(std::launch::async, 
        [n]
        {
            CovidHospitalizationMonitor monitor{};
            createCovidNetworkSimulation(n).operator()(100, monitor);
            return monitor.extractPeakHospitalizedValue();
        }));
    }

    return findMean(results);
}

int main() {
    std::cout << computeAndGetMeanHospitalizedForN(589755);//129.9, 127.55, 125.9, 127.95
    std::cout<<"\n \n";
    std::cout << computeAndGetMeanHospitalizedForN(5822763);//1190.7, 1192.85, 1211, 1202, 1166
}