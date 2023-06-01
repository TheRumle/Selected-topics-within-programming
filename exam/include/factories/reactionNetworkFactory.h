//
// Created by rasmus on 5/29/2023.
//
#include <memory>
#include <cmath>
#include "reactionNetwork/reactionNetworkSimulator.h"
#include "reaction/agents.h"
ReactionNetwork createNetwork(const Agent::P_Container& A,
                              const Agent::P_Container& B,
                              const Agent::P_Container& C){
    
    auto lambda = 0.001;
    Reaction r{{A + C >>= C + B},lambda};
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
        Reaction(S+I >>= E+I, beta/N), // susceptible becomes exposed through infectious
        Reaction( E >>= I, alpha),// exposed becomes infectious
        Reaction( I >>= R, gamma), // infectious becomes removed
        Reaction( I >>= H, kappa), // infectious becomes hospitalized
        Reaction( H >>= R, tau)    // hospitalized becomes removed
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
        Reaction(DA+A>>= D_A, gammaA),
        Reaction(D_A >>= DA+A, thetaA),
        Reaction(A+DR>>= D_R, gammaR),
        Reaction(D_R >>= DR+ A, thetaR),
        Reaction(D_A >>= MA+ D_A, alpha_A),
        Reaction(DA  >>= MA+ DA, alphaA),
        Reaction(D_R >>= MR+ D_R, alpha_R),
        Reaction(DR  >>= MR+ DR, alphaR),
        Reaction(MA  >>= MA+ A, betaA),     
        Reaction(MR  >>= MR+R, betaR),
        Reaction(A+R >>= C, gammaC),       
        Reaction(C   >>= R, deltaA),
        Reaction(A   >>= {}, deltaA),          
        Reaction(R   >>= {}, deltaR),
        Reaction(MA  >>= {}, deltaMA),         
        Reaction(MR  >>= {}, deltaMR)
    };
    //CreateShared reactions
    return ReactionNetworkSimulator{ReactionNetwork{reactions}};
}

std::pair<std::basic_string<char>, double> MonitorAndGetMaxHospitalized(int N){
    ReactionNetworkSimulator covidSimulator1 = createCovidNetworkSimulation(N);
    CovidHospitalizationMonitor monitor{};
    covidSimulator1(1000, monitor);
    return monitor.extractPeakHospitalized();
}
