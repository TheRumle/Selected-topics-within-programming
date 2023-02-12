﻿//
// Created by rasmus on 2/12/2023.
//

#include "Benchmark.h"

benchmark_result benchmark::benchmark_function(int runs, const std::function<void()> &func) {
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(INT_MIN,INT_MAX);
    auto id = dist(mt);
    
    benchmark_result measurement{id};
    for (int i = 0; i <runs; ++i) 
        perform_measurement(func, measurement);
    
    return measurement;
}

void benchmark::perform_measurement(const std::function<void()> &func, benchmark_result &measurement) {
    timer timer;
    timer.start();
    func();
    auto time = timer.stop();
    measurement.add_measurement(time);
}


benchmark_result benchmark::getById(int id) {
    auto begin = results.begin();
    auto end = results.end();
    std::vector<benchmark_result>::iterator result;
    result = std::find_if(begin, end,[id](benchmark_result b_result)
    {return b_result.id == id;});

    if (result != end)
        return results.at(result - end);

    return benchmark_result{NOT_PRESENT};
}
