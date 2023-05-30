//
// Created by rasmus on 5/29/2023.
//

#include "agents.h"
#ifndef LAMBDAS_AGENTOPERATIONS_H
#define LAMBDAS_AGENTOPERATIONS_H

#endif  // LAMBDAS_AGENTOPERATIONS_H
class AgentAction {
protected:
    double amount{};
    std::string name{};
    std::shared_ptr<Agent> agent{};
    
    static std::ostream& toString(std::ostream& s, const AgentAction& action) {
        if (action.amount == 1)
            s << action.name;
        else
            s << std::to_string(action.amount) + action.name;
        s << " ";
        return s;
    }

public:
    AgentAction(const std::shared_ptr<Agent>& agent, double amount) 
        : amount(amount), name(agent->getAgentName()), agent(agent) {}
    
    AgentAction(const std::shared_ptr<Agent>& agent) 
        : amount(1), name(agent->getAgentName()), agent(agent) {}
    
    AgentAction(const AgentAction& other) = default;
    AgentAction(AgentAction&& other) noexcept = default;
    AgentAction& operator=(const AgentAction& other) = default;
    AgentAction& operator=(AgentAction&& other) noexcept = default;
    virtual ~AgentAction() = default;

    [[nodiscard]] double getAmount() const { return amount; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] const std::shared_ptr<Agent>& getAgent() const { return agent; }

    friend std::ostream& operator<<(std::ostream& s, const AgentAction& action) {
        return toString(s, action);
    }

    virtual void operator()() const = 0;
};


class AgentConsumption : public AgentAction {
public:
    using AgentAction::AgentAction; //brings the ctors from the base class AgentAction into this one

    [[nodiscard]] double getAgentAmount() const { return this->agent->getTotalAmountAgent(); }
    [[nodiscard]] bool canBePerformed() const {
        return (this->agent->getTotalAmountAgent() >= this->amount);
    }

    void operator()() const override {
        this->agent->remove(this->amount);
    }
};


class AgentProduction : public AgentAction {
public:
    using AgentAction::AgentAction; //brings the ctors from the base class AgentAction into this one
    
    void operator()() const override {
        this->agent->add(this->amount);
    }
};