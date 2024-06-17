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
    const unsigned int width = *(const unsigned int*)args[0];
    const unsigned int height = *(const unsigned int*)args[1];
    const Pixel* restrict const input = (const Pixel*)args[2];
    Pixel* restrict const output = (Pixel*)args[3];
    const float* restrict const filter = (const float*)args[4];

    // Precompute the filter values
    float filter_values[9];
    for (int i = 0; i < 9; ++i) {
        filter_values[i] = filter[i];
    }

    for (int y = 0; y < height; ++y) {
        Pixel* restrict const output_row = output + y * width;

        for (int x = 0; x < width; x += 4) {
            double r1 = 0, g1 = 0, b1 = 0;
            double r2 = 0, g2 = 0, b2 = 0;
            double r3 = 0, g3 = 0, b3 = 0;
            double r4 = 0, g4 = 0, b4 = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                const int yy = y + dy;
                if (yy >= 0 && yy < height) {
                    const Pixel* restrict const row = input + yy * width;

                    for (int dx = -1; dx <= 1; ++dx) {
                        const int xx1 = x + dx;
                        const int xx2 = x + dx + 1;
                        const int xx3 = x + dx + 2;
                        const int xx4 = x + dx + 3;
                        const float filter_value = filter_values[(dy + 1) * 3 + (dx + 1)];

                        if (xx1 >= 0 && xx1 < width) {
                            const Pixel* restrict const pixel1 = row + xx1;
                            r1 += pixel1->r * filter_value;
                            g1 += pixel1->g * filter_value;
                            b1 += pixel1->b * filter_value;
                        }

                        if (xx2 >= 0 && xx2 < width && x + 1 < width) {
                            const Pixel* restrict const pixel2 = row + xx2;
                            r2 += pixel2->r * filter_value;
                            g2 += pixel2->g * filter_value;
                            b2 += pixel2->b * filter_value;
                        }

                        if (xx3 >= 0 && xx3 < width && x + 2 < width) {
                            const Pixel* restrict const pixel3 = row + xx3;
                            r3 += pixel3->r * filter_value;
                            g3 += pixel3->g * filter_value;
                            b3 += pixel3->b * filter_value;
                        }

                        if (xx4 >= 0 && xx4 < width && x + 3 < width) {
                            const Pixel* restrict const pixel4 = row + xx4;
                            r4 += pixel4->r * filter_value;
                            g4 += pixel4->g * filter_value;
                            b4 += pixel4->b * filter_value;
                        }
                    }
                }
            }

            // Clamp the values to the range [0, 255]
            Pixel p1, p2, p3, p4;
            p1.r = (unsigned char)((r1 < 0) ? 0 : ((r1 > 255) ? 255 : r1));
            p1.g = (unsigned char)((g1 < 0) ? 0 : ((g1 > 255) ? 255 : g1));
            p1.b = (unsigned char)((b1 < 0) ? 0 : ((b1 > 255) ? 255 : b1));
            output_row[x] = p1;

            if (x + 1 < width) {
                p2.r = (unsigned char)((r2 < 0) ? 0 : ((r2 > 255) ? 255 : r2));
                p2.g = (unsigned char)((g2 < 0) ? 0 : ((g2 > 255) ? 255 : g2));
                p2.b = (unsigned char)((b2 < 0) ? 0 : ((b2 > 255) ? 255 : b2));
                output_row[x + 1] = p2;
            }

            if (x + 2 < width) {
                p3.r = (unsigned char)((r3 < 0) ? 0 : ((r3 > 255) ? 255 : r3));
                p3.g = (unsigned char)((g3 < 0) ? 0 : ((g3 > 255) ? 255 : g3));
                p3.b = (unsigned char)((b3 < 0) ? 0 : ((b3 > 255) ? 255 : b3));
                output_row[x + 2] = p3;
            }

            if (x + 3 < width) {
                p4.r = (unsigned char)((r4 < 0) ? 0 : ((r4 > 255) ? 255 : r4));
                p4.g = (unsigned char)((g4 < 0) ? 0 : ((g4 > 255) ? 255 : g4));
                p4.b = (unsigned char)((b4 < 0) ? 0 : ((b4 > 255) ? 255 : b4));
                output_row[x + 3] = p4;
            }
        }
    }
}