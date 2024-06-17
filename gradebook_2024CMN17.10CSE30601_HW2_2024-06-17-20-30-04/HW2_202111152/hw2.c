#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

#define SCALE_FACTOR 8192
#define SCALE_SHIFT 13  // Equivalent to log2(SCALE_FACTOR)

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    long long int int_filter[9];
    for (int i = 0; i < 9; ++i) {
        int_filter[i] = (int)(filter[i] * SCALE_FACTOR);
    }

    int xx = 0, yy = 0;
    long long int r = 0, g = 0, b = 0;

    unsigned int y = 0;
    unsigned int x = 0;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
            r = 0, g = 0, b = 0;
            
            // dy = -1
            yy = y - 1;
            if (yy >= 0) {
                // dx = -1
                xx = x - 1;
                if (xx >= 0 ) {
                    Pixel px = input[xx + yy * width];
                    r += px.r * int_filter[0]; g += px.g * int_filter[0]; b += px.b * int_filter[0];
                }
                // dx = 0
                xx++;
                Pixel px = input[xx + yy * width];
                r += px.r * int_filter[1]; g += px.g * int_filter[1]; b += px.b * int_filter[1];
                
                // dx = 1
                xx++;
                if (xx < width) {
                    Pixel px = input[xx + yy * width];
                    r += px.r * int_filter[2]; g += px.g * int_filter[2]; b += px.b * int_filter[2];
                }
            }

            // dy = 0
            yy++;
            // dx = -1
            xx = x - 1;
            if (xx >= 0 ) {
                Pixel px = input[xx + yy * width];
                r += px.r * int_filter[3]; g += px.g * int_filter[3]; b += px.b * int_filter[3];
            }
            // dx = 0
            xx++;
            Pixel px = input[xx + yy * width];
            r += px.r * int_filter[4]; g += px.g * int_filter[4]; b += px.b * int_filter[4];
            // dx = 1
            xx++;
            if (xx < width) {
                Pixel px = input[xx + yy * width];
                r += px.r * int_filter[5]; g += px.g * int_filter[5]; b += px.b * int_filter[5];
            }

            // dy = 1
            yy++;
            if (yy < height) {
                // dx = -1
                xx = x - 1;
                if (xx >= 0 ) {
                    Pixel px = input[xx + yy * width];
                    r += px.r * int_filter[6]; g += px.g * int_filter[6]; b += px.b * int_filter[6];
                }
                // dx = 0
                xx++;
                Pixel px = input[xx + yy * width];
                r += px.r * int_filter[7]; g += px.g * int_filter[7]; b += px.b * int_filter[7];
                // dx = 1
                xx++;
                if (xx < width) {
                    Pixel px = input[xx + yy * width];
                    r += px.r * int_filter[8]; g += px.g * int_filter[8]; b += px.b * int_filter[8];
                }
            }

            // Scale back down using bit shift and clamp the results to [0, 255]
            r = (r + (1 << (SCALE_SHIFT - 1))) >> SCALE_SHIFT;
            g = (g + (1 << (SCALE_SHIFT - 1))) >> SCALE_SHIFT;
            b = (b + (1 << (SCALE_SHIFT - 1))) >> SCALE_SHIFT;

            r = (r & ~(r >> 31)) | ((255 - r) >> 31 & 255);
            g = (g & ~(g >> 31)) | ((255 - g) >> 31 & 255);
            b = (b & ~(b >> 31)) | ((255 - b) >> 31 & 255);

            output[x + y * width] = (Pixel){(unsigned char)r, (unsigned char)g, (unsigned char)b};
        }
    }
}
