//
// Created by rasmus on 5/27/2023.
//
#include "reaction/reaction.h"
#include "reaction_network/ReactionNetwork.h"
int  main(){
    double  N = 10000;
    
    
    using vessel = reaction::state;
    auto v = vessel {};
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
    
    auto S = Agent{"S", 1};
    auto E = Agent{"E", 1};
    auto I = Agent{"I", 1};
    auto H = Agent{"H", 1};
    auto R = Agent{"R", 1};
    
    v.store(S._name, S0);
    v.store(E._name, E0);
    v.store(I._name, I0);
    v.store(H._name, 0);
    v.store(R._name, 0);
    
    std::initializer_list<reaction> reactions = {
        reaction(LHS {{S,I}} >>= {{E,I}, beta/N}), // susceptible becomes exposed through infectious
        reaction(LHS  {{E}} >>= {{I}, alpha}),// exposed becomes infectious
        reaction(LHS  {{I}}>>= {{{R._name, R.total_agent}}, gamma}), // infectious becomes removed
        reaction(LHS {{I}} >>= {{H}, kappa}), // infectious becomes hospitalized
        reaction(LHS {{H._name, H.total_agent}} >>= {{R}, tau})    // hospitalized becomes removed
    };
    
    ReactionNetwork q {reactions, v};
    q.operator()(100);
}