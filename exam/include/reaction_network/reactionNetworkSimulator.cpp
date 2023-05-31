//
// Created by rasmus on 5/29/2023.
//

#include "reactionNetworkSimulator.h"

const ReactionNetwork& ReactionNetworkSimulator::getNetwork() const { return network; }

std::optional<std::pair<Reaction, double>> 
    ReactionNetworkSimulator::findFastestValidReaction()
{
    std::vector<std::pair<Reaction, double>> validReactionTimes{};
    for (const auto& reaction : network) {
        if (reaction.canBeSatisfied())
            validReactionTimes.emplace_back(reaction, reaction.compute_delay());
    }
    if (validReactionTimes.empty())
        return std::nullopt;;
    
    for (size_t i = 0; i < validReactionTimes.size(); ++i) {
        for (size_t j = 0; j < validReactionTimes.size() - 1; ++j) {
            std::pair<Reaction, double>& lhs = validReactionTimes[j];
            std::pair<Reaction, double>& rhs = validReactionTimes[j + 1];
            
            if (lhs.second > rhs.second) {
                std::swap(lhs, rhs);
            }
        }
    }

    return validReactionTimes.front();
}
