#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

#define CLAMPING(value) ((value) > 255 ? 255 : ((value) < 0 ? 0 : (value)))

void float_to_int_filter(float* float_filter, int* int_filter, int scale) {
    for (int i = 0; i < 9; i++) {
        int_filter[i] = (int)(float_filter[i] * scale);
    }
}

static Pixel convolution(Pixel* input, int x, int y, int width, int height, int* filter) {
    int r = 0, g = 0, b = 0;

    int index_img, index_filter;

    // (-1, -1)
    index_img = (x - 1) + (y - 1) * width;
    index_filter = 0;
    if (y - 1 >= 0 && x - 1 >= 0) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (0, -1)
    index_img = x + (y - 1) * width;
    index_filter = 1;
    if (y - 1 >= 0) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (1, -1)
    index_img = (x + 1) + (y - 1) * width;
    index_filter = 2;
    if (y - 1 >= 0 && x + 1 < width) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (-1, 0)
    index_img = (x - 1) + y * width;
    index_filter = 3;
    if (x - 1 >= 0) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (0, 0)
    index_img = x + y * width;
    index_filter = 4;
    r += input[index_img].r * filter[index_filter];
    g += input[index_img].g * filter[index_filter];
    b += input[index_img].b * filter[index_filter];

    // (1, 0)
    index_img = (x + 1) + y * width;
    index_filter = 5;
    if (x + 1 < width) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (-1, 1)
    index_img = (x - 1) + (y + 1) * width;
    index_filter = 6;
    if (y + 1 < height && x - 1 >= 0) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (0, 1)
    index_img = x + (y + 1) * width;
    index_filter = 7;
    if (y + 1 < height) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    // (1, 1)
    index_img = (x + 1) + (y + 1) * width;
    index_filter = 8;
    if (y + 1 < height && x + 1 < width) {
        r += input[index_img].r * filter[index_filter];
        g += input[index_img].g * filter[index_filter];
        b += input[index_img].b * filter[index_filter];
    }

    Pixel p;
    p.r = (unsigned char)CLAMPING(r / 16);
    p.g = (unsigned char)CLAMPING(g / 16);
    p.b = (unsigned char)CLAMPING(b / 16);

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* float_filter = (float*)args[4];
    int int_filter[9];
    float_to_int_filter(float_filter, int_filter, 16);

    // 경계 처리
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                output[x + y * width] = convolution(input, x, y, width, height, int_filter);
            }
        }
    }

    // 비경계 처리
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; x += 4) { // 4개씩 처리
            if (x + 3 >= width - 1) {
                for (int i = x; i < width - 1; ++i) {
                    output[i + y * width] = convolution(input, i, y, width, height, int_filter);
                }
                break;
            }

            int r0 = 0, g0 = 0, b0 = 0;
            int r1 = 0, g1 = 0, b1 = 0;
            int r2 = 0, g2 = 0, b2 = 0;
            int r3 = 0, g3 = 0, b3 = 0;

            int center0 = x + y * width;
            int center1 = center0 + 1;
            int center2 = center0 + 2;
            int center3 = center0 + 3;

            // (-1, -1)
            int index_img = center0 - width - 1;
            r0 += input[index_img].r * int_filter[0];
            g0 += input[index_img].g * int_filter[0];
            b0 += input[index_img].b * int_filter[0];

            index_img = center1 - width - 1;
            r1 += input[index_img].r * int_filter[0];
            g1 += input[index_img].g * int_filter[0];
            b1 += input[index_img].b * int_filter[0];

            index_img = center2 - width - 1;
            r2 += input[index_img].r * int_filter[0];
            g2 += input[index_img].g * int_filter[0];
            b2 += input[index_img].b * int_filter[0];

            index_img = center3 - width - 1;
            r3 += input[index_img].r * int_filter[0];
            g3 += input[index_img].g * int_filter[0];
            b3 += input[index_img].b * int_filter[0];

            // (0, -1)
            index_img = center0 - width;
            r0 += input[index_img].r * int_filter[1];
            g0 += input[index_img].g * int_filter[1];
            b0 += input[index_img].b * int_filter[1];

            index_img = center1 - width;
            r1 += input[index_img].r * int_filter[1];
            g1 += input[index_img].g * int_filter[1];
            b1 += input[index_img].b * int_filter[1];

            index_img = center2 - width;
            r2 += input[index_img].r * int_filter[1];
            g2 += input[index_img].g * int_filter[1];
            b2 += input[index_img].b * int_filter[1];

            index_img = center3 - width;
            r3 += input[index_img].r * int_filter[1];
            g3 += input[index_img].g * int_filter[1];
            b3 += input[index_img].b * int_filter[1];

            // (1, -1)
            index_img = center0 - width + 1;
            r0 += input[index_img].r * int_filter[2];
            g0 += input[index_img].g * int_filter[2];
            b0 += input[index_img].b * int_filter[2];

            index_img = center1 - width + 1;
            r1 += input[index_img].r * int_filter[2];
            g1 += input[index_img].g * int_filter[2];
            b1 += input[index_img].b * int_filter[2];

            index_img = center2 - width + 1;
            r2 += input[index_img].r * int_filter[2];
            g2 += input[index_img].g * int_filter[2];
            b2 += input[index_img].b * int_filter[2];

            index_img = center3 - width + 1;
            r3 += input[index_img].r * int_filter[2];
            g3 += input[index_img].g * int_filter[2];
            b3 += input[index_img].b * int_filter[2];

            // (-1, 0)
            index_img = center0 - 1;
            r0 += input[index_img].r * int_filter[3];
            g0 += input[index_img].g * int_filter[3];
            b0 += input[index_img].b * int_filter[3];

            index_img = center1 - 1;
            r1 += input[index_img].r * int_filter[3];
            g1 += input[index_img].g * int_filter[3];
            b1 += input[index_img].b * int_filter[3];

            index_img = center2 - 1;
            r2 += input[index_img].r * int_filter[3];
            g2 += input[index_img].g * int_filter[3];
            b2 += input[index_img].b * int_filter[3];

            index_img = center3 - 1;
            r3 += input[index_img].r * int_filter[3];
            g3 += input[index_img].g * int_filter[3];
            b3 += input[index_img].b * int_filter[3];

            // (0, 0)
            index_img = center0;
            r0 += input[index_img].r * int_filter[4];
            g0 += input[index_img].g * int_filter[4];
            b0 += input[index_img].b * int_filter[4];

            index_img = center1;
            r1 += input[index_img].r * int_filter[4];
            g1 += input[index_img].g * int_filter[4];
            b1 += input[index_img].b * int_filter[4];

            index_img = center2;
            r2 += input[index_img].r * int_filter[4];
            g2 += input[index_img].g * int_filter[4];
            b2 += input[index_img].b * int_filter[4];

            index_img = center3;
            r3 += input[index_img].r * int_filter[4];
            g3 += input[index_img].g * int_filter[4];
            b3 += input[index_img].b * int_filter[4];

            // (1, 0)
            index_img = center0 + 1;
            r0 += input[index_img].r * int_filter[5];
            g0 += input[index_img].g * int_filter[5];
            b0 += input[index_img].b * int_filter[5];

            index_img = center1 + 1;
            r1 += input[index_img].r * int_filter[5];
            g1 += input[index_img].g * int_filter[5];
            b1 += input[index_img].b * int_filter[5];

            index_img = center2 + 1;
            r2 += input[index_img].r * int_filter[5];
            g2 += input[index_img].g * int_filter[5];
            b2 += input[index_img].b * int_filter[5];

            index_img = center3 + 1;
            r3 += input[index_img].r * int_filter[5];
            g3 += input[index_img].g * int_filter[5];
            b3 += input[index_img].b * int_filter[5];

            // (-1, 1)
            index_img = center0 + width - 1;
            r0 += input[index_img].r * int_filter[6];
            g0 += input[index_img].g * int_filter[6];
            b0 += input[index_img].b * int_filter[6];

            index_img = center1 + width - 1;
            r1 += input[index_img].r * int_filter[6];
            g1 += input[index_img].g * int_filter[6];
            b1 += input[index_img].b * int_filter[6];

            index_img = center2 + width - 1;
            r2 += input[index_img].r * int_filter[6];
            g2 += input[index_img].g * int_filter[6];
            b2 += input[index_img].b * int_filter[6];

            index_img = center3 + width - 1;
            r3 += input[index_img].r * int_filter[6];
            g3 += input[index_img].g * int_filter[6];
            b3 += input[index_img].b * int_filter[6];

            // (0, 1)
            index_img = center0 + width;
            r0 += input[index_img].r * int_filter[7];
            g0 += input[index_img].g * int_filter[7];
            b0 += input[index_img].b * int_filter[7];

            index_img = center1 + width;
            r1 += input[index_img].r * int_filter[7];
            g1 += input[index_img].g * int_filter[7];
            b1 += input[index_img].b * int_filter[7];

            index_img = center2 + width;
            r2 += input[index_img].r * int_filter[7];
            g2 += input[index_img].g * int_filter[7];
            b2 += input[index_img].b * int_filter[7];

            index_img = center3 + width;
            r3 += input[index_img].r * int_filter[7];
            g3 += input[index_img].g * int_filter[7];
            b3 += input[index_img].b * int_filter[7];

            // (1, 1)
            index_img = center0 + width + 1;
            r0 += input[index_img].r * int_filter[8];
            g0 += input[index_img].g * int_filter[8];
            b0 += input[index_img].b * int_filter[8];

            index_img = center1 + width + 1;
            r1 += input[index_img].r * int_filter[8];
            g1 += input[index_img].g * int_filter[8];
            b1 += input[index_img].b * int_filter[8];

            index_img = center2 + width + 1;
            r2 += input[index_img].r * int_filter[8];
            g2 += input[index_img].g * int_filter[8];
            b2 += input[index_img].b * int_filter[8];

            index_img = center3 + width + 1;
            r3 += input[index_img].r * int_filter[8];
            g3 += input[index_img].g * int_filter[8];
            b3 += input[index_img].b * int_filter[8];

            // 결과 저장
            Pixel p0, p1, p2, p3;
            p0.r = (unsigned char)CLAMPING(r0 / 16);
            p0.g = (unsigned char)CLAMPING(g0 / 16);
            p0.b = (unsigned char)CLAMPING(b0 / 16);
            output[center0] = p0;

            p1.r = (unsigned char)CLAMPING(r1 / 16);
            p1.g = (unsigned char)CLAMPING(g1 / 16);
            p1.b = (unsigned char)CLAMPING(b1 / 16);
            output[center1] = p1;

            p2.r = (unsigned char)CLAMPING(r2 / 16);
            p2.g = (unsigned char)CLAMPING(g2 / 16);
            p2.b = (unsigned char)CLAMPING(b2 / 16);
            output[center2] = p2;

            p3.r = (unsigned char)CLAMPING(r3 / 16);
            p3.g = (unsigned char)CLAMPING(g3 / 16);
            p3.b = (unsigned char)CLAMPING(b3 / 16);
            output[center3] = p3;
        }
    }
}
