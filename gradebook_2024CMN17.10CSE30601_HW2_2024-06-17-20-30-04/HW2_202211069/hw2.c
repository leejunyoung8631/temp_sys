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
    float r = 0;
    float g = 0;
    float b = 0;

    int q = x - 1 + (y - 1) * width;

    if (x == 0 || x == width-1 || y == 0 || y == height-1) {
        q += -1;
        int u = -1;
        int sy;
        int sx;
        for (int dy = -1; dy < 2; ++dy) {
            sy = y + dy;
            if (sy < 0 || sy >= height) {
                u += 3;
                q += width;
                continue;
            }
            for (int dx = -1; dx < 2; ++dx) {
                sx = x + dx;
                u += 1;
                q += 1;
                if (sx < 0 || sx >= width)
                    continue;
                
                r += input[q].r * filter[u];
                g += input[q].g * filter[u];
                b += input[q].b * filter[u];
            }
            q += width - 3;
        }
    }
    else {
        r += input[q].r * filter[0];
        g += input[q].g * filter[0];
        b += input[q].b * filter[0];
        q += 1;
        r += input[q].r * filter[1];
        g += input[q].g * filter[1];
        b += input[q].b * filter[1];
        q += 1;
        r += input[q].r * filter[2];
        g += input[q].g * filter[2];
        b += input[q].b * filter[2];
        q += width - 2;
        r += input[q].r * filter[3];
        g += input[q].g * filter[3];
        b += input[q].b * filter[3];
        q += 1;
        r += input[q].r * filter[4];
        g += input[q].g * filter[4];
        b += input[q].b * filter[4];
        q += 1;
        r += input[q].r * filter[5];
        g += input[q].g * filter[5];
        b += input[q].b * filter[5];
        q += width - 2;
        r += input[q].r * filter[6];
        g += input[q].g * filter[6];
        b += input[q].b * filter[6];
        q += 1;
        r += input[q].r * filter[7];
        g += input[q].g * filter[7];
        b += input[q].b * filter[7];
        q += 1;
        r += input[q].r * filter[8];
        g += input[q].g * filter[8];
        b += input[q].b * filter[8];
    }
    
    Pixel p;

    if (r < 0) {
        p.r = (unsigned char)0;
    }
    else if (r > 255) {
        p.r = (unsigned char)255;
    }
    else {
        p.r = (unsigned char)r;
    }
    if (g < 0) {
        p.g = (unsigned char)0;
    }
    else if (g > 255) {
        p.g = (unsigned char)255;
    }
    else {
        p.g = (unsigned char)g;
    }
    if (b < 0) {
        p.b = (unsigned char)0;
    }
    else if (b > 255) {
        p.b = (unsigned char)255;
    }
    else {
        p.b = (unsigned char)b;
    }

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    int o = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; x+=4) {
            output[o] = convolution(input, x, y, width, height, filter);
            o += 1;

            output[o] = convolution(input, x+1, y, width, height, filter);
            o += 1;

            output[o] = convolution(input, x+2, y, width, height, filter);
            o += 1;

            output[o] = convolution(input, x+3, y, width, height, filter);
            o += 1;
        }
    }
}