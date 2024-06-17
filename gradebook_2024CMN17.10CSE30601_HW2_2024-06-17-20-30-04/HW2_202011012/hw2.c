#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

static Pixel optimized_convolution_with_boundary(Pixel* input, int x, int y, int width, int height, float* filter) {
    double colors[3] = {0, 0, 0}; 

    int dx, dy, nx, ny;
    Pixel* p;
    float filter_value;

    // (-1, -1)
    nx = x - 1; ny = y - 1;
    if (nx >= 0 && ny >= 0) {
        p = &input[nx + ny * width];
        filter_value = filter[0];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (0, -1)
    nx = x; ny = y - 1;
    if (ny >= 0) {
        p = &input[nx + ny * width];
        filter_value = filter[1];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (1, -1)
    nx = x + 1; ny = y - 1;
    if (nx < width && ny >= 0) {
        p = &input[nx + ny * width];
        filter_value = filter[2];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (-1, 0)
    nx = x - 1; ny = y;
    if (nx >= 0) {
        p = &input[nx + ny * width];
        filter_value = filter[3];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (0, 0)
    nx = x; ny = y;
    p = &input[nx + ny * width];
    filter_value = filter[4];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (1, 0)
    nx = x + 1; ny = y;
    if (nx < width) {
        p = &input[nx + ny * width];
        filter_value = filter[5];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (-1, 1)
    nx = x - 1; ny = y + 1;
    if (nx >= 0 && ny < height) {
        p = &input[nx + ny * width];
        filter_value = filter[6];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (0, 1)
    nx = x; ny = y + 1;
    if (ny < height) {
        p = &input[nx + ny * width];
        filter_value = filter[7];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    // (1, 1)
    nx = x + 1; ny = y + 1;
    if (nx < width && ny < height) {
        p = &input[nx + ny * width];
        filter_value = filter[8];
        colors[0] += p->r * filter_value;
        colors[1] += p->g * filter_value;
        colors[2] += p->b * filter_value;
    }

    Pixel result;
    result.r = (unsigned char)(colors[0] < 0 ? 0 : (colors[0] > 255 ? 255 : colors[0]));
    result.g = (unsigned char)(colors[1] < 0 ? 0 : (colors[1] > 255 ? 255 : colors[1]));
    result.b = (unsigned char)(colors[2] < 0 ? 0 : (colors[2] > 255 ? 255 : colors[2]));

    return result;
}

static Pixel optimized_convolution_no_boundary(Pixel* input, int x, int y, int width, int height, float* filter) {
    double colors[3] = {0, 0, 0}; 

    Pixel* p;
    float filter_value;

    // (-1, -1)
    p = &input[(x - 1) + (y - 1) * width];
    filter_value = filter[0];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (0, -1)
    p = &input[x + (y - 1) * width];
    filter_value = filter[1];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (1, -1)
    p = &input[(x + 1) + (y - 1) * width];
    filter_value = filter[2];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (-1, 0)
    p = &input[(x - 1) + y * width];
    filter_value = filter[3];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (0, 0)
    p = &input[x + y * width];
    filter_value = filter[4];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (1, 0)
    p = &input[(x + 1) + y * width];
    filter_value = filter[5];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (-1, 1)
    p = &input[(x - 1) + (y + 1) * width];
    filter_value = filter[6];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (0, 1)
    p = &input[x + (y + 1) * width];
    filter_value = filter[7];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    // (1, 1)
    p = &input[(x + 1) + (y + 1) * width];
    filter_value = filter[8];
    colors[0] += p->r * filter_value;
    colors[1] += p->g * filter_value;
    colors[2] += p->b * filter_value;

    Pixel result;
    result.r = (unsigned char)(colors[0] < 0 ? 0 : (colors[0] > 255 ? 255 : colors[0]));
    result.g = (unsigned char)(colors[1] < 0 ? 0 : (colors[1] > 255 ? 255 : colors[1]));
    result.b = (unsigned char)(colors[2] < 0 ? 0 : (colors[2] > 255 ? 255 : colors[2]));

    return result;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    // (y = 0)
    for (int x = 0; x < width; ++x) {
        output[x] = optimized_convolution_with_boundary(input, x, 0, width, height, filter);
    }

    // (y = height - 1)
    for (int x = 0; x < width; ++x) {
        output[x + (height - 1) * width] = optimized_convolution_with_boundary(input, x, height - 1, width, height, filter);
    }

    // (x = 0)
    for (int y = 1; y < height - 1; ++y) {
        output[y * width] = optimized_convolution_with_boundary(input, 0, y, width, height, filter);
    }

    // (x = width - 1)
    for (int y = 1; y < height - 1; ++y) {
        output[(width - 1) + y * width] = optimized_convolution_with_boundary(input, width - 1, y, width, height, filter);
    }

    // inner pixel
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            output[x + y * width] = optimized_convolution_no_boundary(input, x, y, width, height, filter);
        }
    }
}