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


static Pixel convolution(const Pixel* input, int x, int y, int width, int height, const float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        int y_index = y + dy;
        if (y_index < 0 || y_index >= height)
            continue;

        for (int dx = -1; dx <= 1; ++dx) {
            int x_index = x + dx;
            if (x_index < 0 || x_index >= width)
                continue;

            int filter_index = (dx + 1) + (dy + 1) * 3;
            int image_index = x_index + y_index * width;

            r += input[image_index].r * filter[filter_index];
            g += input[image_index].g * filter[filter_index];
            b += input[image_index].b * filter[filter_index];
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
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    int width_unrolled = width / 4 * 4; 
    for (int y = 0; y < height; ++y) {
        int x;
        for (x = 0; x < width_unrolled; x += 4) {
            output[x + y * width] = convolution(input, x, y, width, height, filter);
            output[x + 1 + y * width] = convolution(input, x + 1, y, width, height, filter);
            output[x + 2 + y * width] = convolution(input, x + 2, y, width, height, filter);
            output[x + 3 + y * width] = convolution(input, x + 3, y, width, height, filter);
        }
        for (; x < width; ++x) {
            output[x + y * width] = convolution(input, x, y, width, height, filter);
        }
    }
}