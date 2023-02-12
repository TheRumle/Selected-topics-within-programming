//
// Created by rasmus on 2/12/2023.
//

#ifndef SESSION2_BENCHMARK_RESULT_H
#define SESSION2_BENCHMARK_RESULT_H


#include <cstddef>
#include <valarray>

struct benchmark_result {
    int id = -1;
    long number_of_measurements{0};
    double sum{0}; // the sum of timings
    double sumsq{0}; // the sum of squared timings
    void add_measurement(double time) {
        ++number_of_measurements;
        sum += time;
        sumsq += time * time;
    }
    [[nodiscard]] double mean() const { return sum / number_of_measurements; }
    [[nodiscard]] double half_conf_interval() const {
        auto standard_error = std::sqrt((sumsq - sum * sum / number_of_measurements) / (number_of_measurements - 1) / number_of_measurements);
        return standard_error * 1.960147;
    }
};

#endif //SESSION2_BENCHMARK_RESULT_H


