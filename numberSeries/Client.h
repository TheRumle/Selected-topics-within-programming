//
// Created by rasmu on 17/02/2023.
//

#ifndef NUMBERSERIES_CLIENT_H
#define NUMBERSERIES_CLIENT_H

#include <vector>
#include <memory>
#include <functional>
#include "NumberSeries.h"



namespace series {
    class Client {
    public:
        Client(){
            _elem = fill_series();
        }
        // void sort(sort signature function as argument);
        static benchmark_result run_benchmark(int num_times_bench);
    private:
        
        static void fill_and_sort();
        static std::unique_ptr<std::vector<NumberSeries>> fill_series();
        std::unique_ptr<std::vector<NumberSeries>> _elem;
    };
}

#endif //NUMBERSERIES_CLIENT_H
