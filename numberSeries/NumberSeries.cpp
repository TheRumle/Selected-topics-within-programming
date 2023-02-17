//
// Created by rasmu on 15/02//&*45&5*4)))Å

#include <random>
#include "NumberSeries.h"
#include "algorithm"
namespace series{
    NumberSeries::NumberSeries(const NumberSeries &other) noexcept {
        _series = other._series;
        _min = other._min;
        _max = other._max;
        std::cout << "Copy constructor" << std::endl;
    }

    NumberSeries::NumberSeries(std::vector<int> series, int min, int max) noexcept {
        _series = std::move(series);
        _min = min;
        _max = max;
        std::cout << "Custom constructor"<< std::endl;;
    }
    

    int NumberSeries::min() const noexcept {return _min;}
    int NumberSeries::max() const noexcept {return _max;}

    NumberSeries NumberSeries::operator+(const series::NumberSeries &other) const {
        return NumberSeries{addVectors(_series, other._series), std::min(other._min, _min), std::max(other._max, _max)};
    }
    
    inline NumberSeries NumberSeries::create_random_vector(size_t size, int min, int max){
        std::mt19937 mt(std::random_device{}());
        std::uniform_int_distribution<int> dist(min, max);

        auto vec = std::vector<int>(size);
        auto _min = max;
        auto _max = min;
        for (int i = 0; i < size; ++i) {
            int random_number = dist(mt);
            _min = std::min(random_number, _min);
            _max = std::max(random_number, _max);
            vec.at(i) = random_number;
        }
        return NumberSeries{std::move(vec), _min, _max};
    }

    NumberSeries NumberSeries:: MakeRandom(std::size_t size) //Should use int instead???
    {
        constexpr auto MIN = INT32_MIN;
        constexpr auto MAX = INT32_MAX;
        return create_random_vector(size, MIN, MAX);
    }
    
    NumberSeries NumberSeries::MakeRandom(std::size_t size, int min, int max) {
        return create_random_vector(size, min, max);
    }


    NumberSeries &NumberSeries::operator+=(const NumberSeries &other) {
        _series = addVectors(_series, other._series);
        return *this;
    }

    std::vector<int> NumberSeries::addVectors(const std::vector<int> &first, const std::vector<int> &second) {
        const std::vector<int> big_series = first.size() > second.size() ? first : second;
        const std::vector<int> small_series = first == big_series ? second : first;
        auto elements = std::vector<int>(big_series.size());

        //for each element in the smaller set, add elements from the larger set
        for (int i = 0; i < small_series.size(); ++i)
            elements.at(i) = first.at(i) + second.at(i);

        //for the remaining elements in the large set, add them to the elements without any element-wise addition.
        for (auto i = small_series.size(); i < big_series.size(); ++i)
            elements.at(i) = big_series.at(i);

        return elements;
    }

    bool NumberSeries::operator<(const NumberSeries &other) const {
        return (_max - _min) > (other._max - other._min);
    }

    std::ostream &operator<<(std::ostream &os, const NumberSeries &series) {
        os << "Number series at " << std::addressof(series) << "  with vector "
        << std::addressof(series._series) << " with vector ranging from "  //NOTICE! The object has same address as the vector!
        << series._min <<" to " << series._max << std::endl << " {";

        for (int element : series._series) 
            os << element << ", ";
        for (auto const& val: series._series)
          os << val << ",";
        
        os << "}" << std::endl;
        return os;
    }


}  