//
// Created by rasmu on 28/02/2023.
//
#include "visitor.h"

void matlang::assign_t::accept(visitor &v) {
    v.visit(*this);
}

