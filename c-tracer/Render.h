#include "Scene.h"


#ifndef RENDER_H_
#define RENDER_H_


typedef struct {
    int frame_count;
    Scene* scene;
} Render;


void render_construct(Render* r);
void render_frames(Render* r, int start, int end);


#endif
