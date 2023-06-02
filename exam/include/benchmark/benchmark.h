//
// Created by rasmus on 2/12/2023.
//

#ifndef SESSION2_BENCHMARK_H
#define SESSION2_BENCHMARK_H

#include <functional>
#include <chrono>
#include <iostream>
#include "timer.h"
#include "random"
#include "vector"
#include "benchmarkResult.h"

class benchmark {
public:
    enum {NOT_PRESENT = -1};
    benchmarkResult getById(int id);
    static benchmarkResult perform_measurements(const std::function<void()> &func, int num_measurements);
private:
    static void perform_measurement(const std::function<void()> &func, benchmarkResult&measurement) ;
    std::vector<benchmarkResult> results;
};

#endif //SESSION2_BENCHMARK_H
