//
// Created by rasmus on 5/26/2023.
//

/**
 * 1. Use operator overloading to support the reaction rule typesetting directly in C++ code. 
 * This could be done by overloading -, + and cout for reactants. overload () for the simulation
 * 2. Pretty print for simulation
 * 
 */


#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H
#include <string>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

struct Reactant {
    std::string name;
    double volume{};
    Reactant(const std::string& name, double volume): name(name), volume(volume) {}
    
};




template<typename TKey, typename TValue>
struct symbol_table{
    std::map<TKey, TValue> state{};
    
    void store( const TKey& key, const TValue& value) {
        state.emplace(key, value);
    };
  
    
    TValue lookup(const TKey& key) const {
        auto it = state.find(key);
        if (it == state.end())
            throw std::invalid_argument("Key was not contained in state");
        
        return (it->second);
    };
};

class Reaction {
public:
    const double lambda{};
    std::vector<Reactant> reactants{};
    std::vector<Reactant> products{};

    Reaction(double lambda, std::vector<Reactant> reactants, std::vector<Reactant> products)
        : lambda(lambda), reactants(std::move(reactants)), products(std::move(products))
    {
        
    }

};


class sim{
public:
    struct ReactantAdditionContainer
    {

        
        Reactant& reactant;

        ReactantAdditionContainer(Reactant& reactant): reactant(reactant)
        {
        }
        
        
        ReactantAdditionContainer operator=(const ReactantAdditionContainer& other){
            this->reactant.volume += other.reactant.volume;
            return *this;
        }
        
        
        inline double volume() const {
            return reactant.volume;
        }
        inline std::string name() const {
            return reactant.name;
        }
    };
public:
    using simulation_state = symbol_table<std::string, ReactantAdditionContainer>;
    
    simulation_state state{};
    explicit sim(simulation_state  startState) : state(std::move(startState)) {
        
    }
    
    
    double computeDelay(const Reaction& first){
        auto res = 1.0;
        for (const auto q : first.reactants) {
            res *= q.volume;
        }
        
        auto d = first.lambda * 1;
        std::random_device rd;
        std::mt19937 gen(rd());
 
        // if particles decay once per second on average,
        // how much time, in seconds, until the next one?
        std::exponential_distribution<> q(d);
        return q(gen);
    }
    
    double time = 0;
    
    void simulate(const std::vector<Reaction>& reactions, double endTime){
        while (time < endTime){
            auto fastest_reaction= *std::min_element(reactions.begin(), reactions.end(),
            [&](const Reaction& first,const Reaction& second)//Danger when capturing 
                {
                    return computeDelay(first) < computeDelay(second) ;
                });

            time += computeDelay(fastest_reaction);
            if (canMakeReaction(fastest_reaction)){
                performReaction(fastest_reaction);
            }

            for (const auto a : state.state) {
                std::cout << "time: " << time << "   " << a.first << ',' << a.second.volume() << "   ";
            }
            std::cout << std::endl;
        }
    }
    
    void performReaction(const Reaction& reaction){
        for (const auto& r : reaction.reactants) {
            //For the state of the system, remove state
            auto s = state.lookup(r.name);
            s.reactant.volume -= 1;
        }
        for (const auto& r : reaction.products) {
            //For the state of the system, remove state
            auto s = state.lookup(r.name);
            s.reactant.volume += r.volume;
        }
        
    }
    
    bool canMakeReaction(const Reaction& reaction) const{
        for (const auto& reactant : reaction.reactants){
            const auto currentR = state.lookup(reactant.name);
            auto currentValue = currentR.volume();
            
            if (currentValue < reactant.volume) 
                return false;
        }
        return true;
    }
    
    friend std::ostream& operator << (std::ostream& os, sim a) {
        os << "TODO";
        return os;
    }
};



#endif  // LAMBDAS_REACTION_H
