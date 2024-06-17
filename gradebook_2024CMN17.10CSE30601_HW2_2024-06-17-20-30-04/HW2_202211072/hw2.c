// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
//
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

static Pixel convolution_optimized(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            int ix = x + dx;
            int iy = y + dy;
            if (ix < 0 || ix >= width || iy < 0 || iy >= height)
                continue;

            Pixel *p = &input[ix + iy * width];
            float f = filter[(dx+1) + (dy+1) * 3];
            r += p->r * f;
            g += p->g * f;
            b += p->b * f;
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            output[x + y * width] = convolution_optimized(input, x, y, width, height, filter);
        }
    }
}
