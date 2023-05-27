//
// Created by rasmus on 5/26/2023.
//

#include "reaction/construction_rules.h"
#include "ReactionNetwork.h"
#include "reaction/reaction.h"
int main() {
    auto lhs = LHS {{{"A",1}, {"C",1}}};
    auto rhs = RHS {{{"B",1}, {"C",1}},0.001};
    const reaction& reaction = lhs >>= rhs;
    std::cout << reaction;
    
    auto s = reaction::state{};

    Agent A = Agent{"A", 100};
    Agent B = Agent{"B", 0};
    Agent C = Agent{"C", 1};

    s.storeOrUpdate(A.name, A.volume);
    s.storeOrUpdate(B.name, B.volume);
    s.storeOrUpdate(C.name, C.volume);

    ReactionNetwork q {{reaction},s};
    q.operator()(1500);
    return 0;
}

