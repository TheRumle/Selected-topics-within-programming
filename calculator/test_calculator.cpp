#include "calculator.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "terms/visitors/visitors.h"
TEST_CASE("Calculate expressions lazily")
{
    auto sys = calculator::symbol_table_t{};
    auto a = sys.var("a", 2);
    auto b = sys.var("b", 3);
    auto c = sys.var("c");
    auto state = std::make_shared<calculator::state_t>(sys.state());
    auto os = std::ostringstream();

    SUBCASE("Reading the value of a variable from state")
    {
        CHECK(a(state) == 2);
        CHECK(b(state) == 3);
        CHECK(c(state) == 0);
    }
    SUBCASE("Unary operations")
    {
        CHECK((+a)(state) == 2);
        CHECK((-b)(state) == -3);
        CHECK((-c)(state) == 0);
    }
    SUBCASE("Addition and subtraction")
    {
        CHECK((a + b)(state) == 5);
        CHECK((a - b)(state) == -1);
        // the state should not have changed:
        CHECK(a(state) == 2);
        CHECK(b(state) == 3);
        CHECK(c(state) == 0);
    }
    SUBCASE("Assignment expression evaluation")
    {
        CHECK(c(state) == 0);
        CHECK((c <<= b - a)(state) == 1);
        CHECK(c(state) == 1);
        CHECK((a * b)(state) == 6 );
        
        CHECK((c += b - a * c)(state) == 2);
        CHECK(c(state) == 2);
        CHECK((c += b - a * c)(state) == 1);
        CHECK(c(state) == 1);
        
        
        CHECK_THROWS_MESSAGE((c - a += b - c), "assignment destination must be a variable expression");
                
    }
    SUBCASE("Parenthesis")
    {
        CHECK((a - (b - c))(state) == -1);
        CHECK((a - (b - a))(state) == 1);
    }
    
    SUBCASE("Evaluation of multiplication and division")
    {
        CHECK((a * b)(state) == 6);
        CHECK((a / b)(state) == 2. / 3);
        CHECK_THROWS_MESSAGE((a / c)(state), "division by zero");
    }
    SUBCASE("Mixed addition and multiplication")
    {
        CHECK((a + a * b)(state) == 8);
        CHECK((a - b / a)(state) == 0.5);
    }
    
    
    SUBCASE("Constant expressions")
    {
        CHECK((7 + a)(state) == 9);
        CHECK((a - 7)(state) == -5);
    }
    
    SUBCASE("Store expression and evaluate lazily")
    {
        auto expr = (a + b) * c;
        auto c_4 = c <<= 4;
        CHECK(expr(state) == 0);
        CHECK(c_4(state) == 4);
        CHECK(expr(state) == 20);
    }
    

    using namespace matlang::visitor;
    SUBCASE("Printer does not crash")
    {
        auto expr = a + 2 + b + c - c;
        printer k = printer{std::cout};
        expr.term->accept(k);
        std::cout << "end";
    }
    
}
