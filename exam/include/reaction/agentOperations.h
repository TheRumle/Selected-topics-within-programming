//
// Created by rasmus on 5/29/2023.
//

#include "agents.h"
#ifndef LAMBDAS_AGENTOPERATIONS_H
#define LAMBDAS_AGENTOPERATIONS_H

#endif  // LAMBDAS_AGENTOPERATIONS_H
class AgentProduction {
private:
    double amount{};
    std::string name{};
    std::shared_ptr<Agent> agent{};
    static std::ostream& toString(std::ostream& s, const AgentProduction& agent){
        if (agent.amount == 1)
            s << agent.name;
        else
            s << std::to_string(agent.amount) + agent.name;
        s << " ";
        return s;
    }
public:
    [[nodiscard]] double getAmount() const { return amount; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] const std::shared_ptr<Agent>& getAgent() const { return agent; };
    
    AgentProduction(const std::shared_ptr<Agent>& agent, double amount): amount(amount), name(agent->getAgentName()), agent(agent){}
    AgentProduction(const std::shared_ptr<Agent>& agent): amount(1), name(agent->getAgentName()), agent(agent){}
    AgentProduction(const AgentProduction& other) = default;
    
    AgentProduction& operator= (const AgentProduction& other){
        if (this == &other)
            return *this;  // Avoid self-assignment
        
    
        this->agent = other.agent;
        this->amount = other.amount;
        this->name = other.name;
        return *this;
    }
    
    friend std::ostream &operator << (std::ostream& s, const AgentProduction& agent){
        return toString(s, agent);
    }
    
    void operator()() const {
        this->agent->add(this->amount);
    }
};