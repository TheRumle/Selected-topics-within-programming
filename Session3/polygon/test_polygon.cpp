#include <iostream>

#include "polygon.hpp"
#include <iostream>
#include <vector>

/**
 * Code to test the understanding of special member functions and references.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

polygon polygon_factory(size_t count){ return polygon(count); }

void draw_value(polygon) { std::cout << "passed-by-value\n"; }
void draw(const polygon&) { std::cout << "passed-by-const-reference\n"; }
void draw(polygon&) { std::cout << "passed-by-lvalue-reference\n"; }
void draw(polygon&&) { std::cout << "passed-by-rvalue-reference\n"; }

int main()
{
    std::string ruler(40, '-');
    // TODO: Replace "???" with your predictions: what gets printed after each line?
    //       Note that some statements may print more than one line.
    // TODO: After all "???" are gone, step through the program in debugger and check your answers against output.
    // TODO: Answer the additional questions below.
    {   // for example:
        std::cout << ruler << std::endl;
        polygon poly;
        // default-constructor
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly(1);
        // Custom constructor 1
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = 1;
        // Custom constructor 
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        const polygon poly0;
        // default constructor


        polygon poly1 = poly0;
        //copy constructor

        std::cout << ruler << std::endl;
        polygon poly2 = polygon(2);
        // custom constructor 2

        std::cout << ruler << std::endl;
        polygon poly3{{1,2},{3,4},{5,6},{7,8}};
        // custom constructor with point

        std::cout << ruler << std::endl;
        poly2 = poly1;
        // copy assignment


        std::cout << ruler << std::endl;
        poly2 = polygon_factory(9);
        // custom 9
        // move
        // destruct

        std::cout << ruler << std::endl;
        draw_value(poly0);
        // copy constructor
        // passed by value
        //  destructor

        std::cout << ruler << std::endl;
        draw(poly0);
        // const ref

        std::cout << ruler << std::endl;
        draw(poly1);
        //passed-by-lvalue-reference

        std::cout << ruler << std::endl;
        draw(polygon_factory(4));
        // custom, passed by r, destruct 

        std::cout << ruler << std::endl;
        std::vector<polygon> polies(4, poly3);
        // 4 times copy constructor

        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // we need to copy to a new array, thus many copy const.
        // we copy the vector, then move array, then destruct old


        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // allocate double size when first increase, thus only copy once!

        std::cout << ruler << std::endl;
        for (auto const &p : std::move(polies))
            std::cout << p << " at " << &p << '\n';
        // we copy to p every time and then also copies the point with same address and then destruct
        /*
         *          std::cout << ruler << std::endl;
                    for (const auto &p : std::move(polies))
                        std::cout << p << " at " << &p << '\n';
         */
        // TODO: Can we make the loop above more efficient?
        // TODO: This is an incredibly common mistake, make sure to fix it, or ask.

        //Lots of destruction
    }
    {
        std::cout << ruler << std::endl;
        draw(1);
        // It is treated as a polygon, as we do not have a draw taking a number.
        //The function will use 1 to construct a polygon using custom polygon, then it is passed by r value, and destructed
        // TODO: What is going on here? Why "1" is treated as polygon? This is unlikely to be intentional.
        // TODO: Can we forbid the last statement without breaking the previous code?
        // TODO: Fix it in polygon.hpp so that this line does not compile. Just add explicit to the
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw_value(std::move(poly));
        // custom constructor, then print of points (default of 0,0) and address of poly. 
        //Then it is moved, and then passed by value and destroyed. 
        std::cout << poly << " at " << &poly << std::endl;
        // points with values (0,0) was in before the draw. 
        // Now it can contain anything (it is empty)
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw(std::move(poly));
        // Custom constructor, two 0 points, then passed as r value and with 0 points.
        std::cout << poly << " at " << &poly << std::endl;
        // TODO: What was inside poly before draw call?
        // TODO: What is inside poly after draw call? Why?
    }
    std::cout << ruler << ruler << std::endl;
}
