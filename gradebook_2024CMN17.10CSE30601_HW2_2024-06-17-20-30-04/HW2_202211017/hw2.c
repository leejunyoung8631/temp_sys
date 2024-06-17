// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bmplib.h"
#include "hw2.h"

#define FILTER_SCALE 256  // 필터 값을 정수로 변환하기 위한 스케일
#define SCALE_SHIFT 8     // 256은 2의 8승이므로, 시프트 연산으로 나눗셈을 대체

// 필터 변환 함수
void convert_filter(const float* float_filter, int* int_filter, int size) {
    for (int i = 0; i < size; i++) {
        int_filter[i] = (int)(float_filter[i] * FILTER_SCALE); // 최적화 방법 : int 연산 사용
    }
}

// Optimized convolution function with loop unrolling and reassociation
static Pixel convolution(const Pixel* input, int x, int y, int width, int height, const int* filter) {
    int r = 0, g = 0, b = 0;

    // Precompute row and column indices to avoid repeated calculations
    int row_indices[3] = { (y - 1) * width, y * width, (y + 1) * width }; // 최적화 방법 : Memory Aliasing 고려
    int col_indices[3] = { x - 1, x, x + 1 }; // 최적화 방법 : Memory Aliasing 고려

    // Unroll the loops for 3x3 filter
    for (int dy = 0; dy < 3; dy++) {
        int row_index = row_indices[dy];
        if (row_index < 0 || row_index >= height * width) continue; // Skip out of boundary rows

        for (int dx = 0; dx < 3; dx++) {
            int col_index = col_indices[dx];
            if (col_index < 0 || col_index >= width) continue; // Skip out of boundary columns

            int index = row_index + col_index;
            int filter_value = filter[dy * 3 + dx];

            r += input[index].r * filter_value;
            g += input[index].g * filter_value;
            b += input[index].b * filter_value;
        }
    }

    Pixel p;
    p.r = (unsigned char)((r >> SCALE_SHIFT) < 0 ? 0 : ((r >> SCALE_SHIFT) > 255 ? 255 : (r >> SCALE_SHIFT))); // 최적화 방법 : 시프트 연산 사용
    p.g = (unsigned char)((g >> SCALE_SHIFT) < 0 ? 0 : ((g >> SCALE_SHIFT) > 255 ? 255 : (g >> SCALE_SHIFT))); // 최적화 방법 : 시프트 연산 사용
    p.b = (unsigned char)((b >> SCALE_SHIFT) < 0 ? 0 : ((b >> SCALE_SHIFT) > 255 ? 255 : (b >> SCALE_SHIFT))); // 최적화 방법 : 시프트 연산 사용

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* float_filter = (float*)args[4];

    // Convert the float filter to int filter
    int int_filter[9];
    convert_filter(float_filter, int_filter, 9);

    // Precompute boundary conditions
    unsigned int width_limit = width - 1;
    unsigned int height_limit = height - 1;

    // Apply the filter with loop unrolling and instruction-level parallelism
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x += 4) { // 최적화 방법 : 함수 호출 최적화, loop unrolling
            Pixel p1 = convolution(input, x, y, width, height, int_filter);
            output[x + y * width] = p1;

            if (x + 1 < width) {
                Pixel p2 = convolution(input, x + 1, y, width, height, int_filter);
                output[x + 1 + y * width] = p2;
            }

            if (x + 2 < width) {
                Pixel p3 = convolution(input, x + 2, y, width, height, int_filter);
                output[x + 2 + y * width] = p3;
            }

            if (x + 3 < width) {
                Pixel p4 = convolution(input, x + 3, y, width, height, int_filter);
                output[x + 3 + y * width] = p4;
            }
        }
    }
}
