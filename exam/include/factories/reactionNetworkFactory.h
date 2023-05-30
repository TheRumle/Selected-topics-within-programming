//
// Created by rasmus on 5/29/2023.
//

#include <memory>
#include <cmath>
#include "reaction_network/reactionNetworkSimulator.h"
ReactionNetwork createNetwork(const std::shared_ptr<Agent>& A,
                              const std::shared_ptr<Agent>& B,
                              const std::shared_ptr<Agent>& C){
    auto lambda = 0.001;
    LHS lhs {{{A}, {C}}};
    RHS const rhs {{{B}, {C}}, lambda};
    Reaction r ( lhs >>= rhs);
    return ReactionNetwork{{r}};
}

ReactionNetworkSimulator create1stSimpleSimulation() {
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 1);
    return {createNetwork(A, B, C)};
}



ReactionNetworkSimulator create2ndSimpleNetwork() {
    const auto A = Agent::CreateShared("A", 100);
    const auto B = Agent::CreateShared("B", 0);
    const auto C = Agent::CreateShared("C", 2);
    return {createNetwork(A, B, C)};
}

ReactionNetworkSimulator create3rdSimpleNetwork() {
    const auto A = Agent::CreateShared("A", 50);
    const auto B = Agent::CreateShared("B", 50);
    const auto C = Agent::CreateShared("C", 2);
    return {createNetwork(A, B, C)};
}

ReactionNetworkSimulator createCovidNetworkSimulation(double N) {
    
    
    const double eps = 0.0009; // initial fraction of infectious
    const auto I0 = double(std::round(eps*N)); // initial infectious
    const auto E0 = double(std::round(eps*N*15)); // initial exposed
    const double S0 = N-I0-E0; // initial susceptible
    const double R0 = 2.4; // basic reproductive number (initial, without lockdown etc)
    const double alpha = 1.0 / 5.1; // incubation rate (E -> I) ~5.1 days
    const double gamma = 1.0 / 3.1; // recovery rate (I -> R) ~3.1 days
    const double beta = R0 * gamma; // infection/generation rate (S+I -> E+I)
    const double P_H = 0.9e-3; // probability of hospitalization
    const double kappa = gamma * P_H*(1.0-P_H); // hospitalization rate (I -> H)
    const double tau = 1.0/10.12; // recovery/death rate in hospital (H -> R) ~10.12 days
    
    auto S = Agent::CreateShared("S", S0);
    auto E = Agent::CreateShared("E", E0);  
    auto I = Agent::CreateShared("I", I0);
    auto H = Agent::CreateShared("H", 0);
    auto R = Agent::CreateShared("R", 0);
    
    
    const std::initializer_list<Reaction> reactions = {
        Reaction(LHS {{S,I}} >>= {{E,I}, beta/N}), // susceptible becomes exposed through infectious
        Reaction(LHS  {{E}} >>= {{I}, alpha}),// exposed becomes infectious
        Reaction(LHS  {{I}} >>= {{R}, gamma}), // infectious becomes removed
        Reaction(LHS {{I}} >>= {{H}, kappa}), // infectious becomes hospitalized
        Reaction(LHS {{H}} >>= {{R}, tau})    // hospitalized becomes removed
    };

    ReactionNetwork network{reactions};
    return {network};
}

ReactionNetworkSimulator createCircadianNetwork(){
    auto alphaA = 50.0;
    auto alpha_A = 500.0;
    auto alphaR = 0.01;
    auto alpha_R = 50.0;
    auto betaA = 50.0;
    auto betaR = 5.0;
    auto gammaA = 1.0;
    auto gammaR = 1.0;
    auto gammaC = 2.0;
    auto deltaA = 1.0;
    auto deltaR = 0.2;
    auto deltaMA = 10.0;
    auto deltaMR = 0.5;
    auto thetaA = 50.0;
    auto thetaR = 100.0;
    
    auto DA  = Agent::CreateShared("DA", 1);
    auto D_A = Agent::CreateShared("D_A", 0);
    auto DR  = Agent::CreateShared("DR", 1);
    auto D_R = Agent::CreateShared("D_R", 0);
    auto MA  = Agent::CreateShared("MA", 0);
    auto MR  = Agent::CreateShared("MR", 0);
    auto A   = Agent::CreateShared("A", 0);
    auto R   = Agent::CreateShared("R", 0);
    auto C   = Agent::CreateShared("C", 0);
    
    const std::vector<Reaction>& reactions {
        Reaction(LHS{{DA, A}} >>= {{D_A}, gammaA}),  Reaction(LHS{D_A} >>= {{DA,A}, thetaA}),
        Reaction(LHS{A,DR} >>= {{D_R}, gammaR}),    Reaction(LHS{D_R} >>= {{DR, A}, thetaR}),
        Reaction(LHS{D_A} >>= {{MA, D_A}, alpha_A}), Reaction(LHS{DA} >>= {{MA, DA}, alphaA}),
        Reaction(LHS{D_R} >>= {{MR, D_R}, alpha_R}), Reaction(LHS{DR} >>= {{MR, DR}, alphaR}),
        Reaction(LHS{MA} >>= {{MA, A}, betaA}),      Reaction(LHS{MR} >>= {{MR,R}, betaR}),
        Reaction(LHS{A,R} >>= {{C}, gammaC}),       Reaction(LHS{C} >>= {{R}, deltaA}),
        Reaction(LHS{A} >>= {{}, deltaA}),           Reaction(LHS{R} >>= {{}, deltaR}),
        Reaction(LHS{MA} >>= {{}, deltaMA}),         Reaction(LHS{MR} >>= {{}, deltaMR})
    };
    //CreateShared reactions
    return ReactionNetworkSimulator{ReactionNetwork{reactions}};
}