//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_AGENTS_H
#define LAMBDAS_AGENTS_H
#include <string>

    
struct Agent{
    virtual ~Agent() = default;
    double volume{};
    const std::string name;
    Agent(std::string  name, double volume): volume(volume), name(std::move(name)) {}
    Agent(const Agent& other): volume(other.volume), name(other.name) {}
    
    static std::string tostring(const Agent& agent){
        if (agent.volume == 1)
            return agent.name;
        else
            return "" + std::to_string(agent.volume) + agent.name;
    }
    
    friend std::ostream &operator << (std::ostream& s, const Agent& value){
        s << tostring(value);
        return s;
    }
    
};

const static Agent ENV{"ENV", -1}; 

#endif  // LAMBDAS_AGENTS_H
