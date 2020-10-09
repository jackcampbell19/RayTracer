#include "Scene.h"
#include <stdlib.h>
#include <stdio.h>
#include "ArrayNode.h"
#include "Object.h"
#include "Color.h"
#include <math.h>
#include "Light.h"
#include <float.h>


void scene_construct(Scene* s, Camera* c, double resolution) {
    s->camera = c;
    s->resolution = resolution;
    s->object_first_node = array_node_first();
    s->object_last_node = s->object_first_node;
    s->light_first_node = array_node_first();
    s->light_last_node = s->light_first_node;
}


int get_1d_index(int x, int y, int width) {
    return y * width + x;
}


int scene_get_pix_rgb_size(Scene* s) {
    return (s->camera->width * s->resolution) * (s->camera->height * s->resolution) * 3;
}


int* scene_create_pix_rgb(Scene* s) {
    return (int*) calloc(scene_get_pix_rgb_size(s), sizeof(int));
}


// Renders the scene in perspective
void scene_render_perspective(Scene* s, int* pix_rgb) {
  // Adjust the width and height to the resolution
    double width = s->camera->width * s->resolution;
    double height = s->camera->height * s->resolution;
    // Iterate over every pixel of the final image
    for (double y = 0; y < height; y++) {
        for (double x = 0; x < width; x++) {
            // Calculate percentages for the width and height
            double px = x / width;
            double py = y / height;
            // Calculate the idex of the pixel in the output array
            int index = get_1d_index(width - x - 1, height - y - 1, (int) width) * 3;
            // Generate cameras ray
            Ray ray;
            camera_generate_ray(s->camera, px, py, &ray);
            // Get the closest object intersection
            double angle;
            Vector intersection;
            Color color;
            Vector light_trace_point;
            if (scene_get_closest_object_intersection(s, &ray, &intersection, &angle, &color, &light_trace_point)) {
                // If there is an intersection
                double intensity = scene_get_light_intensity(s, &light_trace_point, angle);
                pix_rgb[index + 0] = (int) ((double) color.r * intensity);
                pix_rgb[index + 1] = (int) ((double) color.g * intensity);
                pix_rgb[index + 2] = (int) ((double) color.b * intensity);
            }
        }
    }
}


// Gets the closest intersection of all objects in the scene. Returns 0 if no intersection, 1 if intersection.
// Assigns intersection (i), angle (a), and color (c) values on success. light_trace_point is the point to use to continue light tracing.
int scene_get_closest_object_intersection(Scene* s, Ray* ray, Vector* i, double* a, Color* c, Vector* light_trace_point) {
    // Setup tracking var
    double shortest_length = DBL_MAX;
    // Iterate over all object nodes
    ArrayNode* current = s->object_first_node;
    while (1) {
        if (!current->is_head) {
            // Get the object from the node
            Object* obj = (Object*) current->value;
            // Check that the object is visible
            if (obj->visible) {
                // Get the clostest intersection from the object
                double angle;
                Vector intersection;
                Color color;
                if (object_get_closest_intersection(obj, ray, &intersection, &angle, &color)) {
                    // If there is an intersection, check that the distance is shorter than the existing one
                    Vector d;
                    vector_subtract(&intersection, &ray->origin, &d);
                    if (vector_norm(&d) < shortest_length) {
                        shortest_length = vector_norm(&d);
                        // Copy the values to the output
                        vector_copy(i, &intersection);
                        *a = angle;
                        color_copy(c, &color);
                        vector_multiply_t(&d, 1 / shortest_length * 0.00001);
                        vector_subtract(&intersection, &d, light_trace_point);
                    }
                }
            }
        }
        if (!current->has_next) {
            break;
        }
        current = (ArrayNode*) current->next;
    }
    return shortest_length < DBL_MAX;
}


void scene_add_object(Scene* s, Object* o) {
    ArrayNode* node = array_node_create((unsigned long) o);
    array_node_set_next(s->object_last_node, node);
    s->object_last_node = node;
}


void scene_add_light(Scene* s, Light* l) {
    ArrayNode* node = array_node_create((unsigned long) l);
    array_node_set_next(s->light_last_node, node);
    s->light_last_node = node;
}


// Gets the intensity of the light at the given point in the scene
double scene_get_light_intensity(Scene* s, Vector* intersection, double angle) {
    // return -pow((fabs(angle) / 90) - 1, 2) + 1;

    double ambient = (-pow((fabs(angle) / 90) - 1, 2) + 1);

    ArrayNode* current = s->light_first_node;
    Vector i;
    double a;
    Color c;
    double output = 0;
    while (1) {
        if (!current->is_head) {
            // Get the light from the node
            Light* light = (Light*) current->value;
            Vector origin;
            vector_copy(&origin, intersection);
            Vector direction;
            vector_subtract(&light->origin, &origin, &direction);
            Ray ray;
            ray_construct(&ray, &origin, &direction);
            Vector ltp;
            if (!scene_get_closest_object_intersection(s, &ray, &i, &a, &c, &ltp)) {
                output += light_get_distance_intensity(light, intersection) * ambient;
            }
        }
        if (!current->has_next) {
            break;
        }
        current = (ArrayNode*) current->next;
    }
    return output;
}


void scene_set_resolution(Scene* s, double resolution) {
    s->resolution = resolution;
}


// Frees all allocated memory in the scene
void scene_free(Scene* s) {
  // Free objects
  ArrayNode* current = s->object_first_node;
  while (1) {
      if (!current->is_head) {
          // Get the object from the node
          Object* o = (Object*) current->value;
          // Check that the object is visible
          for (int i = 0; i < o->triangle_count; i++) {
              Triangle* t = o->triangles[i];
              // Free all triangles
              free(t);
          }
          // Free object
          free(o);
      }
      if (!current->has_next) {
          // Free the node
          free(current);
          break;
      }
      ArrayNode* current_tmp = (ArrayNode*) current->next;
      // Free the node
      free(current);
      current = current_tmp;
  }
  // Free lights
  current = s->light_first_node;
  while (1) {
      if (!current->is_head) {
          // Get the object from the node
          Light* l = (Light*) current->value;
          // Free object
          free(l);
      }
      if (!current->has_next) {
          // Free the node
          free(current);
          break;
      }
      ArrayNode* current_tmp = (ArrayNode*) current->next;
      // Free the node
      free(current);
      current = current_tmp;
  }
  // Free camera
  free(s->camera);
}
