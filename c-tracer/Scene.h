#include "Camera.h"
#include "Triangle.h"
#include "ArrayNode.h"
#include "Object.h"

#ifndef SCENE_H_
#define SCENE_H_


typedef struct {
    Camera* camera;
    double resolution; // Must be whole number
    ArrayNode* first_node;
    ArrayNode* last_node;
} Scene;


void scene_construct(Scene* s, Camera* c, double resolution);
void scene_render_perspective(Scene* s, int* pix_rgb);
void scene_add_object(Scene* s, Object* o);
int scene_get_pix_rgb_size(Scene* s);


#endif
