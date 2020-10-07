#include "Color.h"
#include "Vector.h"

#ifndef LIGHT_H_
#define LIGHT_H_


typedef struct {
    Vector origin;
    double radius;
    double intensity;
    Color color;
} Light;


Light* light_create(Vector* origin, double radius, double intensity, Color* color);


#endif
