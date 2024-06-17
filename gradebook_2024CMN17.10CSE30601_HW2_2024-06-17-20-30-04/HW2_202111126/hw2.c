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

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!

static Pixel convolution_middle(const Pixel* input, int x, int y, int width, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int filter_index = (0) + (0) * 3;
    int image_index = (x + -1) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (0) + (1) * 3;
    image_index = (x + -1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (0) + (2) * 3;
    image_index = (x + -1) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (1) + (0) * 3;
    image_index = (x + 0) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (1) + (1) * 3;
    image_index = (x + 0) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (1) + (2) * 3;
    image_index = (x + 0) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (2) + (0) * 3;
    image_index = (x + 1) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (2) + (1) * 3;
    image_index = (x + 1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (2) + (2) * 3;
    image_index = (x + 1) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

static Pixel convolution_left_edge(const Pixel* input, int x, int y, int width, int height, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;
    
    
    int filter_index = (1) + (0) * 3;
    int image_index = (x + 0) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (1) + (1) * 3;
    image_index = (x + 0) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (1) + (2) * 3;
    image_index = (x + 0) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (2) + (0) * 3;
    image_index = (x + 1) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (2) + (1) * 3;
    image_index = (x + 1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (2) + (2) * 3;
    image_index = (x + 1) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

static Pixel convolution_right_edge(const Pixel* input, int x, int y, int width, int height, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;
    
    int filter_index = (0) + (0) * 3;
    int image_index = (x + -1) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (0) + (1) * 3;
    image_index = (x + -1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (0) + (2) * 3;
    image_index = (x + -1) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (1) + (0) * 3;
    image_index = (x + 0) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (1) + (1) * 3;
    image_index = (x + 0) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (1) + (2) * 3;
    image_index = (x + 0) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

static Pixel convolution_upper_edge(const Pixel* input, int x, int y, int width, int height, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int filter_index = (0) + (1) * 3;
    int image_index = (x + -1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (0) + (2) * 3;
    image_index = (x + -1) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    

    filter_index = (1) + (1) * 3;
    image_index = (x + 0) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (1) + (2) * 3;
    image_index = (x + 0) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    

    filter_index = (2) + (1) * 3;
    image_index = (x + 1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (2) + (2) * 3;
    image_index = (x + 1) + (y + 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

static Pixel convolution_bottom_edge(const Pixel* input, int x, int y, int width, int height, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int filter_index = (0) + (0) * 3;
    int image_index = (x + -1) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (0) + (1) * 3;
    image_index = (x + -1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (1) + (0) * 3;
    image_index = (x + 0) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    

    filter_index = (1) + (1) * 3;
    image_index = (x + 0) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (2) + (0) * 3;
    image_index = (x + 1) + (y + -1) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];


    filter_index = (2) + (1) * 3;
    image_index = (x + 1) + (y + 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

static Pixel convolution_upper_left(const Pixel* input, int width, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int filter_index = (1) + (1) * 3;
    int image_index = (0) + (0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (1) + (2) * 3;
    image_index = (0) + (1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    

    filter_index = (2) + (1) * 3;
    image_index = (1) + ( 0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (2) + (2) * 3;
    image_index = (1) + ( 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

// 상단 우측 모서리 처리
static Pixel convolution_upper_right(const Pixel* input, int width, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int filter_index = (0) + (1) * 3;
    int image_index = (width-2) + (0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (0) + (2) * 3;
    image_index = (width-2) + (1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    

    filter_index = (1) + (1) * 3;
    image_index = (width-1) + (0) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    filter_index = (1) + (2) * 3;
    image_index = (width-1) + (1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

// 하단 좌측 모서리 처리
static Pixel convolution_bottom_left(const Pixel* input, int width, int height, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;
    
    int filter_index = (1) + (0) * 3;
    int image_index = (0) + (height-2) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (1) + (1) * 3;
    image_index = (0) + (height -1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (2) + (0) * 3;
    image_index = (1) + (height-2) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    

    filter_index = (2) + (1) * 3;
    image_index = (1) + (height -1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

// 하단 우측 모서리 처리
static Pixel convolution_bottom_right(const Pixel* input, int width, int height, const float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;

    int filter_index = (0) + (0) * 3;
    int image_index = (width - 2) + (height - 2) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (0) + (1) * 3;
    image_index = (width - 2) + (height - 1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];
    
    
    filter_index = (1) + (0) * 3;
    image_index = (width - 1) + (height-2) * width;

    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];

    filter_index = (1) + (1) * 3;
    image_index = (width - 1) + (height -1) * width;
    
    r += input[image_index].r * filter[filter_index];
    g += input[image_index].g * filter[filter_index];
    b += input[image_index].b * filter[filter_index];


    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    // 내부 영역 처리
    for (unsigned int y = 1; y < height - 1; ++y) {
        for (unsigned int x = 1; x < width - 1; ++x) {
            output[x + y * width] = convolution_middle(input, x, y, width, filter);
        }
    }

    // 좌측 가장자리 처리
    for (unsigned int y = 1; y < height - 1; ++y) {
        output[0 + y * width] = convolution_left_edge(input, 0, y, width, height, filter);
    }

    // 우측 가장자리 처리
    for (unsigned int y = 1; y < height - 1; ++y) {
        output[(width - 1) + y * width] = convolution_right_edge(input, width - 1, y, width, height, filter);
    }

    // 상단 가장자리 처리
    for (unsigned int x = 1; x < width - 1; ++x) {
        output[x] = convolution_upper_edge(input, x, 0, width, height, filter);
    }

    // 하단 가장자리 처리
    for (unsigned int x = 1; x < width - 1; ++x) {
        output[x + (height - 1) * width] = convolution_bottom_edge(input, x, height - 1, width, height, filter);
    }

    // 네 모서리 처리
    output[0] = convolution_upper_left(input, width, filter); // 좌상단 모서리
    output[width - 1] = convolution_upper_right(input, width, filter); // 우상단 모서리
    output[(height - 1) * width] = convolution_bottom_left(input, width, height, filter); // 좌하단 모서리
    output[(width - 1) + (height - 1) * width] = convolution_bottom_right(input, width, height, filter); // 우하단 모서리
}
