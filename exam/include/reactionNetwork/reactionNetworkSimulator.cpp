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
        return std::nullopt;
    
    std::sort(validReactionTimes.begin(), validReactionTimes.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });

    return validReactionTimes.front();
}

//REQ4
std::vector<std::shared_ptr<const Agent>> ReactionNetworkSimulator::stochasticSimulation(double endTime)
{
    while (time < endTime){
        const auto res = findFastestValidReaction();
        if (!res.has_value())
            break ;

        auto validReactionTimes = res.value();
        time += validReactionTimes.second;
        validReactionTimes.first.operator()();
    }
    return network.getAgents();
}
