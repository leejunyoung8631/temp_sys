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

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!

static Pixel convolution_optimized(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        int nx = x + dx;
        if (nx < 0 || nx >= height) continue;

        for (int dy = -1; dy <= 1; ++dy) {
            int ny = y + dy;
            if (ny < 0 || ny >= width) continue;

            int filter_index = (dx + 1) + (dy + 1) * 3;
            int pixel_index = nx + ny * width;

            r += input[pixel_index].r * filter[filter_index];
            g += input[pixel_index].g * filter[filter_index];
            b += input[pixel_index].b * filter[filter_index];
        }
    }

    r = r < 0 ? 0 : (r > 255 ? 255 : r);
    g = g < 0 ? 0 : (g > 255 ? 255 : g);
    b = b < 0 ? 0 : (b > 255 ? 255 : b);

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
            output[y * width + x] = convolution_optimized(input, x, y, width, height, filter);
        }
    }
}
