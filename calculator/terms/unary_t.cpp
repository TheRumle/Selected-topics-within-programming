//
// Created by rasmu on 24/02/2023.
//


#include "visitor.h"

inline double matlang::unary_t::accept(matlang::visitor &v) {
    return v.visit(*this);
}
