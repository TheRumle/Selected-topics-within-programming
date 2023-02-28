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
        virtual void visit(matlang::const_t& node) = 0;
        virtual void visit(matlang::binary_t& node) = 0;
        virtual void visit(matlang::unary_t& node) = 0;
        virtual void visit(matlang::assign_t& node) = 0;
        virtual void visit(matlang::term_t& node) = 0;
        virtual void visit(matlang::var_t& node) = 0;
    };
}

namespace matlang::visitors{
    class printer : public visitor{
    public:
        void visit(matlang::assign_t &node) override{}
        void visit(matlang::binary_t &node) override{}
        void visit(matlang::const_t &node) override{}
        void visit(matlang::term_t &node) override{}
        void visit(matlang::unary_t &node) override{}
        void visit(matlang::var_t &node) override{}
    };
}


#endif //CALCULATOR_VISITOR_H
