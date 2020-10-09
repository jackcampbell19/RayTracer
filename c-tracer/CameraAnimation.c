#include "CameraAnimation.h"


void camera_animation_construct(CameraAnimation* ca, int frame_number, Vector* origin, Vector* rotation, double focal_length) {
    ca->frame_number = frame_number;
    vector_copy(&ca->origin, origin);
    vector_copy(&ca->rotation, rotation);
    ca->focal_length = focal_length;
}
