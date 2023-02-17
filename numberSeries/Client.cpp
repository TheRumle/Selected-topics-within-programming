//
// Created by rasmu on 17/02/2023.
//

#include <Benchmark.h>
#include "Client.h"
#include "NumberSeries.h"


std::unique_ptr<std::vector<series::NumberSeries>> series::Client::fill_series() {
    constexpr std::size_t numb_series = 100'000;
    std::unique_ptr<std::vector<NumberSeries>> series = std::make_unique<std::vector<NumberSeries>>();
    constexpr std::size_t numb_elems = 100;
    series->reserve(numb_series);

    for (int i = 0; i < numb_series; ++i)
        series->push_back(NumberSeries::MakeRandom(numb_elems));

    return series;
}

void series::Client::fill_and_sort() {
    auto vals = Client::fill_series();
    std::sort(vals->begin(), vals->end());
}

benchmark_result series::Client::run_benchmark(int num_times_bench) {
    return benchmark::perform_measurements([]()
    {
        auto c = Client{};
        c.fill_and_sort();
    }, num_times_bench);
}
