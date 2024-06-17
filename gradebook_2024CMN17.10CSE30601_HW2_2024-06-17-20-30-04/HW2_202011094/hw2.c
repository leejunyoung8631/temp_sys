#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bmplib.h"
#include "hw2.h"

#define TILE_SIZE 32
#define FILTER_SCALE 128
#define CLIP(x) (unsigned char)(((x) > 255) ? 255 : (((x) < 0) ? 0 : (x)))

static int16_t scaled_filter[9];

static void init_filter(float* filter) {
    for(int i = 0; i < 9; i++) {
        scaled_filter[i] = (int16_t)(filter[i] * FILTER_SCALE + (filter[i] >= 0 ? 0.5 : -0.5));
    }
}

static Pixel pixel_convolution(const Pixel* input, int x, int y, int width, int height) {
    int32_t r = 0, g = 0, b = 0;
    const Pixel *p;

    #define CONV(dx, dy, f) \
        if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) { \
            p = &input[(x + dx) + (y + dy) * width]; \
            r += p->r * scaled_filter[f]; \
            g += p->g * scaled_filter[f]; \
            b += p->b * scaled_filter[f]; \
        }

    CONV(-1, -1, 0); CONV(0, -1, 1); CONV(1, -1, 2);
    CONV(-1,  0, 3); CONV(0,  0, 4); CONV(1,  0, 5);
    CONV(-1,  1, 6); CONV(0,  1, 7); CONV(1,  1, 8);

    #undef CONV

    Pixel output;
    output.r = CLIP(r / FILTER_SCALE);
    output.g = CLIP(g / FILTER_SCALE);
    output.b = CLIP(b / FILTER_SCALE);

    return output;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    const Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    init_filter(filter);

    // Process all pixels (including boundaries)
    for(int y = 0; y < height; y += TILE_SIZE) {
        for(int x = 0; x < width; x += TILE_SIZE) {
            int end_x = (x + TILE_SIZE < width) ? x + TILE_SIZE : width;
            int end_y = (y + TILE_SIZE < height) ? y + TILE_SIZE : height;
            for(int ty = y; ty < end_y; ty++) {
                for(int tx = x; tx < end_x; tx += 4) {
                    output[tx + ty * width] = pixel_convolution(input, tx, ty, width, height);
                    if (tx + 1 < end_x) output[tx + 1 + ty * width] = pixel_convolution(input, tx + 1, ty, width, height);
                    if (tx + 2 < end_x) output[tx + 2 + ty * width] = pixel_convolution(input, tx + 2, ty, width, height);
                    if (tx + 3 < end_x) output[tx + 3 + ty * width] = pixel_convolution(input, tx + 3, ty, width, height);
                }
            }
        }
    }
}
