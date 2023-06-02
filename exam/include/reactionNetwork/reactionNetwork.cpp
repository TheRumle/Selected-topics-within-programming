#include "reactionNetwork.h"

std::ostream& operator<<(std::ostream& ostream, const ReactionNetwork& value) {
    ostream << "{";
    auto it = value.begin();
    if (it != value.end()) {
        ostream << *it;
        ++it;
    }
    for (; it != value.end(); ++it) {
        ostream << ", " << *it;
    }
    return ostream << "}\n";
}

std::string ReactionNetwork::to_graphviz_string() const
{
    std::stringstream outString;
    outString << "digraph Reaction {\n";

    for(size_t i = 0; i < reactions.size(); ++i){
        const Reaction& reaction =reactions[i];
        outString << "    R" << i
                  << " [label=\""
                  << reaction.getLambda()
                  << " \", shape=box,style=filled,fillcolor=white];\n";
    }

    for (size_t i = 0; i < reactions.size(); ++i) {
        const auto& reaction = reactions[i];
        for (const auto& lhs : reaction.getConsumptions()){
            outString << "    " << lhs.getName() << " -> R" << i << " [color=red];\n";

        }

        for (const auto& rhs : reaction.getProductionActions())
            outString << "    R" << i << " -> " << rhs.getName() << " [color=blue];\n";

    }

    outString << "}\n";
    return outString.str();
}
void ReactionNetwork::findAgentsForReactions()
{
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
ReactionNetwork& ReactionNetwork::operator=(const ReactionNetwork& other)
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
ReactionNetwork& ReactionNetwork::operator=(ReactionNetwork&& other) noexcept
{
    if (this != &other)
    {
        time = std::move(other.time);
        reactions = std::move(other.reactions);
    }
    return *this;
}
template <AgentActionConcept T>

void ReactionNetwork::addAgentsToSTable(const std::vector<T>& actions)
{
    for (const T& action : actions) {
        const Agent::P_Container agent = action.getAgent();
        agentsTable.storeOrUpdate(agent.getAgentName(), agent.p_agent);
    }
}
