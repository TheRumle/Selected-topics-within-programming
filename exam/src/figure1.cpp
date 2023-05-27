#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "simulation.h"
//
// Created by rasmus on 5/27/2023.
//
void runFirstSimulation(){
    auto lambda = 0.001;
    auto endTime = 1500;
    reaction r ((LHS{{{"A",1}, {"C",1}}} >>= {{"B",1}, {"C",1}}), lambda);
    std::cout << r;
    
    auto s = reaction::state{};

    Agent A = Agent{"A", 100};
    Agent B = Agent{"B", 0};
    Agent C = Agent{"C", 1};
    s.storeOrUpdate(A.name, A.volume);
    s.storeOrUpdate(B.name, B.volume);
    s.storeOrUpdate(C.name, C.volume);    
    
    
    simulation q {{r},s};
    q.operator()(endTime);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
    
}
void runSecondSimulation()
{
    auto lambda = 0.001;
    auto endTime = 1500;
    auto lhs = LHS{{{"A", 1}, {"C", 1}}};
    auto rhs = RHS{{{"B", 1}, {"C", 1}}};
    const reaction& rule = lhs >>= rhs;

    reaction r(rule, lambda);
    std::cout << r;

    auto s = reaction::state{};

    Agent A = Agent{"A", 100};
    Agent B = Agent{"B", 0};
    Agent C = Agent{"C", 2};

    s.storeOrUpdate(A.name, A.volume);
    s.storeOrUpdate(B.name, B.volume);
    s.storeOrUpdate(C.name, C.volume);

    simulation q{{r}, s};
    q.operator()(endTime);
    
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
}

void runThirdSimulation()
{
    auto lambda = 0.001;
    auto endTime = 1500;
    auto lhs = LHS{{{"A", 1}, {"C", 1}}};
    auto rhs = RHS{{{"B", 1}, {"C", 1}}};
    const reaction& rule = lhs >>= rhs;

    reaction r(rule, lambda);
    std::cout << r;

    auto s = reaction::state{};

    Agent A = Agent{"A", 50};
    Agent B = Agent{"B", 50};
    Agent C = Agent{"C", 1};

    s.storeOrUpdate(A.name, A.volume);
    s.storeOrUpdate(B.name, B.volume);
    s.storeOrUpdate(C.name, C.volume);

    simulation q{{r}, s};
    q.operator()(endTime);
    
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
}

int main(){
    runFirstSimulation();
    runSecondSimulation();
    runThirdSimulation();
    
    return 0;
}
