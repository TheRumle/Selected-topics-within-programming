/**
 * Purpose: exercise lambda expressions with STL algorithms.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include <doctest.h>
#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <iterator>


static auto gen = std::mt19937{std::random_device{}()};
static auto dist = std::uniform_int_distribution<int>{0,100};

void fill_with_data(std::vector<int>& data, size_t count)
{
    for (auto i=0u; i<count; ++i)
        data.push_back(dist(gen));
		
}

void print_data(std::ostream& os, const std::vector<int>& data)
{
    /** TODO: use copy and ostream_iterator instead */
    for (auto&& d: data)
		os << d << ' ';
    os << '\n';
}

int compute_sum(const std::vector<int>& data)
{
return    std::accumulate(data.begin(), data.end(), 0);
}

std::string concatenate(const std::vector<int>& data)
{
    /** TODO: use accumulate instead */
    auto res = std::string{};
    for (auto&& d: data)
		res += std::to_string(d);
    return res;
}

size_t odd_count(const std::vector<int>& data)
{
    /** TODO: use count_if instead */
    auto count = 0u;
    for (auto&& d: data)
		if (d % 2 == 1)
			++count;
    return count;
}

std::vector<std::string> stringify(const std::vector<int>& data)
{
    /** TODO: use transform instead */
    auto res = std::vector<std::string>{};
    for (auto&& d: data)
		res.push_back(std::to_string(d));
    return res;
}

std::vector<std::string> compute_sorted(const std::vector<std::string>& data)
{
    /** TODO: use std::sort */
    auto res = data;
    // sorting implementation of decreasing alphabetical order
    return res;
}


std::vector<int> squares(const std::vector<int>&)
{
    /** TODO: find and use an applicable std algorithm */
    auto res = std::vector<int>{};
    // compute square of each input element
    return res;
}

TEST_CASE("Lambda puzzle3")
{
    int data_size = 20;
    auto data = std::vector<int>{};
    fill_with_data(data, data_size);
    SUBCASE("print")    /** TODO: write test for print_data */
    {
        auto actual = concatenate(data);
        std::ostringstream expected{};

        
        std::for_each(data.begin(), data.end(), [&expected](int e){
            expected << e;
        });
        
        CHECK(expected.str() == actual);
    }


    SUBCASE("sum"){
        auto actual = compute_sum(data);
        auto sum = std::accumulate(data.begin(), data.end(), 0);
        CHECK(sum == actual);        
    }
    
    /** TODO: write test for concat */
    SUBCASE("concat")
    {
        auto actual = concatenate(data);

        std::stringstream expected;
        #pragma unroll 4
        for (const auto &a: data) 
            expected << a;
        
        CHECK(actual == expected.str());
    }

    SUBCASE("odd count: ")
    {
        int expected = 0;
        auto actual = odd_count(data);
        for (const auto &a: data)
            if (a % 2 != 0)
                ++expected;

        CHECK(actual == expected);
    }

    SUBCASE("stringify: ")
    {
        std::vector<std::string> expected = std::vector<std::string>();
        auto actual = stringify(data);

        for (const auto &a: data)
            expected.push_back(std::to_string(a));

        CHECK(actual == expected);
        
         actual = compute_sorted(actual);
         
    }


    /** TODO: write test for stringify */
    /** TODO: write test for compute_sorted */
    /** TODO: write test for squares */
    // make print_data a function template, so that the following is accepted:
    //print_data(std::cout, sorted_str);
    print_data(std::cout, squares(data));
}
