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

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r = 0;
	    double g = 0;
	    double b = 0;
            for (int dy = -1; dy < 2; ++dy) {
                int y_2 = y + dy;
                if (y_2 >= height || y_2 < 0) continue;
                for (int dx = -1; dx < 2; ++dx) {
                    int x_2 = x + dx;
                    if (x_2 < 0 || x_2 >= width) continue;
                    int filter_idx = (dy + 1) * 3 + (dx + 1);
                    int input_idx = y_2 * width + x_2;
                    r += input[input_idx].r * filter[filter_idx];
                    g += input[input_idx].g * filter[filter_idx];
                    b += input[input_idx].b * filter[filter_idx];
                }
            }

            r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
            g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
            b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

            output[y*width + x].r = (unsigned char)r;
            output[y*width + x].g = (unsigned char)g;
            output[y*width + x].b = (unsigned char)b;
        }
    }
}
