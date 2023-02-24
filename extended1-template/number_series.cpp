/**
 * Definitions/implementation of some number_series methods
 */

#include "number_series.h"

#include <algorithm>
#include <iterator>
#include <random>
#include <functional>

namespace data_series
{
    number_series::number_series(const number_series&other) noexcept {
        _series = other._series;
        _min = other._min;
        _max = other._max;
    }

    number_series::number_series(std::vector<int> series, int min, int max) noexcept {
        _series = std::move(series);
        _min = min;
        _max = max;
    }
    

    int number_series::get_min() const noexcept {return _min;}
    int number_series::get_max() const noexcept {return _max;}

    number_series number_series::operator+(const data_series::number_series &other) const {
        return number_series{addVectors(_series, other._series), std::min(other._min, _min), std::max(other._max, _max)};
    }
    
    inline number_series number_series::create_random_vector(size_t size, int min, int max){
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
        return number_series{std::move(vec), _min, _max};
    }

    number_series number_series::make_random(std::size_t size) //Should use int instead???
    {
        constexpr auto MIN = INT32_MIN;
        constexpr auto MAX = INT32_MAX;
        return create_random_vector(size, MIN, MAX);
    }

    number_series number_series::MakeRandom(std::size_t size, int min, int max) {
        return create_random_vector(size, min, max);
    }

    number_series& number_series::operator+=(const number_series&other) {
        _series = std::move(addVectors(_series, other._series));
        return *this;
    }

    std::vector<int> number_series::addVectors(const std::vector<int> &first, const std::vector<int> &second) {
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

    bool number_series::operator<(const number_series&other) const {
        return (_max - _min) < (other._max - other._min);
    }

    std::ostream &operator<<(std::ostream &os, const number_series&series) {
        os << "Number series at " << std::addressof(series) << "  with vector "
           << std::addressof(series._series) << " with vector ranging from "  //NOTICE! The object has same address as the vector!
           << series._min <<" to " << series._max << std::endl << " {";

        for (const int& element : series._series) 
            os << element << ", ";
        for (auto const& val: series._series)
            os << val << ",";
        
        os << "}" << std::endl;
        return os;
    }
    void number_series::add_value(const int valu) noexcept {
        _min = std::min(valu, _min);
        _max = std::max(valu, _max);
        _series.push_back(valu);
    }
    number_series::number_series() {
        _series = std::vector<int>();
        _min = INT32_MAX;
        _max = INT32_MIN;
    }
    size_t number_series::size() const noexcept { return _series.size(); }
    number_series::number_series(const std::initializer_list<int>& elems) {
        _series = std::vector<int>(elems);
        for (auto val: _series) {
            _min = std::min(val, _min);
            _max = std::max(val, _max);
        }
    }
    int number_series::amplitude() const noexcept { return _max - _min; }
    number_series& number_series::operator=(number_series&& other) noexcept {
        std::swap(other._series, _series); //good practice is to postpone deletion of other's members until its destruction
        std::swap(_max, other._max);
        std::swap(_min, other._min);
        return *this;    }
}  // namespace data_series
