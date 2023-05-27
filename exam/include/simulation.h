//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_SIMULATION_H
#define LAMBDAS_SIMULATION_H

#include <functional>
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"

class simulation {
private:
    double time = 0.0;

public:
    std::vector<reaction> reactions;
    reaction::state state;
    
    simulation(const std::initializer_list<reaction>& reactions, reaction::state& agentValues):
        reactions(reactions), state(agentValues)
    {};
    friend std::ostream & operator << (std::ostream& s, const simulation& value){
        s << value.time <<":  { ";
        for (const auto& r : value.state){
            if (r.second == 0)
                continue ;
            s << r.first <<'(' <<r.second << ")";
        }
        s << "} ";
        return s;
    }
    
    void print(const simulation& s, reaction& fastestReaction){
        std::cout << s << " by doing " << fastestReaction;
    }
    
    void operator()(double endTime){
        while (time < endTime){
            std::vector<std::pair<reaction, double>> reactionTimes{};
            for (auto& reaction :reactions) {
                reactionTimes.emplace_back(reaction, reaction.compute_delay(state));
            }
            
            for (auto it = reactionTimes.begin(); it != reactionTimes.end(); ++it) {
                for (auto innerIt = reactionTimes.begin(); innerIt != reactionTimes.end() - 1; ++innerIt) {
                    auto& lhs = *innerIt;
                    auto& rhs = *(innerIt + 1);
        
                    if (lhs.second > rhs.second) {
                        std::swap(lhs, rhs);
                    }
                }
            }

            
            auto& fastestReaction = reactionTimes.front();
            time += fastestReaction.second;
            fastestReaction.first.operator()(state);
            print(*this, fastestReaction.first);
        }
    }
};

#endif  // LAMBDAS_SIMULATION_H
