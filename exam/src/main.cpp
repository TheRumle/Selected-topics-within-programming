﻿//
// Created by rasmus on 5/26/2023.
//

#include "reaction/rule.h"
#include "simulation.h"
#include "reaction/reaction.h"
int main() {
    auto lhs = LHS {{{"A",1}, {"C",1}}};
    auto rhs = RHS {{{"B",1}, {"C",1}}};
    const Rule& rule = lhs >>= rhs;
    
    
    reaction r(rule, 0.001);
    std::cout << r;
    
    auto s = symbol_table<std::string, double>{};

    Agent A = Agent{"A", 100};
    Agent B = Agent{"B", 0};
    Agent C = Agent{"C", 1};
    
    s.store(A.name, A.volume);
    s.store(B.name, B.volume);
    s.store(C.name, C.volume);
    
    simulation q {{r},s};
    q.operator()(1500);
    return 0;
}

