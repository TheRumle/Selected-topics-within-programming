﻿#include "agents.h"
//
// Created by rasmus on 5/31/2023.
//
std::ostream& operator<<(std::ostream& s, const Agent& agent)
{
    if (agent.totalAgent == 1)
        s << agent.agentName;
    else
        s << std::to_string(agent.totalAgent) + agent.agentName;
    s << " ";
    return s;
}
Agent& Agent::operator=(const Agent& other)
{
    if (this != &other) {
        agentName = other.agentName;
        totalAgent = other.totalAgent;
    }
    return *this;
}
Agent& Agent::operator=(Agent&& other) noexcept
{
    if (this != &other) {
        agentName = std::move(other.agentName);
        totalAgent = other.totalAgent;
    }
    return *this;
}
