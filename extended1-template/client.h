//
// Created by rasmu on 17/02/2023.
//

#ifndef EXTENDED1_CLIENT_H
#define EXTENDED1_CLIENT_H

#include <memory>
#include "number_series.h"
#include <vector>
namespace data_series {
    class Client {
    public:
        Client(){
            _elem = fill_series();
        }
        // void sort(sort signature function as argument);
        
    private:
        static void fill_and_sort();
        static std::unique_ptr<std::vector<number_series>> fill_series();
        std::unique_ptr<std::vector<number_series>> _elem;
    };
}

#endif  // EXTENDED1_CLIENT_H
