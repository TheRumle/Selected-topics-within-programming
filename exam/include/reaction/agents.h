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
    Agent(const Agent& other) : agentName(other.agentName), totalAgent(other.totalAgent) {
        // Copy constructor implementation
    }
    
    Agent(Agent&& other) noexcept : agentName(std::move(other.agentName)), totalAgent(std::move(other.totalAgent)) {
        // Move constructor implementation
    }

    Agent(std::string name, double volume) : agentName(std::move(name)), totalAgent(volume) {
        // Constructor implementation
    }
    
    
    friend std::ostream &operator << (std::ostream& s, const Agent& agent){
        if (agent.totalAgent == 1)
            s << agent.agentName;
        else
            s << std::to_string(agent.totalAgent) + agent.agentName;
        s << " ";
        return s;
    }
    
    static std::shared_ptr<Agent> CreateShared(const std::string& name, double startValue= 1){
        return std::make_shared<Agent>(Agent{name, startValue});
    }
    static std::shared_ptr<Agent> CreateShared(const Agent&& agent){
        return std::make_shared<Agent>(Agent{agent.agentName, agent.totalAgent});
    }
    
    inline void increment(){ totalAgent +=1;}
    inline void add(double amount){ totalAgent += amount;}
    
    inline void decrement(){ totalAgent -=1;}
    inline void remove(double amount){ totalAgent -= amount;}
    
    inline double getTotalAmount() const{
        return totalAgent;
    }
    inline std::string getAgentName() const{
        return agentName;
    }
    
private:
    std::string agentName;
    double totalAgent{};
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
    [[nodiscard]] double getAgentAmount() const { return this->globalAgent->getTotalAmount() ; }

    AgentConsumption(const std::shared_ptr<Agent>& agent, double amount): amount(amount), name(agent->getAgentName()), globalAgent(agent){}
    AgentConsumption(const std::shared_ptr<Agent>& agent): amount(1), name(agent->getAgentName()), globalAgent(agent){}
    AgentConsumption(const AgentConsumption& other) = default;
    
    AgentConsumption& operator=(const AgentConsumption& other) {
        if (this == &other)
            return *this;  // Avoid self-assignment
        
    
        this->globalAgent = other.globalAgent;
        this->amount = other.amount;
        this->name = other.name;
        return *this;
    }
    
    friend std::ostream &operator << (std::ostream& s, const AgentConsumption& agent){
        return toString(s, agent);
    }
    
    [[nodiscard]] bool canBePerformed() const{
        return (this->globalAgent->getTotalAmount() >= this->amount);
    }
    
    void operator()() const {
        this->globalAgent->remove(this->amount);
    }
};



#endif  // LAMBDAS_AGENTS_H
