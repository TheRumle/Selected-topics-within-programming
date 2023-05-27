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
    Rule::state state;
    
    simulation(const std::initializer_list<reaction>& reactions, Rule::state& agentValues):
        reactions(reactions), state(agentValues)
    {};
    friend std::ostream & operator << (std::ostream& s, const simulation& value){
        s <<"{ ";
        for (const auto& r : value.state){
            s << r.second << " ";
        }
        s << "}\n";
        return s;
    }
    
    void operator()(double endTime){
        double time = 0.0;
        while (time < endTime){
            std::vector<reaction> satisfyables;
            for (auto& v : reactions) {
                if (v.canBeSatisfied(state))
                {
                    satisfyables.emplace_back(v);
                }
            }

            for (auto it = satisfyables.begin(); it != satisfyables.end(); ++it) {
                for (auto innerIt = satisfyables.begin(); innerIt != satisfyables.end() - 1; ++innerIt) {
                    auto& lhs = *innerIt;
                    auto& rhs = *(innerIt + 1);
        
                    if (lhs.compute_delay(state) > rhs.compute_delay(state)) {
                        std::swap(lhs, rhs);
                    }
                }
            }

            
            reaction& fastestReaction = satisfyables.front();
            time += fastestReaction.compute_delay(state);
            std::cout << fastestReaction;
            std::cout << *this;
            fastestReaction.operator()(state);
        }

    }
    


};

#endif  // LAMBDAS_SIMULATION_H
