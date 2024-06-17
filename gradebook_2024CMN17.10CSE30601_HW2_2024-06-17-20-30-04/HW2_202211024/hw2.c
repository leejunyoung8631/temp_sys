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

static Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0, g = 0, b = 0;
    int idx, fidx;

    for (int dy = -1; dy <= 1; ++dy) {
        int y_pos = y + dy;
        
        for (int dx = -1; dx <= 1; ++dx) {
            int x_pos = x + dx;

            if (x_pos < 0 || x_pos >= width || y_pos < 0 || y_pos >= height)
                continue;

            idx = x_pos + y_pos * width;
            fidx = (dx + 1) + (dy + 1) * 3;

            r += input[idx].r * filter[fidx];
            g += input[idx].g * filter[fidx];
            b += input[idx].b * filter[fidx];
        }
    }

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            output[x + y * width] = convolution(input, x, y, width, height, filter);
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                output[x + y * width] = convolution(input, x, y, width, height, filter);
            }
        }
    }
}