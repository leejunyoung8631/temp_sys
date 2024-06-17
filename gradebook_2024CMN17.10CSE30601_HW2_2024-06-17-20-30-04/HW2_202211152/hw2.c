#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

static Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            if ((y + dy) < 0 || (y + dy) >= height)
                continue;

            if ((x + dx) < 0 || (x + dx) >= width)
                continue;

            r += input[(x+dx)+(y+dy)*width].r * filter[(dx+1)+(dy+1)*3];
            g += input[(x+dx)+(y+dy)*width].g * filter[(dx+1)+(dy+1)*3];
            b += input[(x+dx)+(y+dy)*width].b * filter[(dx+1)+(dy+1)*3];
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            output[y * width + x] = convolution(input, x, y, width, height, filter);
        }
    }
}