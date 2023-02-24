//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_VAR_T_H
#define CALCULATOR_VAR_T_H


#include "term_t.h"

class var_t : public term_t  {
    size_t id;
    //Must call super constructor
public:
    var_t(const var_t&) = default;
    var_t& operator=(const var_t&) = default;
    /** returns the value of the variable stored in a state */
    double operator()(state_t& s) override { return s[id]; }
    /** evaluates an assignment to a given expression and returns the resulting value */
    double operator()(state_t& s, term_t& term) const{
        s[id] = (term(s));
        return s[id];
    }
    friend class symbol_table_t;

/** only friends are allowed to construct variable instances */
explicit var_t(size_t id): term_t(), id{id} {}
};
#endif //CALCULATOR_VAR_T_H
