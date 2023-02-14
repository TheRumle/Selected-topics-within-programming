//
// Created by rasmu on 14/02/2023.
//

#include "Polyline.h"

Polyline &Polyline::operator+=(const Point &p)  {
    if (points.use_count() > 1)
    {
        std::cout<<"Copy on write!";
        points =  std::make_shared<std::vector<Point>>(std::vector<Point>(*points));
    }
    points->push_back(p);
    return *this;
}

std::vector<Point> *Polyline::get() const {
    return points.get();
}

std::vector<Point>::iterator Polyline::begin() const {
    return points->begin();
}

std::vector<Point>::iterator Polyline::end() const {
    return points->end();
}

Polyline &Polyline::operator=(const Polyline &other) {
    if (this == &other) {
        return *this;
    }

    std::cout << "Copy assignment operator." << std::endl;
    points = other.points;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Polyline &s) {
    os << s.points->size() << " points were shared with " << s.points.use_count() << "\n";
    for (auto const &p : *s.points) {
        os << s;
    }
    return os;
}


