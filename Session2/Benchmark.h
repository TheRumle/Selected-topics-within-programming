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
#include "benchmark_result.h"


class benchmark {
public:
    enum {NOT_PRESENT = -1};
    static benchmark_result benchmark_function(int runs, const std::function<void (void)> &func);
    benchmark_result getById(int id);
    static void perform_measurement(const std::function<void()> &func, benchmark_result &measurement) ;
private:
    std::vector<benchmark_result> results;
};

#endif //SESSION2_BENCHMARK_H
