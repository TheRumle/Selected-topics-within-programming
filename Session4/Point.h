//
// Created by rasmu on 14/02/2023.
//

#ifndef SESSION4_POINT_H
#define SESSION4_POINT_H

#include <iostream>
struct Point {
    double x;
    double y;
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};



#endif //SESSION4_POINT_H
