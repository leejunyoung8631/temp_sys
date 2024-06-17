#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

void filter_optimized(void* args[]) {
    unsigned int width = *(int*)args[0];
    unsigned int height = *(int*)args[1];
    Pixel* restrict input = (Pixel*)args[2];
    Pixel* restrict output = (Pixel*)args[3];
    float* restrict filter = (float*)args[4];

    float f00 = filter[0], f01 = filter[1], f02 = filter[2];
    float f10 = filter[3], f11 = filter[4], f12 = filter[5];
    float f20 = filter[6], f21 = filter[7], f22 = filter[8];

    int block_size = 64;
    Pixel neighbors[9];

    for (int y_block = 0; y_block < height; y_block += block_size) {
        for (int x_block = 0; x_block < width; x_block += block_size) {
            if (x_block + block_size < width) {
                for (int y = y_block; y < y_block + block_size && y < height; ++y) {
                    __builtin_prefetch(&input[y * width + x_block + block_size], 0, 0);
                    if (y > 0) {
                        __builtin_prefetch(&input[(y - 1) * width + x_block + block_size], 0, 0);
                    }
                    if (y < height - 1) {
                        __builtin_prefetch(&input[(y + 1) * width + x_block + block_size], 0, 0);
                    }
                }
            }
            int yw = y_block * width;
            for (int y = y_block; y < y_block + block_size && y < height; ++y) {
                int y0w = (y > 0) ? (y - 1) * width : yw;
                int y2w = (y < height - 1) ? (y + 1) * width : yw;

                for (int x = x_block; x < x_block + block_size && x < width; ++x) {
                    int r = 0, g = 0, b = 0;

                    neighbors[0] = (y > 0 && x > 0) ? input[y0w + x - 1] : (Pixel){0, 0, 0};
                    neighbors[1] = (y > 0) ? input[y0w + x] : (Pixel){0, 0, 0};
                    neighbors[2] = (y > 0 && x < width - 1) ? input[y0w + x + 1] : (Pixel){0, 0, 0};

                    neighbors[3] = (x > 0) ? input[yw + x - 1] : (Pixel){0, 0, 0};
                    neighbors[4] = input[yw + x];
                    neighbors[5] = (x < width - 1) ? input[yw + x + 1] : (Pixel){0, 0, 0};

                    neighbors[6] = (y < height - 1 && x > 0) ? input[y2w + x - 1] : (Pixel){0, 0, 0};
                    neighbors[7] = (y < height - 1) ? input[y2w + x] : (Pixel){0, 0, 0};
                    neighbors[8] = (y < height - 1 && x < width - 1) ? input[y2w + x + 1] : (Pixel){0, 0, 0};

                    r = neighbors[0].r * f00 + neighbors[1].r * f01 + neighbors[2].r * f02 +
                        neighbors[3].r * f10 + neighbors[4].r * f11 + neighbors[5].r * f12 +
                        neighbors[6].r * f20 + neighbors[7].r * f21 + neighbors[8].r * f22;
                    
                    g = neighbors[0].g * f00 + neighbors[1].g * f01 + neighbors[2].g * f02 +
                        neighbors[3].g * f10 + neighbors[4].g * f11 + neighbors[5].g * f12 +
                        neighbors[6].g * f20 + neighbors[7].g * f21 + neighbors[8].g * f22;

                    b = neighbors[0].b * f00 + neighbors[1].b * f01 + neighbors[2].b * f02 +
                        neighbors[3].b * f10 + neighbors[4].b * f11 + neighbors[5].b * f12 +
                        neighbors[6].b * f20 + neighbors[7].b * f21 + neighbors[8].b * f22;

                    r = (r < 0) ? 0 : (r > 255) ? 255 : r;
                    g = (g < 0) ? 0 : (g > 255) ? 255 : g;
                    b = (b < 0) ? 0 : (b > 255) ? 255 : b;

                    output[yw + x] = (Pixel){ .r = (unsigned char)r, .g = (unsigned char)g, .b = (unsigned char)b };
                }
            yw += width;
            }
        }
    }
}

