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


#define TILE_SIZE 32

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int ty = 0; ty < height; ty += TILE_SIZE) {
        for (int tx = 0; tx < width; tx += TILE_SIZE) {
            for (int y = ty; y < ty + TILE_SIZE && y < height; ++y) {
                Pixel* output_row = output + y * width;
               
                for (int x = tx; x < tx + TILE_SIZE && x < width; ++x) {
                    double r = 0;
                    double g = 0;
                    double b = 0;

                    for (int dy = -1; dy <= 1; ++dy) {
                        int ny = y + dy;
                        if (ny >= 0 && ny < height) {
                            Pixel* input_row_ny = input + ny * width;
                            for (int dx = -1; dx <= 1; ++dx) {
                                int nx = x + dx;
                                if (nx >= 0 && nx < width) {
                                    int filterIndex = (dx + 1) + (dy + 1) * 3;
                                    Pixel* input_pixel = input_row_ny + nx;
                                    float filter_value = filter[filterIndex];
                                    r += input_pixel->r * filter_value;
                                    g += input_pixel->g * filter_value;
                                    b += input_pixel->b * filter_value;
                                }
                            }
                        }
                    }

                    r = r < 0 ? 0 : (r > 255 ? 255 : r);
                    g = g < 0 ? 0 : (g > 255 ? 255 : g);
                    b = b < 0 ? 0 : (b > 255 ? 255 : b);

                    output_row[x].r = (unsigned char)r;
                    output_row[x].g = (unsigned char)g;
                    output_row[x].b = (unsigned char)b;
                }
            }
        }
    }
}
