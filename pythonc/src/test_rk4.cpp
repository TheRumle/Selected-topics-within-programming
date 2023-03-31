//
// Created by rasmu on 31/03/2023.
//
#include "rk4.h"
#include <vector>
#include <iostream>


int main()
{
    size_t vars = 3;
    size_t steps = 50;
    auto t = std::vector<double>(vars*steps);
    t.at(2) = 1.0;
    solve_trig(steps, 0.01, t.data());
    for (size_t v = 1; v < vars; ++v) {
        std::cout<<"v: "<<v;
        for (size_t s = 0; s < steps; ++s)
            std::cout<<"( " << t.at(s*vars) <<"," << t.at(s*vars+v) <<")";
        std::cout << std::endl;
    }
    
}