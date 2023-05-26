//
// Created by rasmus on 2/12/2023.
//

#include "benchmark.h"

void benchmark::perform_measurement(const std::function<void()> &func, benchmark_result &measurement) {
    timer timer;
    timer.start();
    func();
    auto time = timer.stop();
    measurement.add_measurement(time);
}


benchmark_result benchmark::getById(const int id) {
    auto begin = results.begin();
    auto end = results.end();
    std::vector<benchmark_result>::iterator result;
    result = std::find_if(begin, end,
                          [id](benchmark_result b_result){return b_result.id == id;});

    if (result != end)
        return results.at(result - end);
    
    return benchmark_result{NOT_PRESENT};
}

benchmark_result benchmark::perform_measurements(const std::function<void()> &func, int num_measurements) {
    auto measurement = benchmark_result{};
    for (int i = 0; i < num_measurements; ++i)
        perform_measurement(func, measurement);

    return measurement;
}


