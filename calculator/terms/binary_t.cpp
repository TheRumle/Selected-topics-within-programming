//
// Created by rasmu on 24/02/2023.
//

#include "binary_t.h"
double binary_t::operator()(term_t::state_t &state) {
    switch(op) {
        case mul: {
            return   (*f)(state) * (*s)(state);
        }
        case divide: {
            auto lhs = (*f)(state);
            auto rhs =  (*s)(state);
            if (rhs == 0)
                throw std::logic_error{"division by zero"};
            return lhs/rhs;
        }
        case plus:
            return (*f)(state) + (*s)(state);
        case minus:
            return (*f)(state) - (*s)(state);
    }
}