#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

#define BLOCK_SIZE 32
#define FILTER_SIZE 3

static void convolution(const Pixel* input, Pixel* output, unsigned int width, unsigned int height, const float* filter, int start_x, int start_y, int end_x, int end_y) {
    for (int y = start_y; y < end_y; ++y) {
        for (int x = start_x; x < end_x; ++x) {
            float r = 0.0f, g = 0.0f, b = 0.0f;

            int y_min = (y - 1) < 0 ? 0 : (y - 1);
            int y_max = (y + 1) >= height ? height - 1 : (y + 1);
            int x_min = (x - 1) < 0 ? 0 : (x - 1);
            int x_max = (x + 1) >= width ? width - 1 : (x + 1);

            for (int dy = y_min; dy <= y_max; ++dy) {
                int filter_index_y = (dy - y + 1) * FILTER_SIZE;
                int base_index = dy * width;

                for (int dx = x_min; dx <= x_max; dx += 4) {
                    int filter_index1 = filter_index_y + (dx - x + 1);
                    int pixel_index1 = base_index + dx;
                    r += input[pixel_index1].r * filter[filter_index1];
                    g += input[pixel_index1].g * filter[filter_index1];
                    b += input[pixel_index1].b * filter[filter_index1];

                    if (dx + 1 <= x_max) {
                        int filter_index2 = filter_index_y + (dx + 1 - x + 1);
                        int pixel_index2 = base_index + dx + 1;
                        r += input[pixel_index2].r * filter[filter_index2];
                        g += input[pixel_index2].g * filter[filter_index2];
                        b += input[pixel_index2].b * filter[filter_index2];
                    }

                    if (dx + 2 <= x_max) {
                        int filter_index3 = filter_index_y + (dx + 2 - x + 1);
                        int pixel_index3 = base_index + dx + 2;
                        r += input[pixel_index3].r * filter[filter_index3];
                        g += input[pixel_index3].g * filter[filter_index3];
                        b += input[pixel_index3].b * filter[filter_index3];
                    }

                    if (dx + 3 <= x_max) {
                        int filter_index4 = filter_index_y + (dx + 3 - x + 1);
                        int pixel_index4 = base_index + dx + 3;
                        r += input[pixel_index4].r * filter[filter_index4];
                        g += input[pixel_index4].g * filter[filter_index4];
                        b += input[pixel_index4].b * filter[filter_index4];
                    }
                }
            }

            Pixel p;
            p.r = (unsigned char)((r < 0.0f) ? 0 : ((r > 255.0f) ? 255 : r));
            p.g = (unsigned char)((g < 0.0f) ? 0 : ((g > 255.0f) ? 255 : g));
            p.b = (unsigned char)((b < 0.0f) ? 0 : ((b > 255.0f) ? 255 : b));

            output[y * width + x] = p;
        }
    }
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    for (int y = 0; y < height; y += BLOCK_SIZE) {
        for (int x = 0; x < width; x += BLOCK_SIZE) {
            int end_x = (x + BLOCK_SIZE) > width ? width : (x + BLOCK_SIZE);
            int end_y = (y + BLOCK_SIZE) > height ? height : (y + BLOCK_SIZE);
            convolution(input, output, width, height, filter, x, y, end_x, end_y);
        }
    }
}
