#include "triangle.hpp"


void triangle_init(Triangle* triangle, Point p1, Point p2, Point p3, Color color) {
    triangle->p1 = p1;
    triangle->p2 = p2;
    triangle->p3 = p3;
    triangle->color = color;
}