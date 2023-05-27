//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_AGENTS_H
#define LAMBDAS_AGENTS_H
#include <string>

    
struct Agent{
    virtual ~Agent() = default;
    double volume{};
    std::string name;
    Agent(std::string  name, double volume): volume(volume), name(std::move(name)) {}
    static std::string tostring(const Agent& agent){
        if (agent.volume == 0)
            return agent.name;
        else
            return "" + std::to_string(agent.volume) + agent.name;
    }
};

struct Product:Agent {
    Product(const std::string& name, double volume): Agent(name, volume) {}
    friend std::ostream &operator << (std::ostream& s, const Product& value){
        s << tostring(value);
    }
};

struct Reactant:Agent {
    Reactant(const std::string& name, double volume): Agent(name, volume) {}
    friend std::ostream &operator << (std::ostream& s, const Reactant& value){
       s << tostring(value);
       return s;
    }
};

#endif  // LAMBDAS_AGENTS_H
