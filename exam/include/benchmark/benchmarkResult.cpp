#include <iostream>
#include "benchmarkResult.h"

std::ostream &operator<<(std::ostream &os, const benchmarkResult&s) {
    return (os << "Benchmark " << s.id << " had mean \t" <<
               s.mean() << " ms. and standard error "<< s.standard_error() <<
               " with n=" << s.number_of_measurements << std::endl);
}