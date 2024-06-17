#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

#define FILTER_SCALE 256
#define SCALE_SHIFT 8

void convert_filter(const float* float_filter, int* int_filter, int size) {
    for (int i = 0; i < size; i++) {
        int_filter[i] = (int)(float_filter[i] * FILTER_SCALE);
    }
}

static Pixel convolution(const Pixel* input, int x, int y, int width, int height, const int* filter) {
    int r = 0, g = 0, b = 0;
    int dx, dy;

    dy = -1; dx = -1;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }
    dx = 0;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }
    dx = 1;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }

    dy = 0; dx = -1;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }
    dx = 0;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }
    dx = 1;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }

    dy = 1; dx = -1;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }
    dx = 0;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }
    dx = 1;
    if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
        int index = (y + dy) * width + (x + dx);
        int filter_value = filter[(dy + 1) * 3 + (dx + 1)];
        r += input[index].r * filter_value;
        g += input[index].g * filter_value;
        b += input[index].b * filter_value;
    }

    Pixel p;
    p.r = (unsigned char)((r >> SCALE_SHIFT) < 0 ? 0 : ((r >> SCALE_SHIFT) > 255 ? 255 : (r >> SCALE_SHIFT)));
    p.g = (unsigned char)((g >> SCALE_SHIFT) < 0 ? 0 : ((g >> SCALE_SHIFT) > 255 ? 255 : (g >> SCALE_SHIFT)));
    p.b = (unsigned char)((b >> SCALE_SHIFT) < 0 ? 0 : ((b >> SCALE_SHIFT) > 255 ? 255 : (b >> SCALE_SHIFT)));

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* float_filter = (float*)args[4];

    int int_filter[9];
    convert_filter(float_filter, int_filter, 9);

    unsigned int y;
    for (y = 0; y < height; y++) {
        unsigned int x;
        for (x = 0; x < width; x += 8) {
            Pixel temp_pixels[8];

            temp_pixels[0] = convolution(input, x, y, width, height, int_filter);
            if (x + 1 < width) temp_pixels[1] = convolution(input, x + 1, y, width, height, int_filter);
            if (x + 2 < width) temp_pixels[2] = convolution(input, x + 2, y, width, height, int_filter);
            if (x + 3 < width) temp_pixels[3] = convolution(input, x + 3, y, width, height, int_filter);
            if (x + 4 < width) temp_pixels[4] = convolution(input, x + 4, y, width, height, int_filter);
            if (x + 5 < width) temp_pixels[5] = convolution(input, x + 5, y, width, height, int_filter);
            if (x + 6 < width) temp_pixels[6] = convolution(input, x + 6, y, width, height, int_filter);
            if (x + 7 < width) temp_pixels[7] = convolution(input, x + 7, y, width, height, int_filter);

            output[x + y * width] = temp_pixels[0];
            if (x + 1 < width) output[x + 1 + y * width] = temp_pixels[1];
            if (x + 2 < width) output[x + 2 + y * width] = temp_pixels[2];
            if (x + 3 < width) output[x + 3 + y * width] = temp_pixels[3];
            if (x + 4 < width) output[x + 4 + y * width] = temp_pixels[4];
            if (x + 5 < width) output[x + 5 + y * width] = temp_pixels[5];
            if (x + 6 < width) output[x + 6 + y * width] = temp_pixels[6];
            if (x + 7 < width) output[x + 7 + y * width] = temp_pixels[7];
        }
    }
}
