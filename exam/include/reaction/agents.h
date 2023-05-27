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

class AgentAction{
protected:
    const std::shared_ptr<Agent> agent{};
    static std::ostream& toString(std::ostream& s, const AgentAction& agent){
        if (agent.amount == 1)
            s << agent.name;
        else
            s << std::to_string(agent.amount) + agent.name;
        s << " ";
        return s;
    }
public:
    const double amount{};
    const std::string name{};
    
    AgentAction(std::shared_ptr<Agent>& agent, double amount): agent(agent),amount(amount), name(agent->agent_name){}
    AgentAction(std::shared_ptr<Agent> agent): agent(agent),amount(1), name(agent->agent_name){}
    AgentAction(const AgentAction& other): agent(other.agent), amount(other.amount), name(agent->agent_name){}
    

    
};

class AgentConsumption : public AgentAction{
public:
    AgentConsumption(std::shared_ptr<Agent>& agent, double amount):
        AgentAction(agent,amount)
    {
        
    }
    AgentConsumption(const std::shared_ptr<Agent> agent):
        AgentAction(agent){}
    
    AgentConsumption(const AgentConsumption& other):
        AgentAction(other){}
    
    AgentConsumption operator= (const AgentConsumption& other){
        return AgentConsumption{other.agent};
    } 
    
    friend std::ostream &operator << (std::ostream& s, const AgentConsumption& agent){
        return toString(s, agent);
    }
};

class AgentProduction: public AgentAction{
public:
    AgentProduction(std::shared_ptr<Agent>& agent, double amount):
        AgentAction(agent,amount)
    {
        
    }
    AgentProduction(const std::shared_ptr<Agent> agent):
        AgentAction(agent){}
    
    AgentProduction(const AgentProduction& other):
        AgentAction(other){}
    
    AgentProduction operator= (const AgentProduction& other){
        return AgentProduction{other.agent};
    } 
    
    
    friend std::ostream &operator << (std::ostream& s, const AgentProduction& agent){
        return toString(s, agent);
    }
};

#endif  // LAMBDAS_AGENTS_H
