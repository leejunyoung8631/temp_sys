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

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    const int filter_dx[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    const int filter_dy[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

    // 필터 값을 정수로 변환하여 미리 저장
    int filter_int[9];
    filter_int[0] = (int)(filter[0]) << 8;
    filter_int[1] = (int)(filter[1]) << 8;
    filter_int[2] = (int)(filter[2]) << 8;
    filter_int[3] = (int)(filter[3]) << 8;
    filter_int[4] = (int)(filter[4]) << 8;
    filter_int[5] = (int)(filter[5]) << 8;
    filter_int[6] = (int)(filter[6]) << 8;
    filter_int[7] = (int)(filter[7]) << 8;
    filter_int[8] = (int)(filter[8]) << 8;

    int filter_sum = filter_int[0] + filter_int[1] + filter_int[2] +
                     filter_int[3] + filter_int[4] + filter_int[5] +
                     filter_int[6] + filter_int[7] + filter_int[8];

    if (filter_sum == 0) filter_sum = 1;  // 필터 합이 0이면 1로 설정하여 나눗셈을 피함

    unsigned int total_pixels = width * height;

    unsigned int x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
    x0 = y0 = x1 = y1 = x2 = y2 = x3 = y3 = x4 = y4 = x5 = y5 = x6 = y6 = 0;

    for (unsigned int i = 0; i < total_pixels; i += 7) {
        int r0 = 0, g0 = 0, b0 = 0;
        int r1 = 0, g1 = 0, b1 = 0;
        int r2 = 0, g2 = 0, b2 = 0;
        int r3 = 0, g3 = 0, b3 = 0;
        int r4 = 0, g4 = 0, b4 = 0;
        int r5 = 0, g5 = 0, b5 = 0;
        int r6 = 0, g6 = 0, b6 = 0;

        x0 = i % width;
        y0 = i / width;   
        x1 = (i + 1) % width;
        y1 = (i + 1) / width;
        x2 = (i + 2) % width;
        y2 = (i + 2) / width;
        x3 = (i + 3) % width;
        y3 = (i + 3) / width;
        x4 = (i + 4) % width;
        y4 = (i + 4) / width;
        x5 = (i + 5) % width;
        y5 = (i + 5) / width;
        x6 = (i + 6) % width;
        y6 = (i + 6) / width;

        for (int j = 0; j < 9; j += 3) {
            int ix0 = x0 + filter_dx[j];
            int iy0 = y0 + filter_dy[j];
            int ix1 = x0 + filter_dx[j + 1];
            int iy1 = y0 + filter_dy[j + 1];
            int ix2 = x0 + filter_dx[j + 2];
            int iy2 = y0 + filter_dy[j + 2];

            int ix3 = x1 + filter_dx[j];
            int iy3 = y1 + filter_dy[j];
            int ix4 = x1 + filter_dx[j + 1];
            int iy4 = y1 + filter_dy[j + 1];
            int ix5 = x1 + filter_dx[j + 2];
            int iy5 = y1 + filter_dy[j + 2];

            int ix6 = x2 + filter_dx[j];
            int iy6 = y2 + filter_dy[j];
            int ix7 = x2 + filter_dx[j + 1];
            int iy7 = y2 + filter_dy[j + 1];
            int ix8 = x2 + filter_dx[j + 2];
            int iy8 = y2 + filter_dy[j + 2];

            int ix9 = x3 + filter_dx[j];
            int iy9 = y3 + filter_dy[j];
            int ix10 = x3 + filter_dx[j + 1];
            int iy10 = y3 + filter_dy[j + 1];
            int ix11 = x3 + filter_dx[j + 2];
            int iy11 = y3 + filter_dy[j + 2];

            int ix12 = x4 + filter_dx[j];
            int iy12 = y4 + filter_dy[j];
            int ix13 = x4 + filter_dx[j + 1];
            int iy13 = y4 + filter_dy[j + 1];
            int ix14 = x4 + filter_dx[j + 2];
            int iy14 = y4 + filter_dy[j + 2];

            int ix15 = x5 + filter_dx[j];
            int iy15 = y5 + filter_dy[j];
            int ix16 = x5 + filter_dx[j + 1];
            int iy16 = y5 + filter_dy[j + 1];
            int ix17 = x5 + filter_dx[j + 2];
            int iy17 = y5 + filter_dy[j + 2];

            int ix18 = x6 + filter_dx[j];
            int iy18 = y6 + filter_dy[j];
            int ix19 = x6 + filter_dx[j + 1];
            int iy19 = y6 + filter_dy[j + 1];
            int ix20 = x6 + filter_dx[j + 2];
            int iy20 = y6 + filter_dy[j + 2];

            if (ix0 >= 0 && ix0 < width && iy0 >= 0 && iy0 < height) {
                Pixel p = input[ix0 + iy0 * width];
                int f = filter_int[j];
                r0 += p.r * f;
                g0 += p.g * f;
                b0 += p.b * f;
            }

            if (ix1 >= 0 && ix1 < width && iy1 >= 0 && iy1 < height) {
                Pixel p = input[ix1 + iy1 * width];
                int f = filter_int[j + 1];
                r0 += p.r * f;
                g0 += p.g * f;
                b0 += p.b * f;
            }

            if (ix2 >= 0 && ix2 < width && iy2 >= 0 && iy2 < height) {
                Pixel p = input[ix2 + iy2 * width];
                int f = filter_int[j + 2];
                r0 += p.r * f;
                g0 += p.g * f;
                b0 += p.b * f;
            }

            if (ix3 >= 0 && ix3 < width && iy3 >= 0 && iy3 < height) {
                Pixel p = input[ix3 + iy3 * width];
                int f = filter_int[j];
                r1 += p.r * f;
                g1 += p.g * f;
                b1 += p.b * f;
            }

            if (ix4 >= 0 && ix4 < width && iy4 >= 0 && iy4 < height) {
                Pixel p = input[ix4 + iy4 * width];
                int f = filter_int[j + 1];
                r1 += p.r * f;
                g1 += p.g * f;
                b1 += p.b * f;
            }

            if (ix5 >= 0 && ix5 < width && iy5 >= 0 && iy5 < height) {
                Pixel p = input[ix5 + iy5 * width];
                int f = filter_int[j + 2];
                r1 += p.r * f;
                g1 += p.g * f;
                b1 += p.b * f;
            }

            if (ix6 >= 0 && ix6 < width && iy6 >= 0 && iy6 < height) {
                Pixel p = input[ix6 + iy6 * width];
                int f = filter_int[j];
                r2 += p.r * f;
                g2 += p.g * f;
                b2 += p.b * f;
            }

            if (ix7 >= 0 && ix7 < width && iy7 >= 0 && iy7 < height) {
                Pixel p = input[ix7 + iy7 * width];
                int f = filter_int[j + 1];
                r2 += p.r * f;
                g2 += p.g * f;
                b2 += p.b * f;
            }

            if (ix8 >= 0 && ix8 < width && iy8 >= 0 && iy8 < height) {
                Pixel p = input[ix8 + iy8 * width];
                int f = filter_int[j + 2];
                r2 += p.r * f;
                g2 += p.g * f;
                b2 += p.b * f;
            }

            if (ix9 >= 0 && ix9 < width && iy9 >= 0 && iy9 < height) {
                Pixel p = input[ix9 + iy9 * width];
                int f = filter_int[j];
                r3 += p.r * f;
                g3 += p.g * f;
                b3 += p.b * f;
            }

            if (ix10 >= 0 && ix10 < width && iy10 >= 0 && iy10 < height) {
                Pixel p = input[ix10 + iy10 * width];
                int f = filter_int[j + 1];
                r3 += p.r * f;
                g3 += p.g * f;
                b3 += p.b * f;
            }

            if (ix11 >= 0 && ix11 < width && iy11 >= 0 && iy11 < height) {
                Pixel p = input[ix11 + iy11 * width];
                int f = filter_int[j + 2];
                r3 += p.r * f;
                g3 += p.g * f;
                b3 += p.b * f;
            }

            if (ix12 >= 0 && ix12 < width && iy12 >= 0 && iy12 < height) {
                Pixel p = input[ix12 + iy12 * width];
                int f = filter_int[j];
                r4 += p.r * f;
                g4 += p.g * f;
                b4 += p.b * f;
            }
            if (ix13 >= 0 && ix13 < width && iy13 >= 0 && iy13 < height) {
                Pixel p = input[ix13 + iy13 * width];
                int f = filter_int[j + 1];
                r4 += p.r * f;
                g4 += p.g * f;
                b4 += p.b * f;
            }
            if (ix14 >= 0 && ix14 < width && iy14 >= 0 && iy14 < height) {
                Pixel p = input[ix14 + iy14 * width];
                int f = filter_int[j + 2];
                r4 += p.r * f;
                g4 += p.g * f;
                b4 += p.b * f;
            }

            if (ix15 >= 0 && ix15 < width && iy15 >= 0 && iy15 < height) {
                Pixel p = input[ix15 + iy15 * width];
                int f = filter_int[j];
                r5 += p.r * f;
                g5 += p.g * f;
                b5 += p.b * f;
            }
            if (ix16 >= 0 && ix16 < width && iy16 >= 0 && iy16 < height) {
                Pixel p = input[ix16 + iy16 * width];
                int f = filter_int[j + 1];
                r5 += p.r * f;
                g5 += p.g * f;
                b5 += p.b * f;
            }
            if (ix17 >= 0 && ix17 < width && iy17 >= 0 && iy17 < height) {
                Pixel p = input[ix17 + iy17 * width];
                int f = filter_int[j + 2];
                r5 += p.r * f;
                g5 += p.g * f;
                b5 += p.b * f;
            }

            if (ix18 >= 0 && ix18 < width && iy18 >= 0 && iy18 < height) {
                Pixel p = input[ix18 + iy18 * width];
                int f = filter_int[j];
                r6 += p.r * f;
                g6 += p.g * f;
                b6 += p.b * f;
            }
            if (ix19 >= 0 && ix19 < width && iy19 >= 0 && iy19 < height) {
                Pixel p = input[ix19 + iy19 * width];
                int f = filter_int[j + 1];
                r6 += p.r * f;
                g6 += p.g * f;
                b6 += p.b * f;
            }
            if (ix20 >= 0 && ix20 < width && iy20 >= 0 && iy20 < height) {
                Pixel p = input[ix20 + iy20 * width];
                int f = filter_int[j + 2];
                r6 += p.r * f;
                g6 += p.g * f;
                b6 += p.b * f;
            }
        }

        if (i < total_pixels) {
            r0 = (r0 / filter_sum)>>8;
            g0 = (g0 / filter_sum)>>8;
            b0 = (b0 / filter_sum)>>8;

            r0 = r0 < 0 ? 0 : (r0 > 255 ? 255 : r0);
            g0 = g0 < 0 ? 0 : (g0 > 255 ? 255 : g0);
            b0 = b0 < 0 ? 0 : (b0 > 255 ? 255 : b0);

            output[i].r = (unsigned char)r0;
            output[i].g = (unsigned char)g0;
            output[i].b = (unsigned char)b0;
        }

        if (i + 1 < total_pixels) {
            r1 = (r1 / filter_sum)>>8;
            g1 = (g1 / filter_sum)>>8;
            b1 = (b1 / filter_sum)>>8;

            r1 = r1 < 0 ? 0 : (r1 > 255 ? 255 : r1);
            g1 = g1 < 0 ? 0 : (g1 > 255 ? 255 : g1);
            b1 = b1 < 0 ? 0 : (b1 > 255 ? 255 : b1);

            output[i + 1].r = (unsigned char)r1;
            output[i + 1].g = (unsigned char)g1;
            output[i + 1].b = (unsigned char)b1;
        }

        if (i + 2 < total_pixels) {
            r2 = (r2 / filter_sum)>>8;
            g2 = (g2 / filter_sum)>>8;
            b2 = (b2 / filter_sum)>>8;

            r2 = r2 < 0 ? 0 : (r2 > 255 ? 255 : r2);
            g2 = g2 < 0 ? 0 : (g2 > 255 ? 255 : g2);
            b2 = b2 < 0 ? 0 : (b2 > 255 ? 255 : b2);

            output[i + 2].r = (unsigned char)r2;
            output[i + 2].g = (unsigned char)g2;
            output[i + 2].b = (unsigned char)b2;
        }

        if (i + 3 < total_pixels) {
            r3 = (r3 / filter_sum)>>8;
            g3 = (g3 / filter_sum)>>8;
            b3 = (b3 / filter_sum)>>8;

            r3 = r3 < 0 ? 0 : (r3 > 255 ? 255 : r3);
            g3 = g3 < 0 ? 0 : (g3 > 255 ? 255 : g3);
            b3 = b3 < 0 ? 0 : (b3 > 255 ? 255 : b3);

            output[i + 3].r = (unsigned char)r3;
            output[i + 3].g = (unsigned char)g3;
            output[i + 3].b = (unsigned char)b3;
        }

        if (i + 4 < total_pixels) {
            r4 = (r4 / filter_sum)>>8;
            g4 = (g4 / filter_sum)>>8;
            b4 = (b4 / filter_sum)>>8;

            r4 = r4 < 0 ? 0 : (r4 > 255 ? 255 : r4);
            g4 = g4 < 0 ? 0 : (g4 > 255 ? 255 : g4);
            b4 = b4 < 0 ? 0 : (b4 > 255 ? 255 : b4);
            output[i + 4].r = (unsigned char)r4;
            output[i + 4].g = (unsigned char)g4;
            output[i + 4].b = (unsigned char)b4;
        }

        if (i + 5 < total_pixels) {
            r5 = (r5 / filter_sum)>>8;
            g5 = (g5 / filter_sum)>>8;
            b5 = (b5 / filter_sum)>>8;

            r5 = r5 < 0 ? 0 : (r5 > 255 ? 255 : r5);
            g5 = g5 < 0 ? 0 : (g5 > 255 ? 255 : g5);
            b5 = b5 < 0 ? 0 : (b5 > 255 ? 255 : b5);
            output[i + 5].r = (unsigned char)r5;
            output[i + 5].g = (unsigned char)g5;
            output[i + 5].b = (unsigned char)b5;
        }

        if (i + 6 < total_pixels) {
            r6 = (r6 / filter_sum)>>8;
            g6 = (g6 / filter_sum)>>8;
            b6 = (b6 / filter_sum)>>8;

            r6 = r6 < 0 ? 0 : (r6 > 255 ? 255 : r6);
            g6 = g6 < 0 ? 0 : (g6 > 255 ? 255 : g6);
            b6 = b6 < 0 ? 0 : (b6 > 255 ? 255 : b6);
            output[i + 6].r = (unsigned char)r6;
            output[i + 6].g = (unsigned char)g6;
            output[i + 6].b = (unsigned char)b6;
        }
    }
}