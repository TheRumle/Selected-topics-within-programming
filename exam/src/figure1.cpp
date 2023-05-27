#include <iostream>
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
void performSimulation(const std::shared_ptr<Agent>& A,
                       const std::shared_ptr<Agent>& B,
                       const std::shared_ptr<Agent>& C){
    auto lambda = 0.001;
    auto endTime = 1500;
    LHS lhs {{{A}, {C}}};
    reaction r ( lhs 
                >>=
                {{{B}, {C}}, lambda});
    std::cout << r;
    
    auto s = reaction::state{};
    s.storeOrUpdate(A->agent_name, A->total_amount());
    s.storeOrUpdate(B->agent_name, B->total_amount());
    s.storeOrUpdate(C->agent_name, C->total_amount());

    ReactionNetwork q {{r},s};
    q.operator()(endTime);
}

void runFirstSimulation(){
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 1);
    performSimulation(A,B,C);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
    
}
void runSecondSimulation()
{
   
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 2);
    performSimulation(A,B,C);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
}

void runThirdSimulation()
{
    const auto A = Agent::CreateShared(Agent{"A", 50});
    const auto B = Agent::CreateShared(Agent{"B", 50});
    const auto C = Agent::CreateShared("C", 1);
    performSimulation(A,B,C);
    std::cout << "///-------------------------END OF SIMULATION-------------------------///\n";
}

int main(){
    runFirstSimulation();
    runSecondSimulation();
    runThirdSimulation();
    return 0;
}
