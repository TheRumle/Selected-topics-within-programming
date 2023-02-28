//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_UNARY_T_H
#define CALCULATOR_UNARY_T_H



#include <memory>
#include <utility>
#include "term_t.h"

namespace matlang {
    class unary_t : public matlang::term_t {

    private:
        std::shared_ptr<term_t> value;
    public:
        enum unary_op {
            plus, minus, assign
        } op;
        unary_t(std::shared_ptr<term_t> value, unary_op op) : value{std::move(value)}, op{op} 
        {}
        double operator()(term_t::state_t &state) override;
        void accept(matlang::visitor &v) override;
    };
    
}
#endif //CALCULATOR_UNARY_T_H
