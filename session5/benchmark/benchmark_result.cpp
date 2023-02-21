#include <iostream>
#include "benchmark_result.h"

std::ostream &operator<<(std::ostream &os, const benchmark_result &s) {
    return (os << "Benchmark with id " << s.id << " had mean \t" <<
               s.mean() << " ms. and standard error "<< s.standard_error() <<
               " with n=" << s.number_of_measurements << std::endl);
}