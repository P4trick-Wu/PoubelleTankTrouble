#include "color.hpp"


void color_init(Color* color, float r, float g, float b, float a) {
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}