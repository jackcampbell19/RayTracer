#include <stdlib.h>
#include <stdio.h>
#include "Camera.h"


// Creates and sets the frame of a camera struct
void camera_create_frame(Camera* c) {
    // Generate the frame values
    Vector p0;
    Vector p1;
    Vector p2;
    vector_construct(&p0, c->width / 2.0, 0, 0);
    vector_construct(&p1, 0, -c->focal_length, 0);
    vector_construct(&p2, 0, 0, c->height / 2.0);
    // Reset frame
    vector_copy(&c->v0, &p1);
    vector_copy(&c->v1, &p1);
    vector_copy(&c->v2, &p1);
    vector_copy(&c->v3, &p1);
    // Insert values for frame
    vector_subtract_t(&c->v0, &p0);
    vector_add_t(&c->v0, &p2);
    vector_add_t(&c->v1, &p0);
    vector_add_t(&c->v1, &p2);
    vector_subtract_t(&c->v2, &p0);
    vector_subtract_t(&c->v2, &p2);
    vector_add_t(&c->v3, &p0);
    vector_subtract_t(&c->v3, &p2);
    // Apply rotation
    // TODO: this
    // Translate the frame to the cameras origin
    vector_add_t(&c->v0, &c->origin);
    vector_add_t(&c->v1, &c->origin);
    vector_add_t(&c->v2, &c->origin);
    vector_add_t(&c->v3, &c->origin);
}


// Creates a camera struct
void camera_construct(Camera* c, Vector* origin, Vector* rotation, int width, int height, double focal_length) {
    vector_copy(&c->origin, origin);
    vector_copy(&c->rotation, rotation);
    c->width = width;
    c->height = height;
    c->focal_length = focal_length;
    camera_create_frame(c);
}


// Generates a ray from the camera. px and py are between 0 and 1
void camera_generate_ray(Camera* c, double px, double py, Ray* r) {
    // Calculate top x vector
    Vector tx0;
    vector_multiply(&c->v0, px, &tx0);
    Vector m0;
    vector_multiply(&c->v1, (1.0 - px), &m0);
    vector_add_t(&tx0, &m0);
    // Calculate bottom x vector
    Vector tx1;
    vector_multiply(&c->v2, px, &tx1);
    Vector m1;
    vector_multiply(&c->v3, (1.0 - px), &m1);
    vector_add_t(&tx1, &m1);
    // Adjust to the y position
    vector_multiply_t(&tx0, py);
    vector_multiply_t(&tx1, (1.0 - py));
    vector_add_t(&tx0, &tx1);
    // Calculate direction vector
    vector_subtract_t(&tx0, &c->origin);
    // Construct ray
    ray_construct(r, &c->origin, &tx0);
}
