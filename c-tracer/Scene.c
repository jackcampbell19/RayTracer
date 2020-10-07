#include "Scene.h"
#include <stdlib.h>
#include <stdio.h>
#include "ArrayNode.h"
#include "Object.h"
#include "Color.h"


void scene_construct(Scene* s, Camera* c, double resolution) {
    s->camera = c;
    s->resolution = resolution;
    s->first_node = array_node_first();
    s->last_node = s->first_node;
}


int get_1d_index(int x, int y, int width) {
    return y * width + x;
}


int scene_get_pix_rgb_size(Scene* s) {
    return (s->camera->width * s->resolution) * (s->camera->height * s->resolution) * 3;
}


// Renders the scene in perspective
void scene_render_perspective(Scene* s, int* pix_rgb) {
    double width = s->camera->width * s->resolution;
    double height = s->camera->height * s->resolution;
    for (double y = 0; y < height; y++) {
        for (double x = 0; x < width; x++) {
            double px = x / width;
            double py = y / height;
            int index = get_1d_index(width - x - 1, height - y - 1, (int) width) * 3;
            // Generate ray
            Ray ray;
            camera_generate_ray(s->camera, px, py, &ray);
            // Iterate over all nodes
            ArrayNode* current = s->first_node;
            while (1) {
                if (!current->is_head) {
                  // Get the object from the node
                    Object* obj = (Object*) current->value;
                    if (obj->visible) {
                      // Get the intersection from the object
                      double angle;
                      Vector intersection;
                      Color color;
                      int has_intersection = object_get_closest_intersection(obj, &ray, &intersection, &angle, &color);
                      if (has_intersection) {
                          // If there is an intersection
                          pix_rgb[index + 0] = color.r;
                          pix_rgb[index + 1] = color.g;
                          pix_rgb[index + 2] = color.b;
                      } else {
                          // If there is no intersection, asign the default background
                          pix_rgb[index + 0] = 0;
                          pix_rgb[index + 1] = 0;
                          pix_rgb[index + 2] = 0;
                      }
                    }
                }
                if (!current->has_next) {
                    break;
                }
                current = (ArrayNode*) current->next;
            }
        }
    }
}

void scene_add_object(Scene* s, Object* o) {
    ArrayNode* node = array_node_construct((unsigned long) o);
    array_node_set_next(s->last_node, node);
    s->last_node = node;
}
