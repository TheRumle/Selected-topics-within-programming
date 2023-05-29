//
// Created by rasmus on 5/29/2023.
//

#include "ReactionNetworkRunner.h"
std::ostream& operator<<(std::ostream& s, const ReactionNetworkRunner& value) {
    for (const std::pair<const double, std::vector<Agent>>& stateAtTime : value.stateHistory) {
        s << stateAtTime.first << ": { ";
        for (const auto& agent : stateAtTime.second) {
            s << agent;
        }
        s << " } \n";
    }
    return s;
}
const ReactionNetworkRunner::state_history& ReactionNetworkRunner::getStateHistory() const { return stateHistory; }
const std::vector<std::shared_ptr<Agent>>& ReactionNetworkRunner::getAgents() const { return agents; }
