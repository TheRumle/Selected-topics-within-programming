//
// Created by rasmu on 28/02/2023.
//
#include "visitor.h"

inline double matlang::assign_t::accept(visitor &v) {
    return v.visit(*this);
}

