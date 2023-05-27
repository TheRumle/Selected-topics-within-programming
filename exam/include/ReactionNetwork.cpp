#include "ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
std::ostream& operator<<(std::ostream& s, const ReactionNetwork& value)
{
    for (const auto& r : value.stateHistory){
        s << r.first <<":   {  " ;
        for (const auto& q : r.second) {
            s<<q <<" ";
        }
        s << " }\n";
    }
    s << "} ";
    return s;
}
