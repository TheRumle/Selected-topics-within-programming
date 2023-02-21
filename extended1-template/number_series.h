/**
 * Definitions of number_series and number_series_wrap classes.
 */

#ifndef INCLUDE_NUMBER_SERIES_H
#define INCLUDE_NUMBER_SERIES_H

#include <vector>
#include <limits>
#include <memory>
#include <iostream>
#include <algorithm>

namespace data_series
{
    class number_series
    {
    public:
        number_series();
        number_series(std::vector<int> series, int min, int max) noexcept;
        [[nodiscard]] size_t size() const noexcept;

        //copy constructor so must implement the destructor and copy assignment too.  Copy assignment is ok as is. Destructor is okay as is.
        number_series(const number_series& other) noexcept;
        number_series(const std::initializer_list<int>& values);
        
        ~number_series() = default;
        number_series& operator= (const number_series&other)= default;
        number_series& operator= (number_series&&other) noexcept;
        //No need to implement move constructor explicitly - default is memberwise move. Default move for vector is okay.
        static number_series make_random(std::size_t size);
        static number_series MakeRandom(std::size_t size, int min, int max);
        [[nodiscard]] int get_min() const noexcept;
        [[nodiscard]] int get_max() const noexcept;
        /**
         * Add series element wise and appends remaining elements to structure.
         * Does not modify existing structure. 
         */
        number_series operator+(const number_series&other) const;
        bool operator<(const number_series&other) const;
        /**
         * Add series element wise and appends remaining elements to structure.
         * Does not modify existing structure
         */
        number_series& operator+=(const number_series&other);
        void add_value(int value) noexcept;
        friend std::ostream &operator<<(std::ostream &os, const number_series&series);
        [[nodiscard]] int amplitude() const noexcept;

    private:
        static number_series create_random_vector(size_t size, int min, int max);
        std::vector<int> _series = std::vector<int>{};
        int _min{INT32_MAX};
        int _max{INT32_MIN};
        static std::vector<int> addVectors(const std::vector<int>& first,
                                           const std::vector<int>& second);
        
        int averages[200];
    };

    class number_series_wrap
    {
    private:
        explicit number_series_wrap(number_series series);
        std::unique_ptr<data_series::number_series> _series = std::make_unique<data_series::number_series>();
        inline void assign_shared(const data_series::number_series& series) {
            _series = std::make_unique<data_series::number_series>(series);
        }
    public:
        number_series_wrap(number_series_wrap&&other) noexcept;
        
        number_series_wrap(std::initializer_list<int> init);
        number_series_wrap();
            
        number_series_wrap(std::vector<int> series, int min, int max) noexcept;
            
        number_series_wrap(const data_series::number_series_wrap& other) noexcept;
            
        [[nodiscard]] size_t size() const noexcept;
            
        ~number_series_wrap() = default;
        number_series_wrap& operator= (const number_series_wrap&other);
        number_series_wrap& operator= (number_series_wrap&&other) noexcept;
            
        static number_series_wrap make_random(std::size_t size);
        [[nodiscard]] int get_min() const noexcept;
        [[nodiscard]] int get_max() const noexcept;
        /**
             * Add series element wise and appends remaining elements to structure.
             * Does not modify existing structure. 
         */
        number_series_wrap operator+(const number_series_wrap&other) const;
        bool operator<(const number_series_wrap&other) const;
        /**
             * Add series element wise and appends remaining elements to structure.
             * Does not modify existing structure
         */
        number_series_wrap& operator+=(const number_series_wrap&other);
        void add_value(int value) noexcept;
        [[nodiscard]] int amplitude() const noexcept;

        //int averages[120];
    };

}  // namespace data_series

#endif  // INCLUDE_NUMBER_SERIES_H
