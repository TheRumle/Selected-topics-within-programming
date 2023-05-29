//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_AGENTS_H
#define LAMBDAS_AGENTS_H
#include <string>
#include <memory>


class Agent{
public:
    virtual ~Agent() = default;
    Agent(const Agent& other) : agent_name(other.agent_name), total_agent(other.total_agent) {
        // Copy constructor implementation
    }
    
    Agent(Agent&& other) noexcept : agent_name(std::move(other.agent_name)), total_agent(std::move(other.total_agent)) {
        // Move constructor implementation
    }

    Agent(std::string name, double volume) : agent_name(std::move(name)), total_agent(volume) {
        // Constructor implementation
    }
    
    
    friend std::ostream &operator << (std::ostream& s, const Agent& agent){
        if (agent.total_agent == 1)
            s << agent.agent_name;
        else
            s << std::to_string(agent.total_agent) + agent.agent_name;
        s << " ";
        return s;
    }
    
    static std::shared_ptr<Agent> CreateShared(const std::string& name, double startValue= 1){
        return std::make_shared<Agent>(Agent{name, startValue});
    }
    static std::shared_ptr<Agent> CreateShared(const Agent&& agent){
        return std::make_shared<Agent>(Agent{agent.agent_name, agent.total_agent});
    }
    
    inline void increment(){ total_agent +=1;}
    inline void add(double amount){total_agent += amount;}
    
    inline void decrement(){ total_agent -=1;}
    inline void remove(double amount){total_agent -= amount;}
    
    inline double total_amount() const{
        return total_agent;
    }
    inline std::string getAgentName() const{
        return agent_name;
    }
    
private:
    std::string agent_name;
    double total_agent{};
};


class AgentConsumption{
private:
    double amount{};
    std::string name{};
    std::shared_ptr<Agent> globalAgent{};
    static std::ostream& toString(std::ostream& s, const AgentConsumption& agent){
        if (agent.amount == 1)
            s << agent.name;
        else
            s << std::to_string(agent.amount) + agent.name;
        s << " ";
        return s;
    }
public:
    [[nodiscard]] double getConsumptionAmount() const { return amount; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] double getAgentAmount() const { return this->globalAgent->total_amount() ; }

    AgentConsumption(const std::shared_ptr<Agent>& agent, double amount): amount(amount), name(agent->getAgentName()), globalAgent(agent){}
    AgentConsumption(const std::shared_ptr<Agent>& agent): amount(1), name(agent->getAgentName()), globalAgent(agent){}
    AgentConsumption(const AgentConsumption& other):amount(other.amount), name(other.name), globalAgent(other.globalAgent){}
    
    AgentConsumption& operator= (const AgentConsumption& other){
        this->globalAgent =other.globalAgent;
        this->amount=other.amount;
        this->name=other.name;
        return *this;
    }
    
    friend std::ostream &operator << (std::ostream& s, const AgentConsumption& agent){
        return toString(s, agent);
    }
    
    [[nodiscard]] bool canBePerformed() const{
        return (this->globalAgent->total_amount() >= this->amount);
    }
    
    void operator()() const {
        this->globalAgent->remove(this->amount);
    }
};

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
    AgentProduction(const AgentProduction& other):amount(other.amount), name(other.name), agent(other.agent){}
    
    AgentProduction& operator= (const AgentProduction& other){
        this->agent=other.agent;
        this->amount=other.amount;
        this->name=other.name;
        return *this;
    }
    
    friend std::ostream &operator << (std::ostream& s, const AgentProduction& agent){
        return toString(s, agent);
    }
    
    void operator()() const {
        this->agent->add(this->amount);
    }
};

#endif  // LAMBDAS_AGENTS_H
