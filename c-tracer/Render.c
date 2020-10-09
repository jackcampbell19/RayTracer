#include "Render.h"
#include "Camera.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Image.h"
#include "CameraAnimation.h"


void render_construct(Render* r) {
    // Construct camera
    Camera* camera = (Camera*) malloc(sizeof(Camera));
    Vector camera_origin = {0, 0, 0};
    Vector camera_rotation = {0, 0, 0};
    camera_construct(camera, &camera_origin, &camera_rotation, 50, 50, 50);
    // Create scene
    r->scene = (Scene*) malloc(sizeof(Scene));
    scene_construct(r->scene, camera, 1);
}


// Renders out frames start to end
void render_frames(Render* r, int start, int end) {
    for (int frame_number = start; frame_number <= end; frame_number++) {
        // Apply animations for the given frame
        ArrayNode* current = r->scene->camera->first_animation_node;
        while (current->has_next) {
            current = (ArrayNode*) current->next;
            CameraAnimation* ca = (CameraAnimation*) current->value;
            // Apply camera animation
            if (ca->frame_number == frame_number) {
                camera_apply_animation(r->scene->camera, ca);
                break;
            }
            if (ca->frame_number > frame_number) {
                break;
            }
        }
        // Perform scene rendering
        int* pix_rgb = scene_create_pix_rgb(r->scene);
        scene_render_perspective(r->scene, pix_rgb);
        char fn[30] = "output/data/frame-";
        char conv[10];
        sprintf(conv, "%d", frame_number);
        strcat(fn, conv);
        image_write_pix_rgb_to_file(pix_rgb, scene_get_pix_rgb_size(r->scene), fn);
        free(pix_rgb);
    }
}
