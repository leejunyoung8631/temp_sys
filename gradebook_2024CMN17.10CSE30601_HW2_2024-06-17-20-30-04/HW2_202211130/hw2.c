// 최종본 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"


static inline Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int _y = y - 1, y_ = y + 1, _x = x - 1, x_ = x + 1;
    Pixel* inp;
    float* f = filter;


    inp = input + _x + _y * width;
    if (_y >= 0 && _x >= 0) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    inp++;
    if (_y >= 0) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    inp++;
    if (_y >= 0 && x_ < width) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    // inp = input + _x + y * width;
    inp = inp-2+width;
    if (_x >= 0) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    inp++;
    r += inp->r * *f;
    g += inp->g * *f;
    b += inp->b * *f;
    f++;

    inp++;
    if (x_ < width) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    // inp = input + _x + y_ * width;
    inp = inp-2+width;
    if (y_ < height && _x >= 0) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    inp++;
    if (y_ < height) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
    }
    f++;

    inp++;
    if (y_ < height && x_ < width) {
        r += inp->r * *f;
        g += inp->g * *f;
        b += inp->b * *f;
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
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    Pixel* outptr = output;
    for (int y = 0; y < height; ++y) {
        Pixel* inptr = input + y * width;
        for (int x = 0; x < width; ++x, ++outptr, ++inptr) {
            *outptr = convolution(input, x, y, width, height, filter);
        }
    }
}
