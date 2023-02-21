//
// Created by rasmu on 21/02/2023.
//

#include <utility>

#include "number_series.h"
namespace data_series
{

    data_series::number_series_wrap::number_series_wrap(std::initializer_list<int> init)
    {
        assign_shared(data_series::number_series{init});
    }
    data_series::number_series_wrap::number_series_wrap() { assign_shared(data_series::number_series{}); }
    data_series::number_series_wrap::number_series_wrap(std::vector<int> series, int min, int max) noexcept
    {
        assign_shared(data_series::number_series{std::move(series), min, max});
    }

    size_t data_series::number_series_wrap::size() const noexcept { return _series->size(); }
    data_series::number_series_wrap& data_series::number_series_wrap::operator=(const number_series_wrap& other)
    {
        *_series = *other._series;
        return *this;
    }
    data_series::number_series_wrap data_series::number_series_wrap::make_random(std::size_t size)
    {
        return number_series_wrap{data_series::number_series::make_random(size)};
    }

    data_series::number_series_wrap& data_series::number_series_wrap::operator=(number_series_wrap&& other) noexcept
    {
        std::swap(other._series, _series);
        return *this;
    }
    int data_series::number_series_wrap::get_min() const noexcept { return _series->get_min(); }
    int data_series::number_series_wrap::get_max() const noexcept { return _series->get_max(); }
    data_series::number_series_wrap data_series::number_series_wrap::operator+(const number_series_wrap& other) const
    {
        return number_series_wrap{other};
    }
    bool data_series::number_series_wrap::operator<(const number_series_wrap& other) const
    {
        return amplitude() < other.amplitude();
    }

    void data_series::number_series_wrap::add_value(int value) noexcept { _series->add_value(value); }

    data_series::number_series_wrap& data_series::number_series_wrap::operator+=(const number_series_wrap& other)
    {
        *_series += *other._series;
        return *this;
    }
    int data_series::number_series_wrap::amplitude() const noexcept { return _series->amplitude(); }
    data_series::number_series_wrap::number_series_wrap(data_series::number_series series)
    {
        *_series = std::move(series);
    }
    number_series_wrap::number_series_wrap(const data_series::number_series_wrap& other) noexcept
    {
        *_series = *other._series;
    }
    number_series_wrap::number_series_wrap(number_series_wrap&& other)  noexcept {
        _series = std::move(other._series);
    }
}
