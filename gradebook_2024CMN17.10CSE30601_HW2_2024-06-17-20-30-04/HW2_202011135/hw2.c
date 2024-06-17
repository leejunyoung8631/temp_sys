// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include "bmplib.h"
#include "hw2.h"

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!

void filter_optimized(void* args[]) {                           // Merging convolution() and filter_optimized() 
    unsigned int width = *(unsigned int*)args[0];               // Eliminate Dynamic Memory Allocation
    unsigned int height = *(unsigned int*)args[1];
    Pixel* restrict input = (Pixel* restrict)args[2];           // Removing Aliasing (using restrict)
    Pixel* restrict output = (Pixel* restrict)args[3];          // Removing Aliasing (using restrict)
    float* restrict filter = (float* restrict)args[4];          // Removing Aliasing (using restrict)

    int int_filter[9];                                          // Integer conversion for filter values
    for (int i = 0; i < 9; ++i) {
        int_filter[i] = (int)filter[i] << 8;
    }

    for (int y = 0; y < height; ++y) {
        int row_start_index = y * width;                        // Share Common Subexpressions 
        int x = 0;

        for (; x <= width - 4; x += 4) {                        // Loop Unrolling 
            int r0 = 0, g0 = 0, b0 = 0;                         // Variable Type Optimization 
            int r1 = 0, g1 = 0, b1 = 0;
            int r2 = 0, g2 = 0, b2 = 0;
            int r3 = 0, g3 = 0, b3 = 0;

            for (int dy = -1; dy < 2; ++dy) {
                int ny = y + dy;
                if (ny < 0 || ny >= height) continue;

                for (int dx = -1; dx < 2; ++dx) {
                    int nx0 = x + dx;
                    int nx1 = x + dx + 1;
                    int nx2 = x + dx + 2;
                    int nx3 = x + dx + 3;
                    int filter_index = dx + dy + dy + dy + 4;   // Reduced Multiplications, Share Common Subexpressions 
                    int nyw = ny * width;

                    if (nx0 >= 0 && nx0 < width) {
                        int index0 = nx0 + nyw;                 // Share Common Subexpressions 
                        r0 += input[index0].r * int_filter[filter_index];
                        g0 += input[index0].g * int_filter[filter_index];
                        b0 += input[index0].b * int_filter[filter_index];
                    }

                    if (nx1 >= 0 && nx1 < width) {
                        int index1 = nx1 + nyw;
                        r1 += input[index1].r * int_filter[filter_index];
                        g1 += input[index1].g * int_filter[filter_index];
                        b1 += input[index1].b * int_filter[filter_index];
                    }

                    if (nx2 >= 0 && nx2 < width) {
                        int index2 = nx2 + nyw;
                        r2 += input[index2].r * int_filter[filter_index];
                        g2 += input[index2].g * int_filter[filter_index];
                        b2 += input[index2].b * int_filter[filter_index];
                    }

                    if (nx3 >= 0 && nx3 < width) {
                        int index3 = nx3 + nyw;
                        r3 += input[index3].r * int_filter[filter_index];
                        g3 += input[index3].g * int_filter[filter_index];
                        b3 += input[index3].b * int_filter[filter_index];
                    }
                }
            }

            r0 = (r0 >> 8) < 0 ? 0 : (r0 >> 8 > 255 ? 255 : r0 >> 8);
            g0 = (g0 >> 8) < 0 ? 0 : (g0 >> 8 > 255 ? 255 : g0 >> 8);
            b0 = (b0 >> 8) < 0 ? 0 : (b0 >> 8 > 255 ? 255 : b0 >> 8);

            r1 = (r1 >> 8) < 0 ? 0 : (r1 >> 8 > 255 ? 255 : r1 >> 8);
            g1 = (g1 >> 8) < 0 ? 0 : (g1 >> 8 > 255 ? 255 : g1 >> 8);
            b1 = (b1 >> 8) < 0 ? 0 : (b1 >> 8 > 255 ? 255 : b1 >> 8);

            r2 = (r2 >> 8) < 0 ? 0 : (r2 >> 8 > 255 ? 255 : r2 >> 8);
            g2 = (g2 >> 8) < 0 ? 0 : (g2 >> 8 > 255 ? 255 : g2 >> 8);
            b2 = (b2 >> 8) < 0 ? 0 : (b2 >> 8 > 255 ? 255 : b2 >> 8);

            r3 = (r3 >> 8) < 0 ? 0 : (r3 >> 8 > 255 ? 255 : r3 >> 8);
            g3 = (g3 >> 8) < 0 ? 0 : (g3 >> 8 > 255 ? 255 : g3 >> 8);
            b3 = (b3 >> 8) < 0 ? 0 : (b3 >> 8 > 255 ? 255 : b3 >> 8);

            output[x + row_start_index].r = (unsigned char)r0;
            output[x + row_start_index].g = (unsigned char)g0;
            output[x + row_start_index].b = (unsigned char)b0;

            output[x + row_start_index + 1].r = (unsigned char)r1;
            output[x + row_start_index + 1].g = (unsigned char)g1;
            output[x + row_start_index + 1].b = (unsigned char)b1;

            output[x + row_start_index + 2].r = (unsigned char)r2;
            output[x + row_start_index + 2].g = (unsigned char)g2;
            output[x + row_start_index + 2].b = (unsigned char)b2;

            output[x + row_start_index + 3].r = (unsigned char)r3;
            output[x + row_start_index + 3].g = (unsigned char)g3;
            output[x + row_start_index + 3].b = (unsigned char)b3;
        }
    }
}
