#include "Color.h"


void color_construct(Color* c, int r, int g, int b) {
    c->r = r;
    c->g = g;
    c->b = b;
}


void color_copy(Color* a, Color* b) {
    a->r = b->r;
    a->g = b->g;
    a->b = b->b;
}
