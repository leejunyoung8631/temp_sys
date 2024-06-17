#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

#define BLOCK_SIZE 32

static Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0, g = 0, b = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int ix = x + dx;
            int iy = y + dy;
            if (ix < 0 || ix >= width || iy < 0 || iy >= height)
                continue;

            Pixel* p = &input[iy * width + ix];
            float f = filter[(dy + 1) * 3 + (dx + 1)];
            r += p->r * f;
            g += p->g * f;
            b += p->b * f;
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
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int by = 0; by < height; by += BLOCK_SIZE) {
        for (int bx = 0; bx < width; bx += BLOCK_SIZE) {
            for (int y = by; y < by + BLOCK_SIZE && y < height; ++y) {
                for (int x = bx; x < bx + BLOCK_SIZE && x < width; ++x) {
                    output[y * width + x] = convolution(input, x, y, width, height, filter);
                }
            }
        }
    }
}
