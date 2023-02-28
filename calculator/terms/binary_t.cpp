//
// Created by rasmu on 24/02/2023.
//



#include "term_t.h"
#include "binary_t.h"
#include "visitor.h"


double matlang::binary_t::operator()(matlang::term_t::state_t &state) {
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

inline void matlang::binary_t::accept(visitor &v) {
    v.visit(*this);
}
