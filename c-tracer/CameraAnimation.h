#include "Vector.h"

#ifndef CAMERA_ANIMATION_H_
#define CAMERA_ANIMATION_H_


typedef struct {
    int frame_number;
    Vector origin;
    Vector rotation;
    double focal_length;
} CameraAnimation;


void camera_animation_construct(CameraAnimation* ca, int frame_number, Vector* origin, Vector* rotation, double focal_length);


#endif
