//
// Created by rasmu on 28/02/2023.
//

#include "visitor.h"
void matlang::const_t::accept(matlang::visitor &v) {
v.visit(*this);
}

