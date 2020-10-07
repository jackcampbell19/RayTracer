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

int main(void) {


  Camera* camera = (Camera*) malloc(sizeof(Camera));
  Vector origin = {0, 12, 0};
  Vector rotation = {0, 0, 0};
  camera_construct(camera, &origin, &rotation, 60, 60, 25);

  Scene* scene = (Scene*) malloc(sizeof(Scene));
  scene_construct(scene, camera, 10);

  // Add triangle
  Triangle* t0 = (Triangle*) malloc(sizeof(Triangle));
  Vector v0 = {0, 0, 0};
  Vector v1 = {20, -5, 0};
  Vector v2 = {4, 0, 10};
  triangle_construct(t0, &v0, &v1, &v2);
  Color color = {0, 255, 0};
  Object* tri = object_create_triangle(t0, &color);
  scene_add_object(scene, tri);
  tri->visible = 1;

  // Add cube
  Vector c_origin = {10, 0, -3};
  Color c_color = {120, 0, 255};
  Object* cube = object_create_cube(&c_origin, 15, 12, 10, &c_color);
  cube->visible = 1;
  scene_add_object(scene, cube);


  // Add light
  Vector l_origin = {-5, -2, 10};
  Color l_color = {255, 255, 255};
  Light* light = light_create(&l_origin, 20, 1, &l_color);
  scene_add_light(scene, light);


  time_t start = time(NULL);


  int* pix_rgb = scene_create_pix_rgb(scene);
  scene_render_perspective(scene, pix_rgb);

  char* filepath = "myfile.txt";
  image_write_pix_rgb_to_file(pix_rgb, scene_get_pix_rgb_size(scene), filepath);

  time_t end = time(NULL);

  printf("%ld\n", end - start);

  free(camera);
  free(scene);
  free(t0);
  free(pix_rgb);




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
