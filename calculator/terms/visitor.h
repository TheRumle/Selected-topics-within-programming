//
// Created by rasmu on 27/02/2023.
//

#ifndef CALCULATOR_VISITOR_H
#define CALCULATOR_VISITOR_H


#include "assign_t.h"
#include "const_t.h"
#include "binary_t.h"
#include "unary_t.h"

namespace matlang{
    struct visitor {
        virtual double visit(matlang::const_t& node) = 0;
        virtual double visit(matlang::binary_t& node) = 0;
        virtual double visit(matlang::unary_t& node) = 0;
        virtual double visit(matlang::assign_t& node) = 0;
        virtual double visit(matlang::var_t& node) = 0;
    };
}


#endif //CALCULATOR_VISITOR_H
