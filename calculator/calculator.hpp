#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <utility>
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
#include "terms/assign_t.h"
#include "terms/visitors/visitors.h"


namespace calculator
{   
    using namespace matlang;
    using state_t = term_t::state_t;
    struct expr_t
    {
        std::shared_ptr<term_t>term;
        explicit expr_t(std::shared_ptr<term_t>term) : term{std::move(term)}{
        }
        
        expr_t(double val) : term{std::make_shared<const_t>(const_t{val})}{
            
        }
        expr_t(int val) : term{std::make_shared<const_t>(const_t{val})} {
        }
        
        double operator()(std::shared_ptr<state_t> s) const {
            auto v = visitor::evaluator{s};
            return (*term).accept(v);
        }
    };
    class symbol_table_t
    {
        std::vector<std::string> names;
        std::vector<double> initial;
    public:
        [[nodiscard]] expr_t var(const std::string& name, double init = 0) {
            names.push_back(name);
            initial.push_back(init);
            return expr_t{std::make_shared<var_t>(var_t{ names.size()}) };
        }
        
        [[nodiscard]] state_t state() const { return {initial}; }
    };

    static expr_t create_assign(std::shared_ptr<var_t> variable, const std::shared_ptr<term_t>& value){
        auto q = matlang::assign_t{std::move(variable), value};
        std::shared_ptr<term_t> assign = std::make_shared<assign_t>(q);
        return expr_t{assign};
    }


    static expr_t create_composite_assign(const std::shared_ptr<term_t>&first, 
                                          const std::shared_ptr<term_t>&second, binary_t::bin_ops oprator){
        std::shared_ptr<term_t> new_val = std::make_shared<binary_t>(binary_t{first, second, oprator});
        std::shared_ptr<var_t> variable =
                std::dynamic_pointer_cast<var_t> (first);
        if (variable == nullptr)
            throw std::logic_error{"assignment destination must be a variable expression"};
        
        return create_assign(variable, new_val);
    }
    

    /** assignment operation */
    /** unary operators: */
    inline expr_t operator+(const expr_t& e) {
        return expr_t{ std::make_shared<unary_t>(unary_t{e.term, unary_t::plus})};
    }
    
    inline expr_t operator-(const expr_t& e) {
        return expr_t{ std::make_shared<unary_t>(unary_t{e.term, unary_t::minus})};
    }
    inline expr_t operator/(const expr_t& e, const expr_t& e1) {
        return expr_t{ std::make_shared<binary_t>(binary_t{e.term, e1.term, binary_t::divide})};
    }
    inline expr_t operator*(const expr_t& e, const expr_t& e1) {
        return expr_t{std::make_shared<binary_t>(binary_t{e.term, e1.term, binary_t::mul})};
    }
            
    /** binary operators: */
    inline expr_t operator+(const expr_t& e1, const expr_t& e2) {
        return expr_t{std::make_shared<binary_t>(binary_t{e1.term, e2.term, binary_t::plus})};
    }
    inline expr_t operator-(const expr_t& e1, const expr_t& e2) {
        return expr_t{ std::make_shared<binary_t>(binary_t{e1.term, e2.term, binary_t::minus})};
    }
    
    inline expr_t operator<<=(const expr_t& v, const expr_t& e) {
        std::shared_ptr<var_t> derived = std::dynamic_pointer_cast<var_t> (v.term);
        return create_assign(derived, e.term);
    }

    inline expr_t operator+=(const expr_t& e1, const expr_t& e2) {
        return create_composite_assign(e1.term, e2.term, binary_t::plus);
    }
    inline expr_t operator*=(const expr_t& e1, const expr_t& e2) {
        return create_composite_assign(e1.term, e2.term, binary_t::mul);
    }

    inline expr_t operator-=(const expr_t& e1, const expr_t& e2) {
        return create_composite_assign(e1.term, e2.term, binary_t::minus);
    }
}

#endif // INCLUDE_ALGEBRA_HPP

