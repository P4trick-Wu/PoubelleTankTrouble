#ifndef POINT_H
#define POINT_H


struct Point {
    float x;
    float y;
};

void point_init(Point* point, float x, float y);

#endif