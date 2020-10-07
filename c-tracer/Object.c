#include "Object.h"
#include "Vector.h"
#include "Ray.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include "Triangle.h"
#include <stdio.h>


Object* object_construct_base(int num_triangles, Color* c) {
    Object* object = (Object*) malloc(sizeof(Object));
    object->triangle_count = num_triangles;
    object->triangles = (Triangle**) malloc(sizeof(Triangle*) * num_triangles);
    object->visible = 1;
    color_copy(&object->color, c);
    return object;
}


Object* object_create_triangle(Triangle* t, Color* c) {
    int num_triangles = 1;
    Object* triangle = object_construct_base(num_triangles, c);
    triangle->triangles[0] = t;
    return triangle;
}


Object* object_create_cube(Vector* origin, double width, double length, double height, Color* color) {
    int num_triangles = 12;
    Object* cube = object_construct_base(num_triangles, color);
    Vector p0;
    vector_copy(&p0, origin);
    Vector p1;
    vector_copy(&p1, origin);
    p1.x += width;
    Vector p2;
    vector_copy(&p2, origin);
    p2.y -= length;
    Vector p3;
    vector_copy(&p3, origin);
    p3.x += width;
    p3.y -= length;
    Vector p4;
    vector_copy(&p4, origin);
    p4.z += height;
    Vector p5;
    vector_copy(&p5, origin);
    p5.z += height;
    p5.x += width;
    Vector p6;
    vector_copy(&p6, origin);
    p6.z += height;
    p6.y -= length;
    Vector p7;
    vector_copy(&p7, origin);
    p7.z += height;
    p7.x += width;
    p7.y -= length;

    cube->triangles[0] = triangle_create(&p0, &p2, &p1);
    cube->triangles[1] = triangle_create(&p1, &p2, &p3);

    cube->triangles[2] = triangle_create(&p0, &p5, &p4);
    cube->triangles[3] = triangle_create(&p0, &p1, &p5);

    cube->triangles[4] = triangle_create(&p2, &p0, &p4);
    cube->triangles[5] = triangle_create(&p4, &p6, &p2);

    cube->triangles[6] = triangle_create(&p2, &p7, &p3);
    cube->triangles[7] = triangle_create(&p2, &p6, &p7);

    cube->triangles[8] = triangle_create(&p1, &p3, &p5);
    cube->triangles[9] = triangle_create(&p3, &p7, &p5);

    cube->triangles[10] = triangle_create(&p5, &p7, &p6);
    cube->triangles[11] = triangle_create(&p4, &p5, &p6);

    return cube;
}


int object_get_closest_intersection(Object* o, Ray* r, Vector* intersection, double* angle, Color* color) {
    int has_intersection = 0;
    double shortest_length = DBL_MAX;
    for (int i = 0; i < o->triangle_count; i++) {
        Triangle* t = o->triangles[i];
        double a;
        Vector i;
        // Check intersection
        if (triangle_get_intersection(t, r, &i, &a)) {
            has_intersection = 1;
            Vector d;
            vector_subtract(&i, &r->origin, &d);
            // If it is closer than the existing one, assign the values to the output
            if (vector_norm(&d) < shortest_length) {
                shortest_length = vector_norm(&d);
                vector_copy(intersection, &i);
                *angle = a;
                color_copy(color, &o->color); // TEMP COLOR RETURN
            }
        }
    }
    return has_intersection;
}
