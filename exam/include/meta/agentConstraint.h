//
// Created by rasmus on 5/30/2023.
//

#ifndef EXAM2023_AGENTCONSTRAINT_H
#define EXAM2023_AGENTCONSTRAINT_H
#include <valarray>

template<typename T>
concept AgentActionConcept = requires(T action, SymbolTable<std::string, double>& state) {
                                 { action.getAmount() } -> std::convertible_to<double>; //must have amount of double
                                 { action.getAgentName() } -> std::convertible_to<const std::string&>; //must provide name of agent
                                 { action(state) } -> std::same_as<void>; //must be able to be executable given some state
                             };

#endif  // EXAM2023_AGENTCONSTRAINT_H
