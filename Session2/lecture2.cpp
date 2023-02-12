//
// Created by rasmus on 2/12/2023.
//

#include <iostream>
#include <limits>
#include "lecture2.h"
#include <chrono>
#include <vector>

#include "lecture2.h"
using clk = std::chrono::high_resolution_clock;
using time_point = clk::time_point;
union E2Union
{
    float f;
    unsigned int i;
    char c[4];
};


template<typename T>
void printForType() {
    auto l = std::numeric_limits<T>{};
    std::cout << "Size is " << sizeof (T)  << " and max, min, and low is " <<
              l.max() <<" "<<
              l.min() <<" "<<
              l.lowest()  << std::endl;
}

void print_type_and_size(){
    printForType<char>();
    printForType<int>();
    printForType<long>();
    printForType<long long>();
    printForType<float>();
    printForType<double>();
    printForType<long double>();
}

void print_union(){
    auto a = E2Union{};
    a.i = 15;
    for (char i : a.c) {
        std::cout << +i; //convert to int
        // it is little endian, since smallest bits are first.
        auto clock = std::chrono::high_resolution_clock::now();
    }
}
struct measurement_t{
    char* name;
    size_t count{0};
    double sum{0}; // the sum of timings
    double sumsq{0}; // the sum of squared timings
    void add_measurement(std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>){

    }
};

class Benchmark {
    time_point last;
    std::vector<measurement_t> measurements;
private:
    clk::time_point startTime;
public:
    void start(){
        startTime = clk::now();
    }

    static void click_time_point(){
        auto t = clk::now();

    }

    double stop(){
        std::chrono::duration<double, std::milli> fp_ms = clk::now() - startTime;
        return fp_ms.count();
    }
};