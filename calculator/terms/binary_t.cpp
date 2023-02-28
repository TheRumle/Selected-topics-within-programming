//
// Created by rasmu on 24/02/2023.
//



#include "term_t.h"
#include "binary_t.h"
#include "term_visitor.h"


inline double matlang::binary_t::accept(term_visitor &v) {
    return v.visit(*this);
}
