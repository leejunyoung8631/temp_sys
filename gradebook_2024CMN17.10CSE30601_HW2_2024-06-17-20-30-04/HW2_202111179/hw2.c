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

static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    // Unrolling the loops to reduce the overhead
    for (int dy = -1; dy <= 1; ++dy) {
        int y_index = y + dy;
        if (y_index < 0 || y_index >= height)
            continue;
        
        for (int dx = -1; dx <= 1; ++dx) {
            int x_index = x + dx;
            if (x_index < 0 || x_index >= width)
                continue;

            float filter_value = filter[(dx+1) + (dy+1) * 3];
            Pixel pixel = input[x_index + y_index * width];

            r += pixel.r * filter_value;
            g += pixel.g * filter_value;
            b += pixel.b * filter_value;
        }
    }

    // Clamping the values
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

    #pragma omp parallel for
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            output[x + y * width] = convolution(input, x, y, width, height, filter);
        }
    }
}