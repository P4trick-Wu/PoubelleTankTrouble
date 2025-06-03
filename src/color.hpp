#ifndef COLOR_H
#define COLOR_H


struct Color {
    float r;
    float g;
    float b;
    float a;
};

void color_init(Color* color, float r, float g, float b, float a);

#endif