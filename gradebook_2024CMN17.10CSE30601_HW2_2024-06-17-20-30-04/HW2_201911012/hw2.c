// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

static Pixel convolution(const Pixel* input, int x, int y, int width, int height, const float* filter) {
    int r = 0, g = 0, b = 0;
    const float* filterPtr = filter;

    const Pixel* inputPtr = input + (y - 1) * width;
    int xx_m1 = x - 1;
    int xx_1 = x + 1;

    if (y > 0) {
        if (xx_m1 >= 0 && xx_1 < width) {
            const Pixel* p = inputPtr + xx_m1;
            r += p->r * filterPtr[0] + (p + 1)->r * filterPtr[1] + (p + 2)->r * filterPtr[2];
            g += p->g * filterPtr[0] + (p + 1)->g * filterPtr[1] + (p + 2)->g * filterPtr[2];
            b += p->b * filterPtr[0] + (p + 1)->b * filterPtr[1] + (p + 2)->b * filterPtr[2];
            filterPtr += 3;
        }
        else {
            if (xx_m1 >= 0) {
                const Pixel* p = inputPtr + xx_m1;
                r += p->r * filterPtr[0];
                g += p->g * filterPtr[0];
                b += p->b * filterPtr[0];
            }
            filterPtr++;

            const Pixel* p = inputPtr + x;
            r += p->r * filterPtr[0];
            g += p->g * filterPtr[0];
            b += p->b * filterPtr[0];
            filterPtr++;

            if (xx_1 < width) {
                const Pixel* p = inputPtr + xx_1;
                r += p->r * filterPtr[0];
                g += p->g * filterPtr[0];
                b += p->b * filterPtr[0];
            }
            filterPtr++;
        }
    }
    else {
        filterPtr += 3;
    }

    inputPtr += width;
    if (xx_m1 >= 0 && xx_1 < width) {
        const Pixel* p = inputPtr + xx_m1;
        r += p->r * filterPtr[0] + (p + 1)->r * filterPtr[1] + (p + 2)->r * filterPtr[2];
        g += p->g * filterPtr[0] + (p + 1)->g * filterPtr[1] + (p + 2)->g * filterPtr[2];
        b += p->b * filterPtr[0] + (p + 1)->b * filterPtr[1] + (p + 2)->b * filterPtr[2];
        filterPtr += 3;
    }
    else {
        if (xx_m1 >= 0) {
            const Pixel* p = inputPtr + xx_m1;
            r += p->r * filterPtr[0];
            g += p->g * filterPtr[0];
            b += p->b * filterPtr[0];
        }
        filterPtr++;

        const Pixel* p = inputPtr + x;
        r += p->r * filterPtr[0];
        g += p->g * filterPtr[0];
        b += p->b * filterPtr[0];
        filterPtr++;

        if (xx_1 < width) {
            const Pixel* p = inputPtr + xx_1;
            r += p->r * filterPtr[0];
            g += p->g * filterPtr[0];
            b += p->b * filterPtr[0];
        }
        filterPtr++;
    }

    inputPtr += width;
    if (y + 1 < height) {
        if (xx_m1 >= 0 && xx_1 < width) {
            const Pixel* p = inputPtr + xx_m1;
            r += p->r * filterPtr[0] + (p + 1)->r * filterPtr[1] + (p + 2)->r * filterPtr[2];
            g += p->g * filterPtr[0] + (p + 1)->g * filterPtr[1] + (p + 2)->g * filterPtr[2];
            b += p->b * filterPtr[0] + (p + 1)->b * filterPtr[1] + (p + 2)->b * filterPtr[2];
            filterPtr += 3;
        }
        else {
            if (xx_m1 >= 0) {
                const Pixel* p = inputPtr + xx_m1;
                r += p->r * filterPtr[0];
                g += p->g * filterPtr[0];
                b += p->b * filterPtr[0];
            }
            filterPtr++;

            const Pixel* p = inputPtr + x;
            r += p->r * filterPtr[0];
            g += p->g * filterPtr[0];
            b += p->b * filterPtr[0];
            filterPtr++;

            if (xx_1 < width) {
                const Pixel* p = inputPtr + xx_1;
                r += p->r * filterPtr[0];
                g += p->g * filterPtr[0];
                b += p->b * filterPtr[0];
            }
            filterPtr++;
        }
    }
    else {
        filterPtr += 3;
    }

    Pixel result;
    result.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    result.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    result.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
    return result;
}

void filter_optimized(void* args[]) {
    const unsigned int width = *(unsigned int*)args[0];
    const unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    const float* filter = (float*)args[4];

    for (unsigned int y = 0; y < height; ++y) {
        Pixel* outputPtr = output + y * width;
        unsigned int x = 0;
        for (; x < width - 3; x += 4) {
            *outputPtr = convolution(input, x, y, width, height, filter);
            *(outputPtr + 1) = convolution(input, x + 1, y, width, height, filter);
            *(outputPtr + 2) = convolution(input, x + 2, y, width, height, filter);
            *(outputPtr + 3) = convolution(input, x + 3, y, width, height, filter);
            outputPtr += 4;
        }
        *outputPtr = convolution(input, x, y, width, height, filter);
        *(outputPtr + 1) = convolution(input, x + 1, y, width, height, filter);
        *(outputPtr + 2) = convolution(input, x + 2, y, width, height, filter);
    }
}