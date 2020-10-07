#include "Vector.h"
#include "Ray.h"


#ifndef CAMERA_H_
#define CAMERA_H_


typedef struct {
    Vector origin;
    Vector rotation;
    int width;
    int height;
    double focal_length;
    Vector v0;
    Vector v1;
    Vector v2;
    Vector v3;
} Camera;


void camera_create_frame(Camera* c);
void camera_construct(Camera* c, Vector* origin, Vector* rotation, int width, int height, double focal_length);
void camera_generate_ray(Camera* c, double px, double py, Ray* r);

#endif
