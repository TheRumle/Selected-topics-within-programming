#include <iostream>
#include <benchmark_result.h>
#include "NumberSeries.h"
#include "Client.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    auto a = series::NumberSeries::MakeRandom(10);
    auto b = series::NumberSeries::MakeRandom(15) + a;
    b +=a;
    std::cout << b;
    std::cout << series::NumberSeries::MakeRandom(32, -100, 100);
    
    std::cout<<"  BENCHMARKS" << std::endl;
    benchmark_result q = series::Client::run_benchmark(10);
    std::cout << q;
    return 0;
}
