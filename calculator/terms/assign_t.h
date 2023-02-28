//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_ASSIGN_T_H
#define CALCULATOR_ASSIGN_T_H


#include <memory>
#include <utility>
#include "var_t.h"


namespace matlang   {
class assign_t : public term_t {
    std::shared_ptr<var_t> var;
    std::shared_ptr<term_t> term;
public:
    std::shared_ptr<term_t> get_term(){
        return term;
    }
    
    std::shared_ptr<var_t> get_var(){
        return var;
    }
    explicit assign_t(std::shared_ptr<var_t>  variable, std::shared_ptr<term_t> term)
    :term{std::move(term)}, var{std::move(variable)}
    {
        //Clang suggests to pass by value and then move.
        // Why is that better than using const & as I have done with term?
        // This was answered. One pass one reference as parameter and then perform a copy vs a copy and then a move
    }
    
    double accept(matlang::term_visitor &v) override;
};
}
#endif //CALCULATOR_ASSIGN_T_H
