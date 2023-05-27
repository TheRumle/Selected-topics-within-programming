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
    symbol_table<std::string, double> state;
    
    simulation(const std::initializer_list<reaction>& reactions, symbol_table<std::string, double>& agentValues):
        reactions(reactions), state(agentValues)
    {};
    friend std::ostream & operator << (std::ostream& s, const simulation& value){
        s <<"{ ";
        for (const auto& r : value.state.state){
            s << r.second << " ";
        }
        s << "}\n";
        return s;
    }
    
    void operator()(double endTime){
        double time = 0.0;
        while (time < endTime){
            reaction& fastestReaction = reactions.at(0);
            double fastestTime = fastestReaction.compute_delay(state);
            for (size_t i = 1; i < reactions.size(); ++i) {
                reaction& r = reactions.at(i);
                if (fastestReaction.canBeSatisfied(state)){
                    auto foundTime = r.compute_delay(state);
                    if (fastestTime > foundTime){
                        fastestReaction = r;
                        fastestTime = foundTime;
                    }
                }
            }
            
            time += fastestTime;
            fastestReaction.operator()(state);
            std::cout << *this;
        }

    }
    


};

#endif  // LAMBDAS_SIMULATION_H
