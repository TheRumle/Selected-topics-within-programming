//
// Created by rasmus on 5/29/2023.
//

#include "reactionNetworkSimulator.h"

const ReactionNetwork& ReactionNetworkSimulator::getNetwork() const { return network; }

std::pair<Reaction, double> 
    ReactionNetworkSimulator::findFastestValidReaction()
{
    std::vector<std::pair<Reaction, double>> validReactionTimes{};
    for (const auto& reaction : network) {
        if (reaction.canBeSatisfied())
            validReactionTimes.emplace_back(reaction, reaction.compute_delay());
    }
    
    for (auto it = validReactionTimes.begin(); it != validReactionTimes.end(); ++it) {
        for (auto innerIt = validReactionTimes.begin(); innerIt != validReactionTimes.end() - 1; ++innerIt) {
            auto& lhs = *innerIt;
            auto& rhs = *(innerIt + 1);

            if (lhs.second > rhs.second) {
                std::swap(lhs, rhs);
            }
        }
    }

    return validReactionTimes.front();
}
