﻿//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_TERM_T_H
#define CALCULATOR_TERM_T_H

#include <vector>

namespace matlang{
    class visitor;
    class term_t{
    protected:
    
    public:
        using state_t = std::vector<double>;
        term_t() = default;
        virtual ~term_t() noexcept = default;
        virtual double operator()(state_t& state) = 0; //=0 is pure virtual 
        virtual void accept(visitor& v) = 0;
    };
}


#endif //CALCULATOR_TERM_T_H
