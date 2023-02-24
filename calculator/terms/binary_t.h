//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_BINARY_T_H
#define CALCULATOR_BINARY_T_H


#include <stdexcept>
#include <memory>
#include <utility>
#include "term_t.h"
#include "op_t.h"
#include "const_t.h"

class binary_t : public term_t{
    std::shared_ptr<term_t> f;
    std::shared_ptr<term_t> s;
    op_t op;

public:
    
    binary_t(const double val, std::shared_ptr<term_t>second, op_t oprator) 
    : f{std::make_shared<const_t>(const_t{val})}, s{std::move(second)} {
        op = oprator;
    }

    binary_t(std::shared_ptr<term_t>first, std::shared_ptr<term_t>second, op_t oprator):
        f{std::move(first)}, s{std::move(second)}  { //efficient moving!
        op = oprator;
    }
    double operator()(term_t::state_t& state) override  {
        switch(op) {
            case mul: {
                return   (*f)(state) * (*s)(state);
            }
            case divide: {
                return  (*f)(state) / (*s)(state);
            }
            case plus:
                return (*f)(state) + (*s)(state);
            case minus:
                return (*f)(state) - (*s)(state);
        }
    }
};


#endif //CALCULATOR_BINARY_T_H
