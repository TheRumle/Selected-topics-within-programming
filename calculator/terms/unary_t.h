//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_UNARY_T_H
#define CALCULATOR_UNARY_T_H


#include <memory>
#include <utility>
#include "term_t.h"
#include "op_t.h"
#include "assign_t.h"

class unary_t : public term_t {

private:
    enum op_t op;
    std::shared_ptr<term_t> value;
public:
    unary_t(std::shared_ptr<term_t> value, op_t  op) : value{std::move(value)}, op{op} {
    }
    double operator()(term_t::state_t& state) override{
        switch(op) {
        case plus:
            return (*value)(state);
        case minus:
           return -(*value)(state);
        case assign:
            return 0;
        }
    }

};


#endif //CALCULATOR_UNARY_T_H
