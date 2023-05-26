#include <iostream>
#include "benchmark/benchmark.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    auto a = 2;
    benchmark::bench_rand_vals(0,[](){ return;});
    return 0;
}
