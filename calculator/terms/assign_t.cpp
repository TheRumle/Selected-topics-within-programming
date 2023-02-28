//
// Created by rasmu on 28/02/2023.
//
#include "term_visitor.h"

inline double matlang::assign_t::accept(term_visitor &v) {
    return v.visit(*this);
}

