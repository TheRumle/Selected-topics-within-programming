//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_BINARY_T_H
#define CALCULATOR_BINARY_T_H


#include <stdexcept>
#include <memory>
#include "const_t.h"


namespace matlang {
    class binary_t : public matlang::term_t{
        std::shared_ptr<term_t> f;
        std::shared_ptr<term_t> s;
    public:
        enum bin_ops { plus, minus, mul, divide} op;
        binary_t(const double val, std::shared_ptr<term_t>second, bin_ops oprator)
                : f{std::make_shared<const_t>(const_t{val})}, s{std::move(second)} {
            op = oprator;
        }
        
        std::shared_ptr<term_t> get_lhs(){
            return f; 
        }
        std::shared_ptr<term_t> get_rhs(){
            return s;
        }
    
        binary_t(std::shared_ptr<term_t>first, std::shared_ptr<term_t>second, bin_ops oprator):
                f{std::move(first)}, s{std::move(second)}, op{oprator}  { //efficient moving or better to use const ref?
        }
        double accept(matlang::visitor &v) override;
    };
}

#endif //CALCULATOR_BINARY_T_H
