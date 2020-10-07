#ifndef COLOR_H_
#define COLOR_H_


typedef struct {
    int r;
    int g;
    int b;
} Color;


void color_construct(Color* c, int r, int g, int b);
void color_copy(Color* a, Color* b);


#endif
