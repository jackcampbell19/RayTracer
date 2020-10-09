#include "Vector.h"
#include "Ray.h"
#include "ArrayNode.h"
#include "CameraAnimation.h"


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
    ArrayNode* first_animation_node;
    ArrayNode* last_animation_node;
} Camera;


void camera_create_frame(Camera* c);
void camera_construct(Camera* c, Vector* origin, Vector* rotation, int width, int height, double focal_length);
void camera_generate_ray(Camera* c, double px, double py, Ray* r);
void camera_set_origin(Camera* c, Vector* origin);
void camera_set_rotation(Camera* c, Vector* rotation);
void camera_set_size(Camera* c, int width, int height);
void camera_set_focal_length(Camera* c, double focal_length);

void camera_animate(Camera* c, int frame_number, Vector* origin, Vector* rotation, double focal_length);
void camera_apply_animation(Camera* c, CameraAnimation* a);

#endif
