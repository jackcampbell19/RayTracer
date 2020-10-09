#include "Light.h"
#include <stdlib.h>
#include <math.h>


Light* light_create(Vector* origin, double radius, double intensity, Color* color) {
    Light* light = (Light*) malloc(sizeof(Light));
    vector_copy(&light->origin, origin);
    light->radius = radius;
    light->intensity = intensity;
    color_copy(&light->color, color);
    return light;
}


// Returns the light intensity for a point
double light_get_distance_intensity(Light* light, Vector* point) {
    Vector d;
    vector_subtract(point, &light->origin, &d);
    double distance = vector_norm(&d);
    return (1 - fmin(distance / light->radius, 1)) * light->intensity;
}
