#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

// 최적화된 convolution 함수
static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        int yy = y + dy;
        if (yy < 0 || yy >= height) continue;
        for (int dx = -1; dx <= 1; ++dx) {
            int xx = x + dx;
            if (xx < 0 || xx >= width) continue;

            int idx = xx + yy * width;
            int fidx = (dx + 1) + (dy + 1) * 3;

            r += input[idx].r * filter[fidx];
            g += input[idx].g * filter[fidx];
            b += input[idx].b * filter[fidx];
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

// 경계 처리 없는 convolution 함수
static Pixel convolution_no_boundaries(
        Pixel* input, int x, int y, int width, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        int yy = y + dy;
        for (int dx = -1; dx <= 1; ++dx) {
            int xx = x + dx;

            int idx = xx + yy * width;
            int fidx = (dx + 1) + (dy + 1) * 3;

            r += input[idx].r * filter[fidx];
            g += input[idx].g * filter[fidx];
            b += input[idx].b * filter[fidx];
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
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

    // 내부 영역 (경계가 아닌 부분) 처리
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            output[x + y * width] = convolution_no_boundaries(input, x, y, width, filter);
        }
    }

    // 상단 경계 처리
    for (int x = 0; x < width; ++x) {
        output[x] = convolution(input, x, 0, width, height, filter);
    }

    // 하단 경계 처리
    for (int x = 0; x < width; ++x) {
        output[x + (height - 1) * width] = convolution(input, x, height - 1, width, height, filter);
    }

    // 좌측 경계 처리
    for (int y = 0; y < height; ++y) {
        output[y * width] = convolution(input, 0, y, width, height, filter);
    }

    // 우측 경계 처리
    for (int y = 0; y < height; ++y) {
        output[(width - 1) + y * width] = convolution(input, width - 1, y, width, height, filter);
    }
}
