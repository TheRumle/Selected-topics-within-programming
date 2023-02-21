#include <iostream>
#include <memory>
#include <vector>
#include "polymorphic_test/base.h"
#include "benchmark/Benchmark.h"
#include "polymorphic_test/derived.h"


int main() {
    constexpr int NUM_ELEMS = 10000000;
    constexpr int NUM_BENCHES = 50;
    //Create a vector of 10.000.000 smart pointers to base and measure how well it performs its operations
    //and compare it to the derived class
    std::cout << "Using the base and derived implementations of increment" << std::endl;
    
    std::vector<std::unique_ptr<Base>> bases = std::vector<std::unique_ptr<Base>>();
    for (int i = 0; i < NUM_ELEMS; ++i)
        bases.push_back(std::make_unique<Base>(Base{}));
    
    auto baseResult = benchmark::perform_measurements([&bases](){
        for (const auto &b : bases) 
            b->increment();
        }, NUM_BENCHES);
    std::cout << baseResult;


    std::vector<std::unique_ptr<Base>> derived = std::vector<std::unique_ptr<Base>>();
    for (int i = 0; i < NUM_ELEMS; ++i)
        derived.push_back(std::make_unique<Derived>(Derived{}));

    const auto derivedResult = benchmark::perform_measurements([&derived](){
        for (const auto &b : derived)
            b->increment();
    }, NUM_BENCHES);
    
    
    
    std::cout << derivedResult;
    std::destroy(bases.begin(), bases.end());
    std::destroy(derived.begin(), derived.end());

    std::cout << "Using the base for decrement, which is overridden! Thus we need lookup in virtual table!" << std::endl;
    
    bases = std::vector<std::unique_ptr<Base>>();
    for (int i = 0; i < NUM_ELEMS; ++i)
        bases.push_back(std::make_unique<Base>(Base{}));

    auto baseResult2 = benchmark::perform_measurements([&bases](){
        for (const auto &b : bases)
            b->decrement();
    }, NUM_BENCHES);
    std::cout << baseResult2;


    derived = std::vector<std::unique_ptr<Base>>();
    for (int i = 0; i < NUM_ELEMS; ++i)
        bases.push_back(std::make_unique<Base>(Base{}));

    const auto derivedResult2 = benchmark::perform_measurements([&bases](){
        for (const auto &b : bases)
            b->decrement();
    }, NUM_BENCHES);
    std::cout << derivedResult2;
    

    return 0;
}
