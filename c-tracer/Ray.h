#include "Vector.h"


#ifndef RAY_H_
#define RAY_H_


typedef struct {
    Vector origin;
    Vector direction;
    double min_t;
    double max_t;
} Ray;


void ray_construct(Ray* r, Vector* origin, Vector* direction);
void ray_print(Ray* r);


#endif
