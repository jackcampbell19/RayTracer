#include "Ray.h"
#include <stdio.h>


// Constructs a ray. Copies the origin and vector
void ray_construct(Ray* r, Vector* origin, Vector* direction) {
    vector_copy(&r->origin, origin);
    vector_copy(&r->direction, direction);
    r->min_t = 0;
    r->max_t = 100;
}


void ray_print(Ray* r) {
    printf("Ray(origin: (%f, %f, %f), direction: (%f, %f, %f))\n",
            r->origin.x, r->origin.y, r->origin.z,
            r->direction.x, r->direction.y, r->direction.z);
}
