//
// Created by rasmus on 5/30/2023.
//
#include "reactionNetwork.h"

std::ostream& operator<<(std::ostream& ostream, const ReactionNetwork& value) {
    ostream << "{";
    for (const Reaction& reaction : value) {
        ostream << value << ", ";
    }
    return ostream << "}\n";
}
std::string ReactionNetwork::to_graphviz_string() const
{
    std::stringstream outString;
    outString << "digraph Reaction {\n";

    for(size_t i = 0; i < reactions.size(); ++i){
        const Reaction& reaction =reactions[i];
        outString << "    R" << i
                  << " [label=\""
                  << reaction.getLambda()
                  << " \", shape=box,style=filled,fillcolor=white];\n";
    }

    for (size_t i = 0; i < reactions.size(); ++i) {
        const auto& reaction = reactions[i];
        for (const auto& lhs : reaction.getConsumptions()){
            outString << "    " << lhs.getName() << " -> R" << i << " [color=red];\n";

        }

        for (const auto& rhs : reaction.getProductionActions())
            outString << "    R" << i << " -> " << rhs.getName() << " [color=blue];\n";

    }

    outString << "}\n";
    return outString.str();
}
