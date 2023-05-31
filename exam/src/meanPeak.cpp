﻿//
// Created by rasmus on 5/31/2023.
//
#include <iostream>
#include <future>
#include <numeric>
#include "reaction_network/reactionNetworkSimulator.h"
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
    std::cout << computeAndGetMeanHospitalizedForN(10000); //3.55, 3.35
    std::cout<<"\n \n";
    std::cout << computeAndGetMeanHospitalizedForN(15000); //4.6, 5
    std::cout<<"\n \n";
    std::cout << computeAndGetMeanHospitalizedForN(250000);//57.5, 55.5
    std::cout<<"\n \n";
    std::cout << computeAndGetMeanHospitalizedForN(589755);//129.9, 127.55, 127.55, 125.9, 127.95
    std::cout<<"\n \n";
    std::cout << computeAndGetMeanHospitalizedForN(5822763);//1190.7, 1192.85 
}