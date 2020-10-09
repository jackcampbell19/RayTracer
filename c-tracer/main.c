#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
#include "Triangle.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Image.h"
#include "Color.h"
#include "Object.h"
#include <time.h>
#include "Light.h"
#include "Render.h"

int main(void) {

  // Set up render
  Render* render = (Render*) malloc(sizeof(Render));
  render_construct(render);
  // Adjust the resolution
  scene_set_resolution(render->scene, 3);
  // Adjust camera
  camera_set_size(render->scene->camera, 100, 100);
  // Vector camera_origin = {7, 6, 4};
  // camera_set_origin(render->scene->camera, &camera_origin);
  // Vector camera_rotation = {25, 0, -30};
  // camera_set_rotation(render->scene->camera, &camera_rotation);

  Vector cam_ani_origin = {0, 100, 50};
  for (double i = 0; i < 24; i++) {
      Vector arg_ori;
      vector_rotate_z(&cam_ani_origin, -360.0 / 24.0 * i, &arg_ori);
      Vector arg_rot = {25, 0, -360.0 / 24.0 * i};
      // Vector arg_rot = {25, 0, 0};
      // Vector origin = {0, 24 + 6 - i, 0};
      camera_animate(render->scene->camera, (int) i, &arg_ori, &arg_rot, 100);
  }

  // Add triangle
  Triangle* t0 = (Triangle*) malloc(sizeof(Triangle));
  Vector v0 = {-50, -50, 0};
  Vector v1 = {-50, 50, 0};
  Vector v2 = {50, -50, 0};
  triangle_construct(t0, &v0, &v1, &v2);
  Color color = {255, 255, 255};
  Object* tri = object_create_triangle(t0, &color);
  scene_add_object(render->scene, tri);

  // Add cube
  Vector c_origin = {0, 0, 0};
  Color c_color = {120, 0, 255};
  Object* cube = object_create_cube(&c_origin, 20, 20, 20, &c_color);
  scene_add_object(render->scene, cube);

  Triangle* t01 = (Triangle*) malloc(sizeof(Triangle));
  Vector v01 = {50, -50, 0};
  Vector v11 = {50, 50, 0};
  Vector v21 = {-50, 50, 0};
  triangle_construct(t01, &v01, &v11, &v21);
  Color color1 = {255, 255, 255};
  Object* tri1 = object_create_triangle(t01, &color1);
  scene_add_object(render->scene, tri1);


  // Add light
  Vector l_origin = {-50, -40, 80};
  Color l_color = {255, 255, 255};
  Light* light = light_create(&l_origin, 350, 0.75, &l_color);
  scene_add_light(render->scene, light);


  time_t start = time(NULL);


  render_frames(render, 0, 23);


  time_t end = time(NULL);

  printf("%ld\n", end - start);

  // Free memeory
  scene_free(render->scene);
  free(render);




  // Vector p0 = {0, 0, 0};
  // Vector p1 = {10, 0, 0};
  // Vector p2 = {0, 0, 10};
  //
  // Triangle t;
  // triangle_construct(&t, &p0, &p1, &p2);
  //
  // Vector ip = {1, 5, 1};
  // Vector dir = {1, -1, 0};
  // Ray r;
  // ray_construct(&r, &ip, &dir);
  //
  // // triangle_print(&t);
  // // ray_print(&r);
  //
  //
  // Vector vr;
  // double angle;
  // int isect = triangle_get_intersection(&t, &r, &vr, &angle);
  // printf("%d\n", isect);
  // vector_print(&vr);


  return 0;
}
