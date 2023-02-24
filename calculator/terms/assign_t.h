//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_ASSIGN_T_H
#define CALCULATOR_ASSIGN_T_H


#include <memory>
#include <utility>
#include "term_t.h"
#include "var_t.h"

class assign_t : public term_t {
    std::shared_ptr<var_t> var;
    std::shared_ptr<term_t> term;
public:
    explicit assign_t(std::shared_ptr<var_t>  variable, const std::shared_ptr<term_t> &term)
    :term{term}, var{std::move(variable)}
    {
        //Clang suggests to pass by value and then move.
        // Why is that better than using const & as I have done with term?
    }

    //inline simple methods
    inline double operator()(state_t& s) override{
        return (*var)(s, (*term));
    }
};

#endif //CALCULATOR_ASSIGN_T_H
