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
};

struct Product:Agent {
    Product(const std::string& name, double volume): Agent(name, volume) {}
};

struct Reactant:Agent {
    Reactant(const std::string& name, double volume): Agent(name, volume) {}
};

#endif  // LAMBDAS_AGENTS_H
