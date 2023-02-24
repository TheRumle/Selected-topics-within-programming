//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_ASSIGN_T_H
#define CALCULATOR_ASSIGN_T_H


#include <memory>
#include <utility>
#include "term_t.h"
#include "op_t.h"
#include "var_t.h"

class assign_t : public term_t {
    std::shared_ptr<var_t> var;
    std::shared_ptr<term_t> term;
public:
    explicit assign_t(const std::shared_ptr<var_t> var, std::shared_ptr<term_t> term)
    : var(std::move(var)), term{std::move(term)}
    {
        
    }

    double operator()(state_t& s) override{
        auto variable = (*var);
        return variable.operator()(s, (*term));
    }
};

#endif //CALCULATOR_ASSIGN_T_H
