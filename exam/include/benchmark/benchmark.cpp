//
// Created by rasmus on 2/12/2023.
//

#include "benchmark.h"

void benchmark::perform_measurement(const std::function<void()> &func, benchmarkResult&measurement) {
    timer timer;
    timer.start();
    func();
    auto time = timer.stop();
    measurement.add_measurement(time);
}

benchmarkResult benchmark::getById(const int id) {
    auto begin = results.begin();
    auto end = results.end();
    std::vector<benchmarkResult>::iterator result;
    result = std::find_if(begin, end,
                          [id](benchmarkResult b_result){return b_result.id == id;});

    if (result != end)
        return results.at(result - end);
    
    return benchmark_result{NOT_PRESENT};
}

benchmarkResult benchmark::perform_measurements(const std::function<void()> &func, int num_measurements) {
    auto measurement = benchmarkResult{};
    measurement.id = rand();
    for (int i = 0; i < num_measurements; ++i)
        perform_measurement(func, measurement);
    
    return measurement;
}


