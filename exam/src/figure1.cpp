#include <iostream>
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "reaction_network/ReactionNetwork.h"
//
// Created by rasmus on 5/27/2023.
//
void performSimulation(const std::shared_ptr<Agent>& A,
                       const std::shared_ptr<Agent>& B,
                       const std::shared_ptr<Agent>& C){
    auto lambda = 0.001;
    auto endTime = 1500;
    LHS lhs {{{A}, {C}}};
    RHS rhs {{{B}, {C}}, lambda};
    reaction r ( lhs >>= rhs);
    ReactionNetwork q {{r},{A,B,C}};
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
