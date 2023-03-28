#include <vector>
#include <future>
#include <random>
#include <iostream>

static int number_of_data_in_queue = 100;
static auto gen = std::mt19937{std::random_device{}()};
static auto dist = std::uniform_int_distribution<int>{1, 100};

std::vector<int> produce(size_t s){
    std::vector<int> nums = std::vector<int>();
    for (auto i=0u; i < s; ++i)
        nums.push_back(dist(gen));
    return nums;
}

int summarize(std::vector<std::future<std::vector<int>>>&& futures){
    int sum = 0;
    for (auto &f : futures) {
        const auto data = f.get();
        sum += std::accumulate(data.begin(), data.end(), 0);
    }
    return sum;
}

int main(){
    int constexpr num_fut = 100;
    auto futures = std::vector<std::future<std::vector<int>>>{};
    for (int i = 0; i < num_fut; ++i) 
        futures.push_back(std::async(std::launch::async, []{return produce(100);}));

    std::cout << summarize(std::move(futures));
}