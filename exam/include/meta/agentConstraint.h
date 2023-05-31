//
// Created by rasmus on 5/30/2023.
//

#ifndef EXAM2023_AGENTCONSTRAINT_H
#define EXAM2023_AGENTCONSTRAINT_H
#include <valarray>

template <typename T>
concept AgentActionConstraint = std::is_base_of_v<AgentAction, T>;

#endif  // EXAM2023_AGENTCONSTRAINT_H
