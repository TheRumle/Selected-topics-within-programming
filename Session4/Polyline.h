//
// Created by rasmu on 14/02/2023.
//

#ifndef SESSION4_POLYLINE_H


#define SESSION4_POLYLINE_H


#include <vector>
#include <memory>
#include <iostream>
#include "Point.h"

class Polyline {
public:

    Polyline (const Polyline&& other)  noexcept {
        points = other.points;
    }
    Polyline (const Polyline &other) : points(other.points) {
        std::cout << "Polyline copy constructor." << std::endl;
    }
    ~Polyline() = default;
    
    Polyline () {
        std::cout << "Polyline default constructor." << std::endl;
    }
    
    Polyline& operator+= (const Point& p);
    
    explicit operator bool () const{
        return !points->empty();
    }

    [[nodiscard]] std::vector<Point>::iterator begin() const;
    [[nodiscard]] std::vector<Point>::iterator end() const;
    [[nodiscard]] std::vector<Point>* get() const;
    
    Polyline& operator=(const Polyline &other);

    friend std::ostream& operator << (std::ostream &os, const Polyline &s);

    void clear() const {
        std::cout << "Cleared points." << std::endl;
        points->clear();
    }
    
private:
    std::shared_ptr<std::vector<Point>> points 
        = std::make_shared<std::vector<Point>>(std::vector<Point>{3}); //a polygon is assumed to have three points but must not have
};








#endif //SESSION4_POLYLINE_H
