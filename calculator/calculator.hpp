#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include "terms/term_t.h"
#include "terms/var_t.h"
#include "terms/unary_t.h"
#include "terms/binary_t.h"
#include "terms/const_t.h"

namespace calculator
{
    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = term_t::state_t;
    

    /** Forward declarations to get around circular dependencies: */

    struct expr_t
    {
        std::shared_ptr<term_t>term;
        explicit expr_t(std::shared_ptr<term_t>term) : term{std::move(term)}{
        }
        
        expr_t(double val) : term{std::make_shared<const_t>(const_t{val})}{
            
        }
        expr_t(int val) : term{std::make_shared<const_t>(const_t{val})} {
        }
            double operator()(state_t& s) const {
            return  (*term)(s);
        }
    };

    /** Class representing a variable */

    class symbol_table_t
    {
        std::vector<std::string> names;
        std::vector<double> initial;
    public:
        [[nodiscard]] expr_t var(const std::string& name, double init = 0) {
            auto res = names.size();
            names.push_back(name);
            initial.push_back(init);
            std::shared_ptr<term_t> f = std::make_shared<var_t>(var_t{res}) ;
            return expr_t{f};
        }
        [[nodiscard]] state_t state() const { return {initial}; }
    };

    static expr_t create_composite_assign(std::shared_ptr<term_t>first, std::shared_ptr<term_t>second, op_t oprator){
        std::shared_ptr<term_t> newVal = std::make_shared<binary_t>(binary_t{first, first, oprator});

        std::shared_ptr<var_t> derived =
                std::dynamic_pointer_cast<var_t> (first);
        auto q = assign_t{derived, second};
        std::shared_ptr<term_t> assign = std::make_shared<assign_t>(q);
        return expr_t{assign};
    }

    /** assignment operation */
    /** unary operators: */
    inline expr_t operator+(const expr_t& e) {
        std::shared_ptr<term_t> q = std::make_shared<unary_t>(unary_t{e.term, plus});
        return expr_t{q};
    }
    
    inline expr_t operator-(const expr_t& e) {
        std::shared_ptr<term_t> q = std::make_shared<unary_t>(unary_t{e.term, minus});
        return expr_t{q};
    }
    inline expr_t operator/(const expr_t& e, const expr_t& e1) {
        std::shared_ptr<term_t> q = std::make_shared<binary_t>(binary_t{e.term, e1.term, divide});
        return expr_t{q};
    }
    inline expr_t operator*(const expr_t& e, const expr_t& e1) {
        std::shared_ptr<term_t> q = std::make_shared<binary_t>(binary_t{e.term, e1.term, mul});
        return expr_t{q};
    }

    /** binary operators: */
    inline expr_t operator+(const expr_t& e1, const expr_t& e2) {
        std::shared_ptr<term_t> q = std::make_shared<binary_t>(binary_t{e1.term, e2.term, plus});
        return expr_t{q};
    }
    inline expr_t operator-(const expr_t& e1, const expr_t& e2) {
        std::shared_ptr<term_t> q = std::make_shared<binary_t>(binary_t{e1.term, e2.term, minus});
        return expr_t{q};
    }
    
    inline expr_t operator<<=(const expr_t& v, const expr_t& e) {
        //if v is not varable
        std::shared_ptr<var_t> derived =
                std::dynamic_pointer_cast<var_t> (v.term);
        auto q = assign_t{derived, e.term};
        std::shared_ptr<term_t> assign = std::make_shared<assign_t>(q);
        return expr_t{assign}; }

    inline expr_t operator+=(const expr_t& e1, const expr_t& e2) {
        return create_composite_assign(e1.term, e2.term, plus);
    }


    inline expr_t operator*=(const expr_t& e1, const expr_t& e2) {
        return create_composite_assign(e1.term, e2.term, mul);
    }

    inline expr_t operator-=(const expr_t& e1, const expr_t& e2) {
        return create_composite_assign(e1.term, e2.term, minus);
    }
}

#endif // INCLUDE_ALGEBRA_HPP

