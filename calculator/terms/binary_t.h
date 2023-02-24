//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_BINARY_T_H
#define CALCULATOR_BINARY_T_H


#include <stdexcept>
#include <memory>
#include <utility>
#include "term_t.h"
#include "const_t.h"

class binary_t : public term_t{
    std::shared_ptr<term_t> f;
    std::shared_ptr<term_t> s;
public:
    enum bin_ops { plus, minus, mul, divide} op;
    binary_t(const double val, std::shared_ptr<term_t>second, bin_ops oprator)
            : f{std::make_shared<const_t>(const_t{val})}, s{std::move(second)} {
        op = oprator;
    }

    binary_t(std::shared_ptr<term_t>first, std::shared_ptr<term_t>second, bin_ops oprator):
            f{std::move(first)}, s{std::move(second)}, op{oprator}  { //efficient moving or better to use const ref?
    }
    double operator()(term_t::state_t& state) override;
};

#endif //CALCULATOR_BINARY_T_H
