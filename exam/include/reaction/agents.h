//
// Created by rasmus on 5/26/2023.
//

#ifndef EXAM2023_AGENTS_H
#define EXAM2023_AGENTS_H
#include <string>
#include <memory>
#include "vector"


class Agent{
public:
    
    
    
    struct P_Container
    {
        std::shared_ptr<Agent> p_agent;
        P_Container(const Agent& agent): p_agent(std::make_shared<Agent>(agent)){}
        P_Container(const Agent&& agent): p_agent(std::make_shared<Agent>(agent)){}
        
        inline void add(double amount) const { p_agent->totalAgent += amount;}
    
        inline void remove(double amount) const { p_agent->totalAgent -= amount;}
    
        inline double getTotalAmountAgent() const{
            return p_agent->totalAgent;
        }
        inline std::string getAgentName() const{
            return p_agent->agentName;
        }
        
        std::vector<P_Container> operator+(const P_Container&& other) const{
            P_Container r(other);
            return {{*this, r}};
        }
        
        std::vector<P_Container> operator+(const P_Container& other) const {
            P_Container r(other);
            return {{*this, r}};
        }
        
        std::vector<P_Container>& operator+(std::vector<P_Container>& vector){
            vector.emplace_back(*this);
            return vector;
        }
        struct ToRule{
            const Agent::AgentComposition& lhs;
            const Agent::AgentComposition& rhs;
            ToRule(const Agent::AgentComposition& lhs,const Agent::AgentComposition& rhs)
                :lhs(lhs), rhs(rhs){}
        };
        
        ToRule operator >>=(Agent::AgentComposition& other){
            return {*this, other};
        }
        ToRule operator >>=(Agent::AgentComposition&& other){
            return {*this, other};
        }
    };
    
    
    
    
    
    virtual ~Agent() = default;
    Agent(const Agent& other) = default;
    
    Agent(Agent&& other) noexcept = default;

    Agent(std::string name, double volume) : agentName(std::move(name)), totalAgent(volume) {
        // Constructor implementation
    }
    
    
    friend std::ostream &operator << (std::ostream& s, const Agent& agent);
    
    Agent& operator=(const Agent& other);
    
    Agent& operator=(Agent&& other) noexcept;
    
    static P_Container CreateShared(const std::string& name, double startValue= 1){
        return {Agent{name, startValue}};
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
