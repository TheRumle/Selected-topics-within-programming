//
// Created by rasmu on 28/02/2023.
//
#include "var_t.h"
#include "visitor.h"
void matlang::var_t::accept(matlang::visitor &v) {
    v.visit(*this);
}

