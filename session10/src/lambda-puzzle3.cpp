/**
 * Purpose: exercise lambda expressions with STL algorithms.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */
#include <doctest.h>
#include <iostream>
#include <vector>
#include <random>
#include <sstream>


static auto gen = std::mt19937{std::random_device{}()};


void fill_with_data(std::vector<int>& data, size_t count)
{
    for (auto i=0u; i<count; ++i)
        std::generate_n(data.begin(), count, gen);
		
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
    constexpr int data_size = 20;
    auto data = std::vector<int>{};
    fill_with_data(data, data_size);
    SUBCASE("print")    /** TODO: write test for print_data */
    {
        std::ostringstream stringstream{};
        print_data(stringstream, data);
        
        std::ostringstream actual{};
        std::for_each(data.begin(), data.end(), [&actual](int e){
            actual << e;
        });
        
        CHECK(actual.str() == stringstream.str());
    }


    SUBCASE("sum"){
        auto actual = compute_sum(data);
        auto sum = std::accumulate(data.begin(), data.end(), 0);
        CHECK(sum == actual);        
    }
    /** TODO: write test for concat */

    SUBCASE("concat")
    {
        auto a = concatenate(data);
        
    }
    std::cout << "concat: " << concatenate(data) << std::endl;
    /** TODO: write test for odd_count */
    std::cout << "odd count: " << odd_count(data) << std::endl;
    /** TODO: write test for stringify */
    auto data_str = stringify(data);
    /** TODO: write test for compute_sorted */
    auto sorted_str = compute_sorted(data_str);
    /** TODO: write test for squares */
    // make print_data a function template, so that the following is accepted:
    //print_data(std::cout, sorted_str);
    print_data(std::cout, squares(data));
}
