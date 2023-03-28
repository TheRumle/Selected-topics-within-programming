#include <random>
#include <iostream>
#include <thread>
#include "mtqueue.hpp"
static int number_of_data_in_queue = 100;
static auto gen = std::mt19937{std::random_device{}()};
static auto dist = std::uniform_int_distribution<int>{1, 100};
void produce(mtqueue<int>& q)
{
    for (auto i=0u; i < number_of_data_in_queue; ++i)
        q.put(dist(gen));
}

void consume(mtqueue<int>& qu)
{
    for (auto i=0u; i < number_of_data_in_queue * 100; ++i)
        std::cout << " " << qu.get();
}

int main(){
    mtqueue<int> mtqueue{};
    std::vector<std::thread> producers = {};
    std::vector<std::thread> consumers = {};
    for (int i = 0; i < 3; ++i)
        producers.emplace_back(std::thread{produce, std::ref(mtqueue)});

    for (int i = 0; i < 2; ++i) 
        consumers.emplace_back(std::thread{consume, std::ref(mtqueue)});

    for (auto &p:producers) 
        p.join();
    
    for (auto &c : consumers)
        c.join();
    
    // TODO: create an instance of a queue
	// TODO: spawn multiple producers for producer and consumer using the queue
    // NOTE: producer and consumer expect to bind to the queue by reference:
    // 1) STL uses values, therefore plain queue argument might not work: wrap the queue into std::ref instead.
    // 2) Using std::ref is not normal: it is a red-flag that we are doing something wrong.
    //    In this case we are sharing the queue between producers -- dangerous design!
    //    But in this exercise this is how we stress-test our queue in multi-threaded (MT) environment.
    // NOTE: many successful test runs do not guarantee that the queue is MT-safe.
    // You may make your producers to work longer, try running optimized builds hoping to trigger an error,
    // or enable option(TSAN "Thread Sanitizer" ON) in the CMakeLists.txt
    // (remember to regenerate the cmake build by deleting the build directories).
    // Limitations:
    //  - clang++-13 does not ship std::jthread.
    //  - thread sanitizer is supported only on Linux and MacOS.
}