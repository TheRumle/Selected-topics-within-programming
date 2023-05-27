//
// Created by rasmus on 5/27/2023.
//
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "simulation.h"


int main(){
    using vessel = reaction::state;
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
    auto D_A = Agent{"D_A", 1};
    auto DR = Agent{"DR", 1};
    auto D_R = Agent{"D_R", 1};
    auto MA = Agent{"MA", 1};
    auto MR = Agent{"MR", 1};
    auto A = Agent{"A", 1};
    auto R = Agent{"R", 1};
    auto C = Agent{"C", 1};
    
    //Init start state for agents
    v.storeOrUpdate(DA.name, 1);
    v.storeOrUpdate(D_A.name, 0);
    v.storeOrUpdate(DR.name, 1);
    v.storeOrUpdate(D_R.name, 0);
    v.storeOrUpdate(MA.name, 0);
    v.storeOrUpdate(MR.name, 0);
    v.storeOrUpdate(A.name, 0);
    v.storeOrUpdate(R.name, 0);
    v.storeOrUpdate(C.name, 0);

    //Create reactions
    std::initializer_list<reaction> initializerList = {reaction(reaction(LHS{{DA, A}} >>= RHS{D_A}), gammaA),
                                                       reaction(reaction(LHS{D_A} >>= {D_A,A}), thetaA),
                                                       reaction(reaction(LHS{A,DR} >>= {D_R}), gammaR),
                                                       reaction(reaction(LHS{D_R} >>= {DR, A}), thetaR),
                                                       reaction(reaction(LHS{D_A} >>= {MA, D_A}), alpha_A),
                                                       reaction(reaction(LHS{DA} >>= {MA, DA}), alphaA),
                                                       reaction(reaction(LHS{D_R} >>= {MR, D_R}), alpha_R),
                                                       reaction(reaction(LHS{DR} >>= {MR, DR}), alphaR),
                                                       reaction(reaction(LHS{MA} >>= {MA, A}), betaA),
                                                       reaction(reaction(LHS{MR} >>= {MR,R}), betaR),
                                                       reaction(reaction(LHS{A,R} >>= {C}), gammaC)  ,
                                                       reaction(reaction(LHS{C} >>= {R}), deltaA),
                                                       reaction(reaction(LHS{A} >>= {}), deltaA),
                                                       reaction(reaction(LHS{R} >>= {}), deltaR),
                                                       reaction(reaction(LHS{MA} >>= {}), deltaMA),
                                                       reaction(reaction(LHS{MR} >>= {}), deltaMR)
    };
    
    simulation q {initializerList, v};
    q.operator()(100);
    return 0;
}
