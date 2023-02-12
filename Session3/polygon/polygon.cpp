﻿//
// Created by rasmus on 2/12/2023.
//

#include "polygon.hpp" // include your headers first to test that they are self-contained
#include <iostream>
#include <algorithm>

/**
 * Implementation of the polygon class methods.
 * They are mostly printing, but other content (copy and move constructor and assignment)
 * are representative of good practice. There are still some minor details left to fix.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

/**
 * 1) Very important: fix the memory leak. Address sanitizer may provide a quick help.
 * 2) Change the initializations to uniform initializations with curly braces.
 *          Be careful, not all make sense.
 * 3) move-constructor and move-assignment operator have identical code,
 *          which is difficult to maintain. How can we apply the DRY principle? Fix it!
 *          DRY = Don't Repeat Yourself, i.e. get rid of the code duplicates by reusing the code.
 * 4) copy-constructor and copy-assignment operator have almost identical code,
 *          which is difficult to maintain. How can we apply the DRY principle? Fix it!
 * 5) Nearly all constructors have identical initializations, DRY them by using constructor delegation.
 * 6) Use std::transform instead of for() loop when copying array data.
 * 7) Compare the performance of copy-assignment vs move-assignment (mentally).
 * 8) Install SonarLink plugin for Clion (Settings -> Plugins -> search for SonarLint)
 *          and check if there are more issues in this file and polygon.hpp.
 */

std::ostream& operator<<(std::ostream& os, const point& p)
{
    return os << "point{" << p.x << ',' << p.y << "}";
}

polygon::~polygon() noexcept
{
    delete [] points; // fixes memory leak

    std::cout << "destructor\n";
}
polygon::polygon():polygon(0){}

polygon::polygon(size_t count):
        count{count}, points{count ? new point[count]() : nullptr}
{
    std::cout << "custom-constructor(" << count << ")\n";
}

polygon::polygon(const std::initializer_list<point>& ps):
        polygon(ps.size())
{

    std::cout << "custom-constructor{";
    for (auto i=0u; i<count; ++i)
        points[i] = std::data(ps)[i];

    if (count) {
        std::cout << points[0];
        for (auto i=1u; i<count; ++i)
            std::cout << ',' << points[i];
    }
    std::cout << "}\n";
}

polygon& polygon::operator=(const polygon& other)
{
    if (this != &other) {
        std::cout << "copy-assignment\n";
        delete [] points;
        copy(other);
    }
    return *this; // remember to return, otherwise wicked memory issues
}

polygon::polygon(const polygon& other): points{}, count{0}
{
    std::cout << "copy-constructor\n";
    copy(other);
}

polygon& polygon::operator=(polygon&& other) noexcept
{
    std::cout << "move-assignment\n";
    polygon::move(other);
    return *this; // remember to return, otherwise all kinds of weird memory issues
}

polygon::polygon(polygon&& other) noexcept: points{}, count{0}
{
    std::cout << "move-constructor\n";
    move(other);
}

void polygon::copy(const polygon& other) {
    // Allocate memory:
    count = other.count; // copy
    points = new point[count]; // allocate -- expensive

    std::ranges::transform(other.begin(), other.end(), points,
                           [](const auto& p) {return p; });
}

void polygon::move(polygon& other) noexcept {
    std::swap(count, other.count);   // cheap
    std::swap(points, other.points); // super cheap!
}

std::ostream& operator<<(std::ostream& os, const polygon& poly)
{
    if (poly.empty()) {
        os << "(empty polygon)";
    } else {
        for (auto const &point: poly) { //use const pointer instead
            os << point << " ";
        }
    }

    return os; // remember to return, otherwise wicked memory issues
}