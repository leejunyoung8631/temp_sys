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

    for (unsigned int y = 0; y < height; ++y) {
        int row_offset = y * width;
        for (unsigned int x = 0; x < width; x += 4) {
            Pixel p0, p1, p2, p3;
            int idx0 = row_offset + x;

            p0 = (x < width) ? convolution(input, x, y, width, height, filter) : (Pixel){0, 0, 0};
            p1 = (x + 1 < width) ? convolution(input, x + 1, y, width, height, filter) : (Pixel){0, 0, 0};
            p2 = (x + 2 < width) ? convolution(input, x + 2, y, width, height, filter) : (Pixel){0, 0, 0};
            p3 = (x + 3 < width) ? convolution(input, x + 3, y, width, height, filter) : (Pixel){0, 0, 0};

            if (x < width) {
                output[idx0].r = p0.r;
                output[idx0].g = p0.g;
                output[idx0].b = p0.b;
            }
            if (x + 1 < width) {
                output[idx0 + 1].r = p1.r;
                output[idx0 + 1].g = p1.g;
                output[idx0 + 1].b = p1.b;
            }
            if (x + 2 < width) {
                output[idx0 + 2].r = p2.r;
                output[idx0 + 2].g = p2.g;
                output[idx0 + 2].b = p2.b;
            }
            if (x + 3 < width) {
                output[idx0 + 3].r = p3.r;
                output[idx0 + 3].g = p3.g;
                output[idx0 + 3].b = p3.b;
            }
        }
    }
}
