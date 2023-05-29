//
// Created by rasmus on 5/27/2023.
//
#include <cmath>
#include "reaction/reaction.h"
#include "reaction_network/reactionNetwork.h"
#include "reaction_network/reactionNetworkSimulator.h"
int  main(){
    double  N = 10000;
    
    
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
    ReactionNetworkSimulator runner {network,{S, E, I, H, R}};
    runner.operator()(100);
}