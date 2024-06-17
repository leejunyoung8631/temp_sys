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

// Inline convolution function
static inline Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    int dy_11 = 1;
    int dy_22 = 4;
    int dy_33 = 7;

    int index_1 = -1;
    int index_2 = -1;
    int index_3 = -1;
    int index_4 = -1;
    int index_5 = -1;
    int index_6 = -1;
    int index_7 = -1;
    int index_8 = -1;
    int index_9 = -1;

    if (y - 1 >= 0 && y - 1 < height) {
        if (x - 1 >= 0 && x - 1 < width)
            index_1 = (x - 1) + (y - 1) * width;
        if (x >= 0 && x < width)
            index_2 = x + (y - 1) * width;
        if (x + 1 >= 0 && x + 1 < width)
            index_3 = (x + 1) + (y - 1) * width;
    }

    if (y >= 0 && y < height) {
        if (x - 1 >= 0 && x - 1 < width)
            index_4 = (x - 1) + y * width;
        if (x >= 0 && x < width)
            index_5 = x + y * width;
        if (x + 1 >= 0 && x + 1 < width)
            index_6 = (x + 1) + y * width;
    }

    if (y + 1 >= 0 && y + 1< height) {
        if (x - 1 >= 0 && x - 1 < width)
            index_7 = (x -1 ) + (y + 1) * width;
        if (x >= 0 && x < width)
            index_8 = x + (y + 1) * width;
        if (x + 1 >= 0 && x + 1 < width)
            index_9 = (x + 1) + (y + 1) * width;
    }

    int filter_index_1 = -1 + dy_11;
    int filter_index_2 = dy_11;
    int filter_index_3 = 1 + dy_11;
    int filter_index_4 = -1 + dy_22;
    int filter_index_5 = dy_22;
    int filter_index_6 = 1 + dy_22;
    int filter_index_7 = -1 + dy_33;
    int filter_index_8 = dy_33;
    int filter_index_9 = 1 + dy_33;

    if (index_1 >= 0) {
        r += input[index_1].r * filter[filter_index_1];
        g += input[index_1].g * filter[filter_index_1];
        b += input[index_1].b * filter[filter_index_1];
    }
    if (index_2 >= 0) {
        r += input[index_2].r * filter[filter_index_2];
        g += input[index_2].g * filter[filter_index_2];
        b += input[index_2].b * filter[filter_index_2];
    }
    if (index_3 >= 0) {
        r += input[index_3].r * filter[filter_index_3];
        g += input[index_3].g * filter[filter_index_3];
        b += input[index_3].b * filter[filter_index_3];
    }
    if (index_4 >= 0) {
        r += input[index_4].r * filter[filter_index_4];
        g += input[index_4].g * filter[filter_index_4];
        b += input[index_4].b * filter[filter_index_4];
    }
    if (index_5 >= 0) {
        r += input[index_5].r * filter[filter_index_5];
        g += input[index_5].g * filter[filter_index_5];
        b += input[index_5].b * filter[filter_index_5];
    }
    if (index_6 >= 0) {
        r += input[index_6].r * filter[filter_index_6];
        g += input[index_6].g * filter[filter_index_6];
        b += input[index_6].b * filter[filter_index_6];
    }
    if (index_7 >= 0) {
        r += input[index_7].r * filter[filter_index_7];
        g += input[index_7].g * filter[filter_index_7];
        b += input[index_7].b * filter[filter_index_7];
    }
    if (index_8 >= 0) {
        r += input[index_8].r * filter[filter_index_8];
        g += input[index_8].g * filter[filter_index_8];
        b += input[index_8].b * filter[filter_index_8];
    }
    if (index_9 >= 0) {
        r += input[index_9].r * filter[filter_index_9];
        g += input[index_9].g * filter[filter_index_9];
        b += input[index_9].b * filter[filter_index_9];
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
    

// Optimized filter function with inline keyword
inline void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (unsigned int y = 0; y < height; ++y) {
        unsigned int y_width = y * width;
        for (unsigned int x = 0; x < width; x += 2) {
            unsigned int index1 = y_width + x;
            unsigned int index2 = index1 + 1;

            output[index1] = convolution(input, x, y, width, height, filter);
            if (x + 1 < width) {
                output[index2] = convolution(input, x + 1, y, width, height, filter);
            }
        }
    }
}
