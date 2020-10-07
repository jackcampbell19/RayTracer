#include "Triangle.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Constructs a triangle
void triangle_construct(Triangle* t, Vector* a, Vector* b, Vector* c) {
  vector_copy(&t->a, a);
  vector_copy(&t->b, b);
  vector_copy(&t->c, c);
}


Triangle* triangle_create(Vector* a, Vector* b, Vector* c) {
    Triangle* t = (Triangle*) malloc(sizeof(Triangle));
    triangle_construct(t, a, b, c);
    return t;
}


void triangle_compute_normal(Triangle* t, Vector* r) {
    Vector v1;
    Vector v2;
    vector_subtract(&t->b, &t->a, &v1);
    vector_subtract(&t->c, &t->a, &v2);
    vector_cross(&v1, &v2, r);
    vector_multiply_t(r, 1.0 / vector_norm(r));
}


// Returns 1 if the triangle has an intersection, 0 otherwise.
// If the result is true, v and angle will have values.
int triangle_get_intersection(Triangle* t, Ray* r, Vector* vr, double* angle) {
    // Moller-Trumbore
    Vector e1;
    vector_subtract(&t->b, &t->a, &e1);
    Vector e2;
    vector_subtract(&t->c, &t->a, &e2);
    Vector s;
    vector_subtract(&r->origin, &t->a, &s);
    Vector s1;
    vector_cross(&r->direction, &e2, &s1);
    Vector s2;
    vector_cross(&s, &e1, &s2);
    double slr = vector_dot(&s1, &e1);
    if (slr == 0) {
        return 0;
    }
    double scalar = 1.0 / slr;
    Vector v;
    vector_construct(&v, vector_dot(&e2, &s2), vector_dot(&s, &s1), vector_dot(&r->direction, &s2));
    vector_multiply_t(&v, scalar);
    if ((v.y < 0.0 || v.y > 1.0) || (v.z < 0.0 || v.y + v.z > 1.0)
            || (v.x < 0.000001) || v.x < r->min_t || v.x > r->max_t) {
        return 0;
    }
    // Calculate intersection
    vector_copy(vr, &r->direction);
    vector_multiply_t(vr, v.x);
    vector_add_t(vr, &r->origin);
    // Compute normal
    Vector normal;
    triangle_compute_normal(t, &normal);
    *angle = asin(vector_dot(&r->direction, &normal) / vector_norm(&r->direction) * vector_norm(&normal)) * 180 / M_PI;
    return 1;
}


void triangle_print(Triangle* t) {
    printf("Triangle:\n");
    vector_print(&t->a);
    vector_print(&t->b);
    vector_print(&t->c);
}
