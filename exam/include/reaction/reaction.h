//
// Created by rasmus on 5/26/2023.
//

#ifndef LAMBDAS_REACTION_H
#define LAMBDAS_REACTION_H

#include <utility>

#include "rule.h"
struct reaction
{
    const double lambda;
    Rule rule;
    reaction(reaction const &reaction) = default;
    reaction(reaction& other) = default;
    reaction(Rule& rule, const double lambda): lambda(lambda), rule(rule) {}
    reaction(Rule  rule, double lambda): lambda(lambda), rule(std::move(rule)){}
    
    
    reaction operator= (reaction other){
        return reaction(other);
    }
    
    [[nodiscard]] double compute_delay(symbol_table<std::string, double>& state);
    [[nodiscard]] bool canBeSatisfied(symbol_table<std::string,  double >& state);
    inline void operator()(symbol_table<std::string, double >& state){
        this->rule.operator()(state);
    }
    
    friend std::ostream & operator << (std::ostream& s, const reaction& value){
        s <<"{ ";
        for (const auto& r : value.rule.reactants){
            s << r << " ";
        }
        s << " --" << value.lambda <<  "--> ";
        for (const auto& p : value.rule.products)
            s << p << " ";
        s << "}\n";
        return s;
    }
};


#endif  // LAMBDAS_REACTION_H
