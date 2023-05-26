//
// Created by rasmus on 5/26/2023.
//
#include <iostream>
#include "../include/benchmark/benchmark.h"

#include <algorithm>
#include "reaction/Reaction.h"
int main() {
    sim::simulation_state state;
    auto as =Reactant("A", 100);
    auto bs =Reactant("B", 0);
    auto cs =Reactant("C", 2);
    
    state.store(as.name, sim::ReactantAdditionContainer{as});
    state.store(bs.name, sim::ReactantAdditionContainer{bs});
    state.store(cs.name, sim::ReactantAdditionContainer{cs});
    
    Reaction reaction 
        {0.001, std::vector<Reactant>{Reactant("A", 1),Reactant("C", 1)},
         std::vector<Reactant>{Reactant("B", 1), Reactant("C", 1)}};
    
    sim s{state};
    s.simulate(std::vector<Reaction>{reaction}, 1500);
    
    
    return 0;
}

