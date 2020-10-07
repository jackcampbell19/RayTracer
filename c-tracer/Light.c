#include "Light.h"
#include <stdlib.h>


Light* light_create(Vector* origin, double radius, double intensity, Color* color) {
    Light* light = (Light*) malloc(sizeof(Light));
    vector_copy(&light->origin, origin);
    light->radius = radius;
    light->intensity = intensity;
    color_copy(&light->color, color);
    return light;
}
