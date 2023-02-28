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
    };
}


#endif //CALCULATOR_TERM_T_H
