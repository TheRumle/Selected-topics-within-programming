#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
void performSimulation(const Agent& A,const Agent& B,const Agent& C){
    auto lambda = 0.001;
    auto endTime = 1500;
    reaction r (LHS{{{"A",1}, {"C",1}}} >>= {{{"B",1}, {"C",1}}, lambda});
    std::cout << r;
    
    auto s = reaction::state{};
    s.storeOrUpdate(A.name, A.volume);
    s.storeOrUpdate(B.name, B.volume);
    s.storeOrUpdate(C.name, C.volume);

    ReactionNetwork q {{r},s};
    q.operator()(endTime);
}

void runFirstSimulation(){
    const Agent A = Agent{"A", 100};
    const Agent B = Agent{"B", 0};
    const Agent C = Agent{"C", 1};
    performSimulation(A,B,C);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
    
}
void runSecondSimulation()
{
   
    const Agent A = Agent{"A", 100};
    const Agent B = Agent{"B", 0};
    const Agent C = Agent{"C", 2};
    performSimulation(A,B,C);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
}

void runThirdSimulation()
{
    const Agent A = Agent{"A", 50};
    const Agent B = Agent{"B", 50};
    const Agent C = Agent{"C", 1};
    performSimulation(A,B,C);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
}

int main(){
    runFirstSimulation();
    runSecondSimulation();
    runThirdSimulation();
    return 0;
}
