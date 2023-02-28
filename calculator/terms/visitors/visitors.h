//
// Created by rasmu on 28/02/2023.
//

#ifndef CALCULATOR_VISITORS_H
#define CALCULATOR_VISITORS_H
#include <utility>
#include <map>

#include "../term_visitor.h"

namespace matlang::visitor{
    class evaluator : public term_visitor {
        std::shared_ptr<term_t::state_t> state;
        double result = 0;
        
    public:
        evaluator(std::shared_ptr<term_t::state_t> s){
            state = std::move(s);
        }
        inline double visit(matlang::const_t &node) override{
            return node.get_value();            
        }
        
        inline double visit(matlang::var_t &node) override{
            return (*state)[node.get_id()];
        }        
        
        double visit(matlang::assign_t &node) override;
        double visit(matlang::binary_t &node) override;
        double visit(matlang::unary_t &node) override;
    };

    class printer : public term_visitor{
        std::ostream& ostream;

    public:
        printer(std::ostream& s) : ostream{s}{}
        double visit(matlang::assign_t &node) override;
        double visit(matlang::binary_t &node) override;
        double visit(matlang::const_t &node) override;
        double visit(matlang::unary_t &node) override;
        double visit(matlang::var_t &node) override;
    };
}
#endif //CALCULATOR_VISITORS_H
