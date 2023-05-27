//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_SIMULATION_H
#define LAMBDAS_SIMULATION_H

#include <functional>
#include "reaction/rule.h"
#include "reaction/reaction.h"
struct simulation {
    std::vector<reaction> reactions;
    symbol_table<std::string, Agent> state;
    
    simulation(std::vector<reaction> reactions, symbol_table<std::string, Agent>& agents):
        reactions(std::move(reactions)), state(agents)
    {};
    friend std::ostream & operator << (std::ostream& s, const simulation& value){
        s <<"{ ";
        for (const auto& r : value.state.state){
            s << Agent::tostring(r.second) << " ";
        }
        s << "}\n";
        return s;
    }
    
    void operator()(double endTime, std::function<void(const reaction&, const  symbol_table<std::string, Agent>& state)> monitorFunc){
        double time = 0.0;
        while (time < endTime){
            reaction& fastestReaction = reactions.at(0);
            double fastestTime = fastestReaction.compute_delay(state);
            for (size_t i = 1; i < reactions.size(); ++i) {
                reaction& r = reactions.at(i);
                auto foundTime = r.compute_delay(state);
                if (fastestTime < foundTime){
                    fastestReaction = r;
                    fastestTime = foundTime;
                }
            }
            
            time += fastestTime;
            if (fastestReaction.canBeSatisfied(state))
            {
                fastestReaction.operator()(state);
                std::cout << *this;
            }
        }

    }
    


};

#endif  // LAMBDAS_SIMULATION_H
