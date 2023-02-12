//
// Created by rasmu on 12/02/2023.
//

#include <random>
#include "bench_random.h"
#include "Benchmark.h"



void bench_rnd_vals(int min, int max, int count) {

    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);

    int *random_numbers = new int[count];

    for (int i = 0; i < count; i++) {
        int random_number = dist(mt);
        random_numbers[i] = random_number;
    }

    delete[] random_numbers;

}

void run_bench() {
    constexpr int count = 10'0000;
    constexpr int min = 0;
    constexpr int max = 1000;
    auto res = benchmark::bench_rand_vals(10000, []() { bench_rnd_vals(min, max, count); });
    std::cout << res;
}
