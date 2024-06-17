#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

// Define max & min macros
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

// Helper function to convert float filter -> int filter
void convert_filter(float* float_filter, int* int_filter, int size) {
    for (int i = 0; i < size; ++i) {
        int_filter[i] = (int)(float_filter[i] * 256); // Scale float -> int
    }
}

// Clamp function for int values
static inline int clamp(int val) {
    return (val < 0) ? 0 : (val > 255) ? 255 : val;
}

// Convolution function using int filter
static inline Pixel convolution(Pixel *input, int x, int y, int width, int height, int *filter) {
    int r = 0, g = 0, b = 0;
    int idx;

    // Unrolling the loop for the 3x3 filter directly
    if (x > 0 && y > 0) {
        idx = (x - 1) + (y - 1) * width;
        r += input[idx].r * filter[0];
        g += input[idx].g * filter[0];
        b += input[idx].b * filter[0];
    }
    if (y > 0) {
        idx = x + (y - 1) * width;
        r += input[idx].r * filter[1];
        g += input[idx].g * filter[1];
        b += input[idx].b * filter[1];
    }
    if (x < width - 1 && y > 0) {
        idx = (x + 1) + (y - 1) * width;
        r += input[idx].r * filter[2];
        g += input[idx].g * filter[2];
        b += input[idx].b * filter[2];
    }
    if (x > 0) {
        idx = (x - 1) + y * width;
        r += input[idx].r * filter[3];
        g += input[idx].g * filter[3];
        b += input[idx].b * filter[3];
    }

    // Center pixel
    idx = x + y * width;
    r += input[idx].r * filter[4];
    g += input[idx].g * filter[4];
    b += input[idx].b * filter[4];

    if (x < width - 1) {
        idx = (x + 1) + y * width;
        r += input[idx].r * filter[5];
        g += input[idx].g * filter[5];
        b += input[idx].b * filter[5];
    }
    if (x > 0 && y < height - 1) {
        idx = (x - 1) + (y + 1) * width;
        r += input[idx].r * filter[6];
        g += input[idx].g * filter[6];
        b += input[idx].b * filter[6];
    }
    if (y < height - 1) {
        idx = x + (y + 1) * width;
        r += input[idx].r * filter[7];
        g += input[idx].g * filter[7];
        b += input[idx].b * filter[7];
    }
    if (x < width - 1 && y < height - 1) {
        idx = (x + 1) + (y + 1) * width;
        r += input[idx].r * filter[8];
        g += input[idx].g * filter[8];
        b += input[idx].b * filter[8];
    }

    Pixel p = {
        .r = clamp(r / 256), // Adjust back to 0-255 range
        .g = clamp(g / 256),
        .b = clamp(b / 256)
    };

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* float_filter = args[4];

    // Convert float filter -> int filter
    int int_filter[9];
    convert_filter(float_filter, int_filter, 9);

    // Apply the convolution with the int filter
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            output[y * width + x] = convolution(input, x, y, width, height, int_filter);
        }
    }
}
