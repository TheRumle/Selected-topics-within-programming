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
