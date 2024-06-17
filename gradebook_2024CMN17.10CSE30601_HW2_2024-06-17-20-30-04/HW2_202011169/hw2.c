// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>       //추가
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
            double r = 0, g = 0, b = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                int ny = y + dy;
                if (ny < 0 || ny >= height) continue;
                int index_base = ny * width;  // index에 쓰일 베이스
                for (int dx = -1; dx <= 1; ++dx) {
                    int nx = x + dx;
                    if (nx < 0 || nx >= width) continue;
                    double filter_value = filter[(dy + 1) * 3 + (dx + 1)];
                    int index = index_base + nx;
                    r += input[index].r * filter_value;
                    g += input[index].g * filter_value;
                    b += input[index].b * filter_value;
                }
            }
            int out_index = y * width + x;
            output[out_index].r = (unsigned char)fmin(fmax(r, 0), 255);
            output[out_index].g = (unsigned char)fmin(fmax(g, 0), 255);
            output[out_index].b = (unsigned char)fmin(fmax(b, 0), 255);
        }
    }
}
