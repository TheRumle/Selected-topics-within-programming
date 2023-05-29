//
// Created by rasmus on 5/27/2023.
//
#include "reaction/construction_rules.h"
#include "reaction/reaction.h"
#include "reaction_network/ReactionNetwork.h"

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

    auto DA = Agent::CreateShared("DA", 1);
    auto D_A = Agent::CreateShared("D_A", 0);
    auto DR = Agent::CreateShared("DR", 1);
    auto D_R = Agent::CreateShared("D_R", 0);
    auto MA = Agent::CreateShared("MA", 0);
    auto MR = Agent::CreateShared("MR", 0);
    auto A = Agent::CreateShared("A", 0);
    auto R = Agent::CreateShared("R", 0);
    auto C = Agent::CreateShared("C", 0);
    
    //Init start state_history for agents
    v.storeOrUpdate(DA->agent_name, 1);
    v.storeOrUpdate(D_A->agent_name, 0);
    v.storeOrUpdate(DR->agent_name, 1);
    v.storeOrUpdate(D_R->agent_name, 0);
    v.storeOrUpdate(MA->agent_name, 0);
    v.storeOrUpdate(MR->agent_name, 0);
    v.storeOrUpdate(A->agent_name, 0);
    v.storeOrUpdate(R->agent_name, 0);
    v.storeOrUpdate(C->agent_name, 0);

    //CreateShared reactions
    const std::initializer_list<reaction> initializerList = {
        reaction(LHS{{DA, A}} >>= {{D_A}, gammaA}),
        reaction(LHS{D_A} >>= {{D_A,A}, thetaA}),
        reaction(LHS{A,DR} >>= {{D_R}, gammaR}),
        reaction(LHS{D_R} >>= {{DR, A}, thetaR}),
        reaction(LHS{D_A} >>= {{MA, D_A}, alpha_A}),
        reaction(LHS{DA} >>= {{MA, DA}, alphaA}),
        reaction(LHS{D_R} >>= {{MR, D_R}, alpha_R}),
        reaction(LHS{DR} >>= {{MR, DR}, alphaR}),
        reaction(LHS{MA} >>= {{MA, A}, betaA}),
        reaction(LHS{MR} >>= {{MR,R}, betaR}),
        reaction(LHS{A,R} >>= {{C}, gammaC}),
        reaction(LHS{C} >>= {{R}, deltaA}),
        reaction(LHS{A} >>= {{}, deltaA}),
        reaction(LHS{R} >>= {{}, deltaR}),
        reaction(LHS{MA} >>= {{}, deltaMA}),
        reaction(LHS{MR} >>= {{}, deltaMR})
    };

    ReactionNetwork q {initializerList, v};
    q.operator()(100);
    return 0;
}
