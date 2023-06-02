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
        
        struct Rule
        {
            const std::vector<Agent::P_Container> lhs;
            const std::vector<Agent::P_Container> rhs;
            Rule(const std::vector<Agent::P_Container>& lhs,const std::vector<Agent::P_Container>& rhs)
                :lhs(lhs), rhs(rhs){}
        };
        
        struct Composite {
            std::vector<P_Container> elements{};
            //"Rule of Zero", therefore no assign
            Composite() = default;
            Composite(const Composite& other) = default;
            Composite(Composite&& other) = default;
            
            Composite(const std::vector<P_Container>& elements)
                : elements(elements)
            {}

            Composite(std::vector<P_Container>&& elements)
                : elements(std::move(elements))
            {}
            
            Composite(const P_Container& other)
                : elements({other})
            {}
    

            Rule operator >>=(const Composite& other) const{
                return Rule{{this->elements}, {other.elements}};
            }
            Rule operator >>=(const Composite&& other) const{
                return Rule{{this->elements}, other.elements};
            }
            Rule operator >>=(const P_Container& other) const{
                return Rule{{this->elements}, {other}};
            }
            Rule operator >>=(const P_Container&& other) const{
                return Rule{{this->elements}, {other}};
            }
        };
        
        Composite operator+(const P_Container& other) const{
            return {std::vector<P_Container>{{*this,other}}};
        }

        Rule operator>>=(const P_Container& other) const{
            return {std::vector<P_Container>{*this}, {other}};
        }
        Rule operator>>=(const Composite& other) const{
            return {std::vector<P_Container>{*this},other.elements};
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
    
    static P_Container CreateShared(const std::string& name, double startValue= 0){
        return {Agent{name, startValue}};
    }
    inline void add(double amount){ totalAgent += amount;}
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
