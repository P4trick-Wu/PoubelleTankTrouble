#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.hpp"
#include "color.hpp"


struct Triangle {
    Point p1;
    Point p2;
    Point p3;
    Color color;
};

void triangle_init(Triangle* triangle, Point p1, Point p2, Point p3, Color color);

#endif