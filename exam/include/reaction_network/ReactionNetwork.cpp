#include "ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
std::ostream& operator<<(std::ostream& s, const ReactionNetwork& value) {
    if (!value.reactions.empty()) {
            s << "ReactionNetwork: time = " << value.time << ", reactions = [";
            for (const auto& reaction : value.reactions)
            {
                s << reaction << ", ";
            }
            s << "]";
            return s;
    }
    
    return s;
}
