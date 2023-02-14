//
// Created by rasmu on 14/02/2023.
//

#include "Point.h"

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}