﻿#include <iostream>

#include <iostream>
#include "Polyline.h"

void eval_line_boolean(const Polyline &line) {
    if (line) {
        std::cout << "The line is non-empty :)" << std::endl;
    } else {
        std::cout << "The line is empty :(" << std::endl;
    }
}


void print_ruler() {
    std::string ruler(40, '-');
    std::cout << ruler << std::endl;
}

int main() {
    Point a { 1.0, 5.0 };
    Point b { 6.9, 4.20 };

    Polyline line1;

    // Demonstrate overloading += working for exercise 2
    std::cout << "Exercise 2 results:" << std::endl;
    line1 += a;
    line1 += b;

    std::cout << line1;
    print_ruler();

    // Demonstrate copy-on-write semantics for exercise 3
    std::cout << "Exercise 3 results:" << std::endl;
    Polyline line2 = line1;
    std::cout << line2;

    Point c { 10, 20 };

    std::cout << std::endl << "The following memory addresses should be identical as they share the same data structure:" << std::endl;
    std::cout << "line1: " << std::hex << line1.get() << std::endl;
    std::cout << "line2: " << std::hex << line2.get() << std::endl << std::endl;

    // This should invoke copy-on-write because we wrote to the data structure.
    line2 += c;

    std::cout << std::endl << "The following memory addresses should no longer be identical because we wrote to line2:" << std::endl;
    std::cout << "line1: " << std::hex << line1.get() << std::endl;
    std::cout << "line2: " << std::hex << line2.get() << std::endl << std::endl;

    std::cout << line2;
    print_ruler();

    /*
     * Notes on exercise 4:
     * I have implemented a copy constructor as well as a copy assignment operator. I deem these necessary.
     * 
     * I do not need to implement a move constructor or move assignment operator because the std::shared_ptr member
     * already implements move semantics.
     * 
     * I do not need to implement a destructor because shared_ptr manages the lifetime of the dynamically allocated
     * data automatically by freeing the dynamically allocated memory when the last shared Pointer to the data goes
     * out of scope or is destroyed.
    */

    // Demonstrate bool operator overload for exercise 5
    std::cout << "Exercise 5 results:" << std::endl;
    eval_line_boolean(line1);
    line1.clear();
    eval_line_boolean(line1);

    return 0;
}