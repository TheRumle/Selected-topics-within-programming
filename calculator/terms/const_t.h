﻿//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_CONST_T_H
#define CALCULATOR_CONST_T_H


#include "term_t.h"

class const_t: public term_t {
private:
    double value;
public:
    explicit const_t(double value) : value(value) {}
    const_t(int value) : value(value) {}

    //inline simple operations
    inline double operator()(state_t& _) override{
        return value;
    }
};


#endif //CALCULATOR_CONST_T_H
