//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_TERM_T_H
#define CALCULATOR_TERM_T_H

#include <vector>

namespace matlang{
    class term_visitor;
    class term_t{
    protected:
    
    public:
        using state_t = std::vector<double>;
        term_t() = default;
        virtual ~term_t() noexcept = default;
        inline virtual double accept(term_visitor& v) = 0; //can one inline virtual method? Should you?
        //I do not use const here, because in general an operation from a Visitor may update either the
        //Node ‘‘visited’’ or the Visitor itself.
    };
}


#endif //CALCULATOR_TERM_T_H
