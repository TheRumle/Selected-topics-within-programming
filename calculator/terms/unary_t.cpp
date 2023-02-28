//
// Created by rasmu on 24/02/2023.
//


#include "term_visitor.h"

inline double matlang::unary_t::accept(matlang::term_visitor &v) {
    return v.visit(*this);
}
