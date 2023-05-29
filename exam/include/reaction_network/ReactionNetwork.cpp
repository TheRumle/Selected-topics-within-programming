#include "ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
std::ostream& operator<<(std::ostream& s, const ReactionNetwork& value) {
    if (!value.reactions.empty()) {
        auto lastReaction = value.reactions.end() - 1;
        for (auto it = value.reactions.begin(); it != lastReaction; ++it) {
            s << *it << ",";
        }
        s << *lastReaction;
    }
    
    return s;
}
