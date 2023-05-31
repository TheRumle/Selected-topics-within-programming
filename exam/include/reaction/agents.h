﻿//
// Created by rasmus on 5/26/2023.
//

#ifndef EXAM2023_AGENTS_H
#define EXAM2023_AGENTS_H
#include <string>
#include <memory>


class Agent{
public:
    virtual ~Agent() = default;
    Agent(const Agent& other) = default;
    
    Agent(Agent&& other) noexcept : agentName(std::move(other.agentName)), totalAgent(other.totalAgent) {
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
    
    Agent& operator=(const Agent& other) {
        if (this != &other) {
            agentName = other.agentName;
            totalAgent = other.totalAgent;
        }
        return *this;
    }
    
    Agent& operator=(Agent&& other) noexcept {
        if (this != &other) {
            agentName = std::move(other.agentName);
            totalAgent = other.totalAgent;
        }
        return *this;
    }
    
    static std::shared_ptr<Agent> CreateShared(const std::string& name, double startValue= 1){
        return std::make_shared<Agent>(Agent{name, startValue});
    }
    
    inline void increment(){ totalAgent +=1;}
    inline void add(double amount){ totalAgent += amount;}
    
    inline void decrement(){ totalAgent -=1;}
    inline void remove(double amount){ totalAgent -= amount;}
    
    inline double getTotalAmountAgent() const{
        return totalAgent;
    }
    inline std::string getAgentName() const{
        return agentName;
    }
    
private:
    std::string agentName;
    double totalAgent{};
};



#endif  // EXAM2023_AGENTS_H
