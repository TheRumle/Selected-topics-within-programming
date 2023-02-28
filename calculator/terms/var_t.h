//
// Created by rasmu on 24/02/2023.
//

#ifndef CALCULATOR_VAR_T_H
#define CALCULATOR_VAR_T_H

#include "term_t.h"

namespace matlang{
    
    class var_t : public matlang::term_t  {
        size_t id;
    public:
        [[nodiscard]] inline size_t get_id() const{
            return id;
        }
    
        var_t(const var_t&) = default;
        var_t& operator=(const var_t&) = default;
        double accept(matlang::term_visitor &v) override;
        explicit var_t(size_t id): term_t(), id{id} {}
    };
}
#endif //CALCULATOR_VAR_T_H
