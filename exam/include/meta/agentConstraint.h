//
// Created by rasmus on 5/30/2023.
//

#ifndef LAMBDAS_AGENTCONSTRAINT_H
#define LAMBDAS_AGENTCONSTRAINT_H
#include <valarray>

template <typename T>
constexpr bool is_string_v = std::is_same_v<std::remove_cvref_t<T>,std:: string>
                             || std::is_same_v<std::remove_cvref_t<T>, const char*>
                             || std::is_same_v<std::decay_t<T>, char*>;

template <typename T>
concept Container = requires(T&& a) //why use forward reference?
{
    {std::begin(a)};
    {std::end(a)};
} && !is_string_v<T>;

template <typename T>
concept AgentActionConstraint = std::is_base_of_v<AgentAction, T>;

#endif  // LAMBDAS_AGENTCONSTRAINT_H
