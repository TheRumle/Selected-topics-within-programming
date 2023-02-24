//
// Created by rasmu on 24/02/2023.
//

#include "unary_t.h"

double unary_t::operator()(term_t::state_t &state) {
    switch(op) {
        case plus:
            return (*value)(state);
        case minus:
            return -(*value)(state);
        case assign:
            return 0;
    }
}
