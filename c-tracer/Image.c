#include "Image.h"
#include <stdio.h>


void image_write_pix_rgb_to_file(int* pix_rgb, int array_size, char* filepath) {
    FILE* fp = fopen(filepath, "w+");
    char comma[3] = ",";
    char conv[5];
    for (int i = 0; i < array_size; i++) {
        sprintf(conv, "%d", pix_rgb[i]);
        fputs(conv, fp);
        fputc(comma[0], fp);
    }
}
