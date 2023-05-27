//
// Created by rasmus on 5/27/2023.
//
#include "reaction/rule.h"
#include "reaction/reaction.h"
#include "simulation.h"


int main(){
    using vessel = symbol_table<std::string, Agent>;
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
    auto v = vessel {};
    
    auto DA = Agent{"DA", 1};
    auto D_A = Agent{"D_A", 0};
    auto DR = Agent{"DR", 1};
    auto D_R = Agent{"D_R", 0};
    auto MA = Agent{"MA", 0};
    auto MR = Agent{"MR", 0};
    auto A = Agent{"A", 0};
    auto R = Agent{"R", 0};
    auto C = Agent{"C", 0};
    v.store(DA.name, DA);
    v.store(D_A.name, D_A);
    v.store(DR.name, DR);
    v.store(D_R.name, D_R);
    v.store(MA.name, MA);
    v.store(MR.name, MR);
    v.store(A.name, A);
    v.store(R.name, R);
    v.store(C.name, C);

    LHS reaction = (, );
    simulation s ({(zA, DA) >>= D_A, gammaA }, v)
    
    return 0;
}
