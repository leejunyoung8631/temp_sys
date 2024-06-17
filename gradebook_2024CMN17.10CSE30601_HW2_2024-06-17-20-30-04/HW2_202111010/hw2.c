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
    int r = 0;
    int g = 0;
    int b = 0;
    int f_tmp = 0;
    int i_idx = 0;
    Pixel p;

    if (x-1 >= 0 && x-1 < width && y-1 >= 0 && y-1 < height) {
        i_idx = (x-1)+(y-1)*width;
        f_tmp = filter[0];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (x >= 0 && x < width && y-1 >= 0 && y-1 < height) {
        i_idx = x+(y-1)*width;
        f_tmp = filter[1];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (x+1 >= 0 && x+1 < width && y-1 >= 0 && y-1 < height) {
        i_idx = (x+1)+(y-1)*width;
        f_tmp = filter[2];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (x-1 >= 0 && x-1 < width && y >= 0 && y < height) {
        i_idx = (x-1)+y*width;
        f_tmp = filter[3];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    i_idx = x+y*width;
    f_tmp = filter[4];
    r += input[i_idx].r * f_tmp;
    g += input[i_idx].g * f_tmp;
    b += input[i_idx].b * f_tmp;
    if (x+1 >= 0 && x+1 < width && y >= 0 && y < height) {
        i_idx = (x+1)+y*width;
        f_tmp = filter[5];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (x-1 >= 0 && x-1 < width && y+1 >= 0 && y+1 < height) {
        i_idx = (x-1)+(y+1)*width;
        f_tmp = filter[6];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (x >= 0 && x < width && y+1 >= 0 && y+1 < height) {
        i_idx = x+(y+1)*width;
        f_tmp = filter[7];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (x+1 >= 0 && x+1 < width && y+1 >= 0 && y+1 < height) {
        i_idx = (x+1)+(y+1)*width;
        f_tmp = filter[8];
        r += input[i_idx].r * f_tmp;
        g += input[i_idx].g * f_tmp;
        b += input[i_idx].b * f_tmp;
    }
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

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
    int tmp = 0;

    for (int y = 0; y < height; ++y) {
        tmp = y*width;
        for (int x = 0; x < width; ++x) {
            output[x+tmp] = convolution(input, x, y, width, height, filter);
        }
    }
}
