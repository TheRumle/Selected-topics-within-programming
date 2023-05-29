//
// Created by rasmus on 5/29/2023.
//

#include <memory>
#include "reaction_network/ReactionNetworkRunner.h"
ReactionNetwork createNetwork(const std::shared_ptr<Agent>& A,
                              const std::shared_ptr<Agent>& B,
                              const std::shared_ptr<Agent>& C){
    auto lambda = 0.001;
    LHS lhs {{{A}, {C}}};
    RHS const rhs {{{B}, {C}}, lambda};
    reaction r ( lhs >>= rhs);
    return ReactionNetwork {{r}};
}

std::pair<ReactionNetwork, std::vector<std::shared_ptr<Agent>>> create1stSimpleNetwork() {
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 1);
    return {createNetwork(A, B, C), std::vector<std::shared_ptr<Agent>> {A, B, C}};
}

ReactionNetwork create2ndSimpleNetwork() {
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 2);
    return createNetwork(A, B, C);
}

ReactionNetwork create3rdSimpleNetwork() {
    const auto A = Agent::CreateShared("A", 50);
    const auto B = Agent::CreateShared("B", 50);
    const auto C = Agent::CreateShared("C", 2);
    return createNetwork(A, B, C);
}