//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_AGENTS_H
#define LAMBDAS_AGENTS_H
#include <string>


class Agent{
public:
    virtual ~Agent() = default;
    Agent(const Agent& other) = default;
    Agent(const Agent&& other) : agent_name(other.agent_name), total_agent(other.total_agent)
    {}
    
    Agent(std::string  name, double volume): agent_name(std::move(name)), total_agent(volume) {}
    
    
    friend std::ostream &operator << (std::ostream& s, const Agent& agent){
        if (agent.total_agent == 1)
            s << agent.agent_name;
        else
            s << std::to_string(agent.total_agent) + agent.agent_name;
        s << " ";
    }
    
    static std::shared_ptr<Agent> CreateShared(const std::string& name, double startValue= 1){
        return std::make_shared<Agent>(Agent{name, startValue});
    }
    static std::shared_ptr<Agent> CreateShared(const Agent&& agent){
        return std::make_shared<Agent>(Agent{agent.agent_name, agent.total_agent});
    }
    
    inline void increment(){ total_agent +=1;}
    
    inline void add(double amount){total_agent += amount;}
    
    inline double total_amount(){
        return total_agent;
    }
    const std::string agent_name;
    
private:
    double total_agent{};
};


class AgentConsumption{
private:
    double amount{};
    std::string name{};
    std::shared_ptr<Agent> agent{};
    static std::ostream& toString(std::ostream& s, const AgentConsumption& agent){
        if (agent.amount == 1)
            s << agent.name;
        else
            s << std::to_string(agent.amount) + agent.name;
        s << " ";
        return s;
    }
public:
    double getAmount() const { return amount; }
    const std::string& getName() const { return name; }
    const std::shared_ptr<Agent>& getAgent() const { return agent; };

    AgentConsumption(const std::shared_ptr<Agent>& agent, double amount): amount(amount), name(agent->agent_name), agent(agent){}
    AgentConsumption(const std::shared_ptr<Agent>& agent): amount(1), name(agent->agent_name), agent(agent){}
    AgentConsumption(const AgentConsumption& other):amount(other.amount), name(other.name), agent(other.agent){}
    
    AgentConsumption& operator= (const AgentConsumption& other){
        this->agent=other.agent;
        this->amount=other.amount;
        this->name=other.name;
        return *this;
    }
    
    friend std::ostream &operator << (std::ostream& s, const AgentConsumption& agent){
        return toString(s, agent);
    }
};

class AgentProduction {
public:
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
    double getAmount() const { return amount; }
    const std::string& getName() const { return name; }
    const std::shared_ptr<Agent>& getAgent() const { return agent; };
    
    AgentProduction(const std::shared_ptr<Agent>& agent, double amount): amount(amount), name(agent->agent_name), agent(agent){}
    AgentProduction(const std::shared_ptr<Agent>& agent): amount(1), name(agent->agent_name), agent(agent){}
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
};

#endif  // LAMBDAS_AGENTS_H
