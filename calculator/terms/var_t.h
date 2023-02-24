//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_VAR_T_H
#define CALCULATOR_VAR_T_H


#include "term_t.h"

class var_t : public term_t  {
    size_t id;
public:
    var_t(const var_t&) = default;
    var_t& operator=(const var_t&) = default;
    inline
    double operator()(state_t& s) override { return s[id]; }
    inline 
    double operator()(state_t& s, term_t& term) const{
        s[id] = (term(s));
        return s[id];
    }

    explicit var_t(size_t id): term_t(), id{id} {}
};
#endif //CALCULATOR_VAR_T_H
