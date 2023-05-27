//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_SIMULATION_H
#define LAMBDAS_SIMULATION_H

#include "reaction/rule.h"
#include "reaction/reaction.h"
struct simulation {
    std::vector<reaction> reactions;
    symbol_table<std::string, Agent> state;
    
    simulation(std::vector<reaction> reactions, symbol_table<std::string, Agent>& agents):
        reactions(std::move(reactions)), state(agents)
    {};
    
    void operator()(double endTime){
        double time = 0.0;
        while (time < endTime){
            reaction& fastestReaction = reactions.at(0);
            double fastestTime = fastestReaction.compute_delay(state);
            for (size_t i = 1; i < reactions.size(); ++i) {
                reaction& r = reactions.at(i);
                if (fastestTime <r.compute_delay(state)){
                    fastestReaction = r;
                }
            }
            
            time+=fastestTime;
            if (fastestReaction.canBeSatisfied(state))
            {
                fastestReaction.operator()(state);
            }

            for (const auto& a : state.state) {
                std::cout << a.second.name << ": " << a.second.volume << ",   ";
            }
        }

    }
    
    
    

};

#endif  // LAMBDAS_SIMULATION_H
