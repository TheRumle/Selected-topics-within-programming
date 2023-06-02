#ifndef EXAM2023_AGENTCONSTRAINT_H
#define EXAM2023_AGENTCONSTRAINT_H
#include <valarray>

template<typename T>
concept AgentActionConcept = std::is_base_of_v<AgentAction, T> &&
                             requires(T action) {
                                 { action.getAmount() } -> std::convertible_to<double>; //must have amount of double
                                 { action.getName() } -> std::convertible_to<const std::string&>; //must provide name of agent
                                 { action() } -> std::same_as<void>; //must be able to be executable given some state
                             };

#endif  // EXAM2023_AGENTCONSTRAINT_H
