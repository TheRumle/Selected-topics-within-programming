//
// Created by rasmu on 15/02/2023.
//

#ifndef NUMBERSERIES_NUMBERSERIES_H
#define NUMBERSERIES_NUMBERSERIES_H


#include <utility>
#include <vector>
#include <iosfwd>
#include <iostream>

namespace series {

    class NumberSeries {
    public:
        NumberSeries(std::vector<int> series, int min, int max) noexcept;


        //copy constructor so must implement the destructor and copy assignment too.  Copy assignment is ok as is. Destructor is okay as is.
        NumberSeries(const NumberSeries& other) noexcept;

        ~NumberSeries() = default;
        NumberSeries& operator= (const NumberSeries &other)= default;
        //No need to implement move constructor explicitly - default is memberwise move. Default move for vector is okay.
        static NumberSeries MakeRandom(std::size_t size);
        static NumberSeries MakeRandom(std::size_t size, int min, int max);
        int min() const noexcept;
        int max() const noexcept;
        /**
         * Add series element wise and appends remaining elements to structure.
         * Does not modify existing structure. 
         */
        NumberSeries operator+(const NumberSeries &other) const;
        bool operator<(const NumberSeries &other) const;
        /**
         * Add series element wise and appends remaining elements to structure.
         * Does not modify existing structure
         */
        NumberSeries& operator+=(const NumberSeries &other);
        friend std::ostream &operator<<(std::ostream &os, const NumberSeries &series);

    private:
        static NumberSeries create_random_vector(size_t size, int min, int max);
        std::vector<int> _series = std::vector<int>{};
        int _min{0};
        int _max{0};
        static std::vector<int> addVectors(const std::vector<int>& first,
                                      const std::vector<int>& second);
    };


}
#endif //NUMBERSERIES_NUMBERSERIES_H
