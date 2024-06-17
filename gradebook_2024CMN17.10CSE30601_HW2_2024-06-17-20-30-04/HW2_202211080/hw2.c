#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

static Pixel convolution(
    Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    int nx = x - 1;
    int ny = y - 1;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[0];
        g += input[index].g * filter[0];
        b += input[index].b * filter[0];
    }

    ny = y;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[3];
        g += input[index].g * filter[3];
        b += input[index].b * filter[3];
    }

    ny = y + 1;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[6];
        g += input[index].g * filter[6];
        b += input[index].b * filter[6];
    }

    nx = x;
    ny = y - 1;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[1];
        g += input[index].g * filter[1];
        b += input[index].b * filter[1];
    }

    ny = y;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[4];
        g += input[index].g * filter[4];
        b += input[index].b * filter[4];
    }

    ny = y + 1;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[7];
        g += input[index].g * filter[7];
        b += input[index].b * filter[7];
    }

    nx = x + 1;
    ny = y - 1;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[2];
        g += input[index].g * filter[2];
        b += input[index].b * filter[2];
    }

    ny = y;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[5];
        g += input[index].g * filter[5];
        b += input[index].b * filter[5];
    }

    ny = y + 1;
    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        int index = nx + ny * width;
        r += input[index].r * filter[8];
        g += input[index].g * filter[8];
        b += input[index].b * filter[8];
    }

    r = r < 0 ? 0 : (r > 255 ? 255 : r);
    g = g < 0 ? 0 : (g > 255 ? 255 : g);
    b = b < 0 ? 0 : (b > 255 ? 255 : b);

    Pixel p;
    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (unsigned int y = 0; y < height; ++y) {
        int yw = y * width;
        for (unsigned int x = 0; x < width; ++x) {
            output[x + yw] = convolution(input, x, y, width, height, filter);
        }
    }
}