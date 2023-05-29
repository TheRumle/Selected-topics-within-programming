//
// Created by rasmus on 5/29/2023.
//

#include "reactionNetworkSimulator.h"
std::ostream& operator<<(std::ostream& s, const ReactionNetworkSimulator& value) {
    for (const std::pair<const double, std::vector<Agent>>& stateAtTime : value.stateHistory) {
        s << stateAtTime.first << ": { ";
        for (const auto& agent : stateAtTime.second) {
            s << agent;
        }
        s << " } \n";
    }
    return s;
}
const ReactionNetworkSimulator::state_history& ReactionNetworkSimulator::getStateHistory() const { return stateHistory; }
const std::vector<std::shared_ptr<Agent>>& ReactionNetworkSimulator::getAgents() const { return agents; }
const ReactionNetwork& ReactionNetworkSimulator::getNetwork() const { return network; }
