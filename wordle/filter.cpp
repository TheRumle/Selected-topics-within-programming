//
// Created by rasmu on 26/02/2023.
//

#include "filter.h"

static bool same_spot(const  &token, std::string word) {
    return word[token.position()] == token.character();
}

