//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_CONST_T_H
#define CALCULATOR_CONST_T_H


#include "term_t.h"


namespace matlang {
class const_t: public matlang::term_t {
    private:
        double value;
    public:
        explicit const_t(double value) : value(value) {}
        const_t(int value) : value(value) {}
        double accept(matlang::term_visitor &v) override;
        //inline simple operations

        [[nodiscard]] double get_value() const{return value;}
    };
}


#endif //CALCULATOR_CONST_T_H
