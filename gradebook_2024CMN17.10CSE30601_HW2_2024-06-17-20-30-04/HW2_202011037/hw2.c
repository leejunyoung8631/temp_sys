#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

#define FIXED_POINT_SHIFT 10
#define CACHE_LINE_SIZE 64

static Pixel convolution_fixed_point(const Pixel* input, int x, int y, int width, int height, const int32_t* filterValues) {
    int32_t r = 0, g = 0, b = 0;
    const int filterWidth = 3;

    const int startY = (y > 0) ? -1 : 0;
    const int endY = (y < height - 1) ? 1 : 0;
    const int startX = (x > 0) ? -1 : 0;
    const int endX = (x < width - 1) ? 1 : 0;

    for (int dy = startY; dy <= endY; ++dy) {
        const Pixel* rowStart = input + (y + dy) * width + x;
        for (int dx = startX; dx <= endX; ++dx) {
            const Pixel* p = rowStart + dx;
            int filterIndex = (dy + 1) * filterWidth + (dx + 1);
            r += p->r * filterValues[filterIndex];
            g += p->g * filterValues[filterIndex];
            b += p->b * filterValues[filterIndex];
        }
    }

    r >>= FIXED_POINT_SHIFT;
    g >>= FIXED_POINT_SHIFT;
    b >>= FIXED_POINT_SHIFT;

    r = (r < 0) ? 0 : (r > 255) ? 255 : r;
    g = (g < 0) ? 0 : (g > 255) ? 255 : g;
    b = (b < 0) ? 0 : (b > 255) ? 255 : b;

    return (Pixel){.r = (unsigned char)r, .g = (unsigned char)g, .b = (unsigned char)b};
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    int32_t filterValues[9];
    for (int i = 0; i < 9; i++) {
        filterValues[i] = (int)(filter[i] * (1 << FIXED_POINT_SHIFT));
    }

    const int tileSize = 64; 
    for (int ty = 0; ty < height; ty += tileSize) {
        for (int tx = 0; tx < width; tx += tileSize) {
            int tileEndY = (ty + tileSize > height) ? height : ty + tileSize;
            int tileEndX = (tx + tileSize > width) ? width : tx + tileSize;

            for (int y = ty; y < tileEndY; ++y) {
                for (int x = tx; x < tileEndX; ++x) {
                    output[x + y * width] = convolution_fixed_point(input, x, y, width, height, filterValues);
                }
            }
        }
    }
}
