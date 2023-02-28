//
// Created by rasmu on 28/02/2023.
//

#include "visitor.h"
inline double matlang::var_t::accept(matlang::visitor &v) {
    return v.visit(*this);
}

