#include <stdlib.h>
#include <stdio.h>
#include "Camera.h"
#include "CameraAnimation.h"


// Creates and sets the frame of a camera struct
void camera_update_frame(Camera* c) {
    // Generate temp vectors
    Vector t0 = {-c->width / 2.0,
                 -c->focal_length,
                 c->height / 2.0};
    Vector t1 = {c->width / 2.0,
                 -c->focal_length,
                 c->height / 2.0};
    Vector t2 = {-c->width / 2.0,
                 -c->focal_length,
                 -c->height / 2.0};
    Vector t3 = {c->width / 2.0,
                 -c->focal_length,
                 -c->height / 2.0};
    // Apply initial frame
    vector_copy(&c->v0, &t0);
    vector_copy(&c->v1, &t1);
    vector_copy(&c->v2, &t2);
    vector_copy(&c->v3, &t3);
    // Apply rotation
    vector_rotate_x_t(&c->v0, c->rotation.x);
    vector_rotate_y_t(&c->v0, c->rotation.y);
    vector_rotate_z_t(&c->v0, c->rotation.z);
    vector_rotate_x_t(&c->v1, c->rotation.x);
    vector_rotate_y_t(&c->v1, c->rotation.y);
    vector_rotate_z_t(&c->v1, c->rotation.z);
    vector_rotate_x_t(&c->v2, c->rotation.x);
    vector_rotate_y_t(&c->v2, c->rotation.y);
    vector_rotate_z_t(&c->v2, c->rotation.z);
    vector_rotate_x_t(&c->v3, c->rotation.x);
    vector_rotate_y_t(&c->v3, c->rotation.y);
    vector_rotate_z_t(&c->v3, c->rotation.z);
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
    c->first_animation_node = array_node_first();
    camera_update_frame(c);
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


void camera_set_origin(Camera* c, Vector* origin) {
    vector_copy(&c->origin, origin);
    camera_update_frame(c);
}


void camera_set_rotation(Camera* c, Vector* rotation) {
    vector_copy(&c->rotation, rotation);
    camera_update_frame(c);
}


void camera_set_size(Camera* c, int width, int height) {
    c->width = width;
    c->height = height;
    camera_update_frame(c);
}


void camera_set_focal_length(Camera* c, double focal_length) {
    c->focal_length = focal_length;
    camera_update_frame(c);
}


// Places the animation in the array at the appropriate place
void camera_animate(Camera* c, int frame_number, Vector* origin, Vector* rotation, double focal_length) {
  ArrayNode* current = c->first_animation_node;
  ArrayNode* prev = current;
  while (1) {
      if (!current->is_head) {
          // Get the CameraAnimation from the node
          CameraAnimation* ca = (CameraAnimation*) current->value;
          if (ca->frame_number > frame_number) {
              break;
          }
      }
      if (!current->has_next) {
          prev = current;
          break;
      }
      prev = current;
      current = (ArrayNode*) current->next;
  }
  CameraAnimation* cam_ani = (CameraAnimation*) malloc(sizeof(CameraAnimation));
  camera_animation_construct(cam_ani, frame_number, origin, rotation, focal_length);
  ArrayNode* new = array_node_create((unsigned long) cam_ani);
  if (prev->has_next) {
      array_node_set_next(new, (ArrayNode*) prev->next);
  }
  array_node_set_next(prev, new);
}


void camera_apply_animation(Camera* c, CameraAnimation* a) {
    vector_copy(&c->origin, &a->origin);
    vector_copy(&c->rotation, &a->rotation);
    c->focal_length = a->focal_length;
    camera_update_frame(c);
}
