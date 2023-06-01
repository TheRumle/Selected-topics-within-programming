//
// Created by rasmus on 5/29/2023.
//

#ifndef EXAM2023_AGENTOPERATIONS_H
#define EXAM2023_AGENTOPERATIONS_H
#include "agents.h"

class AgentAction {
protected:
    double amount{};
    std::string name{};
    Agent::P_Container agent;
    
    static std::ostream& toString(std::ostream& s, const AgentAction& action) {
        if (action.amount == 1)
            s << action.name;
        else
            s << std::to_string(action.amount) + action.name;
        s << " ";
        return s;
    }

public:
    AgentAction(const Agent::P_Container& agent, double amount) 
        : amount(amount), name(agent.getAgentName()), agent(agent) {}
    
    AgentAction(const Agent::P_Container& agent) 
        : amount(1), name(agent.getAgentName()), agent(agent) {}
    
    AgentAction(const AgentAction& other) = default;
    AgentAction(AgentAction&& other) noexcept = default;
    AgentAction& operator=(const AgentAction& other) = default;
    AgentAction& operator=(AgentAction&& other) noexcept = default;
    virtual ~AgentAction() = default;

    [[nodiscard]] double getAmount() const { return amount; }
    [[nodiscard]] const std::string getName() const { return name; }
    [[nodiscard]] const Agent::P_Container& getAgent() const { return agent; }

    friend std::ostream& operator<<(std::ostream& s, const AgentAction& action) {
        return toString(s, action);
    }

    virtual void operator()() const = 0;
    
    template <typename ActionType>
    static std::vector<ActionType> FromRule(const std::vector<Agent::P_Container>& elements) {
        std::vector<ActionType> res;
        for (const auto& value : elements) {
            res.emplace_back(ActionType{ value, 1 });
        }
        return res;
    }
};


class AgentConsumption : public AgentAction {
public:
    using AgentAction::AgentAction; //brings the ctors from the base class AgentAction into this one

    [[nodiscard]] double getAgentAmount() const { return this->agent.getTotalAmountAgent(); }
    [[nodiscard]] bool canBePerformed() const {
        return (this->agent.getTotalAmountAgent() >=    this->amount);
    }

    void operator()() const override {
        this->agent.remove(1);
    }
};


class AgentProduction : public AgentAction {
public:
    using AgentAction::AgentAction; //brings the ctors from the base class AgentAction into this one
    
    void operator()() const override {
        this->agent.add(1);
    }
};

#endif  // EXAM2023_AGENTOPERATIONS_H
