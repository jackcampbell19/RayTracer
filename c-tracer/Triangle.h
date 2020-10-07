#include "Vector.h"
#include "Ray.h"


#ifndef TRIANGLE_H_
#define TRIANGLE_H_


typedef struct {
    Vector a;
    Vector b;
    Vector c;
} Triangle;


void triangle_construct(Triangle* t, Vector* a, Vector* b, Vector* c);
void triangle_compute_normal(Triangle* t, Vector* r);
int triangle_get_intersection(Triangle* t, Ray* r, Vector* vr, double* angle);
void triangle_print(Triangle* t);
Triangle* triangle_create(Vector* a, Vector* b, Vector* c);


#endif
