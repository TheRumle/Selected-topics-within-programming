//
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
    
    auto s = symbol_table<std::string, Agent>{};
    
    Product A = Product{"A", 100};
    Product B = Product{"B", 0};
    Product C = Product{"C", 1};
    
    s.store({{A.name, A},{B.name, B}, {C.name, C} });
    
    simulation q {{r},s};
    q.operator()(100);
    return 0;
}

