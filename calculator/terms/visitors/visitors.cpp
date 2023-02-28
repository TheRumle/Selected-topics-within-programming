//
// Created by rasmu on 28/02/2023.
//

#include "visitors.h"

double matlang::visitor::evaluator::visit(matlang::assign_t &node) {
    auto a =  node.get_term()->accept(*this);
    auto id = node.get_var()->get_id();
    (*state)[id] = a;
    return a;
}

double matlang::visitor::evaluator::visit(matlang::binary_t &node) {
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

double matlang::visitor::evaluator::visit(matlang::unary_t &node) {
    switch (node.op) {
        case unary_t::minus:
            return - node.get_value()->accept(*this);
        case unary_t::plus:
        case unary_t::assign:
            return node.get_value()->accept(*this);
    }
    return (*node.get_value()).accept(*this);
}

double matlang::visitor::printer::visit(matlang::assign_t &node) {
    ostream << "Assignment: ";
    (*node.get_term()).accept(*this);
    return 0;
}

double matlang::visitor::printer::visit(matlang::binary_t &node) {
    ostream << " binary node consisting of a ";
    node.get_lhs()->accept(*this);
    ostream <<" and ";
    node.get_rhs()->accept(*this);
    return 0;
}

double matlang::visitor::printer::visit(matlang::const_t &node) {
    ostream << " constant value of " << node.get_value();
    return 0;
}

double matlang::visitor::printer::visit(matlang::unary_t &node) {
    (*node.get_value()).accept(*this);
    return 0;
}

double matlang::visitor::printer::visit(matlang::var_t &node) {
    ostream << node.get_id();
    return 0;
}
