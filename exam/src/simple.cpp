#include <iostream>
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "reaction_network/ReactionNetwork.h"
#include "reaction_network/ReactionNetworkRunner.h"
//
// Created by rasmus on 5/27/2023.
//

ReactionNetworkRunner create_simulation(const std::shared_ptr<Agent>& A,
                       const std::shared_ptr<Agent>& B,
                       const std::shared_ptr<Agent>& C){
    auto lambda = 0.001;
    LHS lhs {{{A}, {C}}};
    RHS const rhs {{{B}, {C}}, lambda};
    reaction r ( lhs >>= rhs);
    ReactionNetwork network{{r}};
    
    return ReactionNetworkRunner {network, {A,B,C} };
}


ReactionNetworkRunner create_simulation1(){
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 1);
    auto lambda = 0.001;
    LHS lhs {{{A}, {C}}};
    RHS const rhs {{{B}, {C}}, lambda};
    reaction r ( lhs >>= rhs);
    ReactionNetwork network{{r}};
    return ReactionNetworkRunner {network, {A,B,C} };
}

ReactionNetworkRunner create_simulation2(){
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 2);
    auto lambda = 0.001;
    LHS lhs {{{A}, {C}}};
    RHS const rhs {{{B}, {C}}, lambda};
    reaction r ( lhs >>= rhs);
    ReactionNetwork network{{r}};
    return ReactionNetworkRunner {network, {A,B,C} };
}

ReactionNetworkRunner create_simulation1(){
    const auto A = Agent::CreateShared("A", 50);
    const auto B = Agent::CreateShared("B", 50);
    const auto C = Agent::CreateShared("C", 1);
    auto lambda = 0.001;
    LHS lhs {{{A}, {C}}};
    RHS const rhs {{{B}, {C}}, lambda};
    reaction r ( lhs >>= rhs);
    ReactionNetwork network{{r}};
    return ReactionNetworkRunner {network, {A,B,C} };
}

void performSimulation(const std::shared_ptr<Agent>& A,
                       const std::shared_ptr<Agent>& B,
                       const std::shared_ptr<Agent>& C){
    auto endTime = 1500;
    
    create_simulation(A,B,C)
        .operator()(endTime);
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
