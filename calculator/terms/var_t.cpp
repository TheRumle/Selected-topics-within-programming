//
// Created by rasmu on 28/02/2023.
//

#include "term_visitor.h"
inline double matlang::var_t::accept(matlang::term_visitor &v) {
    return v.visit(*this);
}

