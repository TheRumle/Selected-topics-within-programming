//
// Created by rasmu on 24/02/2023.
//



#include "term_t.h"
#include "binary_t.h"
#include "visitor.h"


inline double matlang::binary_t::accept(visitor &v) {
    return v.visit(*this);
}
