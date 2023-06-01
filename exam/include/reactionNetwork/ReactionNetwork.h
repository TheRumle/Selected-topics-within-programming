//
// Created by rasmus on 5/26/2023.
//

#ifndef EXAM2023_REACTIONNETWORK_H
#define EXAM2023_REACTIONNETWORK_H

#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include "reaction/constructionRules.h"
#include "reaction/reaction.h"
#include "meta/agentConstraint.h"

class ReactionNetwork
{
    SymbolTable<std::string, std::shared_ptr<Agent>> agentsTable{};
    double time = 0.0;
    std::vector<Reaction> reactions{};
    std::vector<std::shared_ptr<const Agent>> _agents{}; 
    
    template <AgentActionConstraint T>
    void addAgentsToSTable(const std::vector<T>& actions) {
        for (const T& action : actions) {
            const Agent::P_Container agent = action.getAgent();
            agentsTable.storeOrUpdate(agent.getAgentName(), agent.p_agent);
        }
    }
    
    void findAgentsForReactions(){
        for (const auto& reaction : reactions) {
            addAgentsToSTable(reaction.getProductionActions());
            addAgentsToSTable(reaction.getConsumptions());
        }
        std::vector<std::shared_ptr<const Agent>> agents{};
        for (const auto& agent : agentsTable) {
            agents.emplace_back(agent.second);
        }
        _agents = std::move(agents);
    }
    
public:
    using state = std::vector<std::shared_ptr<const Agent>>; //For all other purposes, only the network
    
    // Constructor taking an initializer list of reactions
    ReactionNetwork(const std::initializer_list<Reaction>& reactions) : reactions(reactions)
    {
        findAgentsForReactions();
    }

    ReactionNetwork(const std::vector<Reaction>& reactions) : reactions(reactions)
    {
        findAgentsForReactions();
    }

    // Default constructor
    ReactionNetwork() = default;
    // Copy constructor
    ReactionNetwork(const ReactionNetwork& other) = default;
    // Move constructor
    ReactionNetwork(ReactionNetwork&& other) noexcept = default;
    // Destructor
    ~ReactionNetwork() = default;

    // Copy assignment operator
    ReactionNetwork& operator=(const ReactionNetwork& other)
    {
        if (this != &other)
        {
            time = other.time;
            reactions = other.reactions;
            this->agentsTable = other.agentsTable;
            this->_agents = other._agents;
        }
        return *this;
    }

    // Move assignment operator
    ReactionNetwork& operator=(ReactionNetwork&& other) noexcept
    {
        if (this != &other)
        {
            time = std::move(other.time);
            reactions = std::move(other.reactions);
        }
        return *this;
    }
    auto begin()  { return reactions.begin(); }
    auto end() { return reactions.end(); }
    auto begin() const { return reactions.begin(); }
    auto end() const { return reactions.end(); }

    friend std::ostream& operator<<(std::ostream& s, const ReactionNetwork& value);
    
    std::string to_graphviz_string() const;
    
    /// Only exposes constant _agents. Noone should modify but the network itself.
    /// \return 
    std::vector<std::shared_ptr<const Agent>> getAgents() const {
        return _agents;
    }
};



#endif  // EXAM2023_REACTIONNETWORK_H
