#include "Camera.h"
#include "Triangle.h"
#include "ArrayNode.h"
#include "Object.h"
#include "Light.h"

#ifndef SCENE_H_
#define SCENE_H_


typedef struct {
    Camera* camera;
    double resolution; // Must be whole number
    ArrayNode* object_first_node;
    ArrayNode* object_last_node;
    ArrayNode* light_first_node;
    ArrayNode* light_last_node;
} Scene;


void scene_construct(Scene* s, Camera* c, double resolution);
void scene_render_perspective(Scene* s, int* pix_rgb);
void scene_add_object(Scene* s, Object* o);
void scene_add_light(Scene* s, Light* l);
int scene_get_pix_rgb_size(Scene* s);
double scene_get_light_intensity(Scene* s, Vector* intersection, double angle);
int* scene_create_pix_rgb(Scene* s);
int scene_get_closest_object_intersection(Scene* s, Ray* ray, Vector* i, double* a, Color* c, Vector* light_trace_point);
void scene_free(Scene* s);
void scene_set_resolution(Scene* s, double resolution);


#endif
