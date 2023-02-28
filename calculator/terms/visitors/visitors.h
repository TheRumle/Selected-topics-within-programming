//
// Created by rasmu on 28/02/2023.
//

#ifndef CALCULATOR_VISITORS_H
#define CALCULATOR_VISITORS_H
#include <utility>
#include <map>

#include "../term_visitor.h"

namespace matlang::visitors{
    class evaluator : public term_visitor {
        std::shared_ptr<term_t::state_t> state;
        double result = 0;
        
    public:
        evaluator(std::shared_ptr<term_t::state_t> s){
            state = std::move(s);
        }
        
        double visit(matlang::assign_t &node) override{
            //an assignment is essentially two operations
            auto a =  node.get_term()->accept(*this);
            auto id = node.get_var()->get_id();
            (*state)[id] = a;
            return a;
        }

        double visit(matlang::binary_t &node) override{
            double lhs = node.get_lhs()->accept(*this);
            double rhs = node.get_rhs()->accept(*this);
            
            switch (node.op) {
                case binary_t::mul: {
                    return  rhs * lhs;
                }
                case binary_t::divide: {
                    if (rhs == 0)
                        throw std::logic_error{"division by zero"};
                    return lhs/rhs;
                }
                case binary_t::plus:
                    return lhs + rhs;
                case binary_t::minus:
                    return lhs - rhs;
            }
        }

        double visit(matlang::const_t &node) override{
            return node.get_value();            
        }

        double visit(matlang::unary_t &node) override{
            switch (node.op) {
                case unary_t::minus:
                    return - node.get_value()->accept(*this);
                case unary_t::plus:
                case unary_t::assign:
                    return node.get_value()->accept(*this);
            }
            return (*node.get_value()).accept(*this);
        }
        double visit(matlang::var_t &node) override{
            return (*state)[node.get_id()];
        }        
    };

    class printer : public term_visitor{
        std::ostream& ostream;

    public:
        printer(std::ostream& s) : ostream{s}{}
        double visit(matlang::assign_t &node) override{
            ostream << "Assignment: ";
            (*node.get_term()).accept(*this);
            return 0;
        }

        double visit(matlang::binary_t &node) override{
            ostream << " binary node consisting of a ";
            node.get_lhs()->accept(*this);
            ostream <<" and ";
            node.get_rhs()->accept(*this);
            return 0;
        }

        double visit(matlang::const_t &node) override{
            ostream << " constant value of " << node.get_value();
            return 0;
        }

        double visit(matlang::unary_t &node) override{
            (*node.get_value()).accept(*this);
            return 0;
        }
        double visit(matlang::var_t &node) override{
            ostream << node.get_id();
            return 0;
        }
    };
}
#endif //CALCULATOR_VISITORS_H
