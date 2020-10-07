#include "Triangle.h"
#include "Vector.h"
#include "Color.h"


#ifndef OBJECT_H_
#define OBJECT_H_


typedef struct {
    Triangle** triangles;
    int triangle_count;
    int visible;
    Color color;
} Object;


Object* object_create_cube(Vector* origin, double width, double length, double height, Color* color);
int object_get_closest_intersection(Object* o, Ray* r, Vector* intersection, double* angle, Color* color);
Object* object_create_triangle(Triangle* t, Color* c);


#endif
