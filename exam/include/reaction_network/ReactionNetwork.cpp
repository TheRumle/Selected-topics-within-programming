#include "ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
std::ostream& operator<<(std::ostream& s, const ReactionNetwork& value)
{
    s << value.time <<":  { ";
    for (const auto& r : value.state){
        if (r.second == 0)
            continue ;
        s << r.first <<'(' <<r.second << ")";
    }
    s << "} ";
    return s;
}
