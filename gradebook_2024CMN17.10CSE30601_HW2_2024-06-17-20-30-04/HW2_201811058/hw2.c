#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

// Inline function for convolution
static inline Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int ix = x + dx;
            int iy = y + dy;

            if (ix < 0 || ix >= width || iy < 0 || iy >= height)
                continue;

            float f = filter[(dx + 1) + (dy + 1) * 3];
            Pixel p = input[ix + iy * width];

            r += p.r * f;
            g += p.g * f;
            b += p.b * f;
        }
    }

    Pixel result;
    result.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    result.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    result.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return result;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    // Handle edges separately
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || x == width-1 || y == 0 || y == height-1) {
                output[x + y * width] = convolution(input, x, y, width, height, filter);
            }
        }
    }

    // Process inner pixels
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int idx = x + y * width;

            double r = 0, g = 0, b = 0;

            // Unrolled loop
            r += input[idx - width - 1].r * filter[0];
            r += input[idx - width].r * filter[1];
            r += input[idx - width + 1].r * filter[2];
            r += input[idx - 1].r * filter[3];
            r += input[idx].r * filter[4];
            r += input[idx + 1].r * filter[5];
            r += input[idx + width - 1].r * filter[6];
            r += input[idx + width].r * filter[7];
            r += input[idx + width + 1].r * filter[8];

            g += input[idx - width - 1].g * filter[0];
            g += input[idx - width].g * filter[1];
            g += input[idx - width + 1].g * filter[2];
            g += input[idx - 1].g * filter[3];
            g += input[idx].g * filter[4];
            g += input[idx + 1].g * filter[5];
            g += input[idx + width - 1].g * filter[6];
            g += input[idx + width].g * filter[7];
            g += input[idx + width + 1].g * filter[8];

            b += input[idx - width - 1].b * filter[0];
            b += input[idx - width].b * filter[1];
            b += input[idx - width + 1].b * filter[2];
            b += input[idx - 1].b * filter[3];
            b += input[idx].b * filter[4];
            b += input[idx + 1].b * filter[5];
            b += input[idx + width - 1].b * filter[6];
            b += input[idx + width].b * filter[7];
            b += input[idx + width + 1].b * filter[8];

            output[idx].r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            output[idx].g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            output[idx].b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
        }
    }
}

