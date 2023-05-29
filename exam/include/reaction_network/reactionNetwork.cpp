#include "reactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
std::ostream& operator<<(std::ostream& s, const reactionNetwork& value) {
    if (!value.reactions.empty()) {
            s << "reactionNetwork: time = " << value.time << ", reactions = [";
            for (const auto& reaction : value.reactions)
            {
                s << reaction << ", ";
            }
            s << "]";
            return s;
    }
    return s;
}
