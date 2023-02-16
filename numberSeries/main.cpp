#include <iostream>
#include "NumberSeries.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto a = series::NumberSeries::MakeRandom(10);
    auto b = series::NumberSeries::MakeRandom(15) + a;
    b +=a;
    std::cout << b;
    std::cout << series::NumberSeries::MakeRandom(32, -100, 100);
    return 0;
}
