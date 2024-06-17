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

static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            if ((y + dy) < 0 || (y + dy) >= height)
                continue;

            if ((x + dx) < 0 || (x + dx) >= width)
                continue;

            r += input[(x+dx)+(y+dy)*width].r * filter[(dx+1)+(dy+1)*3];
            g += input[(x+dx)+(y+dy)*width].g * filter[(dx+1)+(dy+1)*3];
            b += input[(x+dx)+(y+dy)*width].b * filter[(dx+1)+(dy+1)*3];
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

#define FILTER_SIZE 3

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    int filter_offset = FILTER_SIZE / 2;
    const int prefetch_distance = 64; // Adjust as needed for optimal prefetching

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; x += 16) {
            double r1 = 0, g1 = 0, b1 = 0;
            double r2 = 0, g2 = 0, b2 = 0;
            double r3 = 0, g3 = 0, b3 = 0;
            double r4 = 0, g4 = 0, b4 = 0;
            double r5 = 0, g5 = 0, b5 = 0;
            double r6 = 0, g6 = 0, b6 = 0;
            double r7 = 0, g7 = 0, b7 = 0;
            double r8 = 0, g8 = 0, b8 = 0;
            double r9 = 0, g9 = 0, b9 = 0;
            double r10 = 0, g10 = 0, b10 = 0;
            double r11 = 0, g11 = 0, b11 = 0;
            double r12 = 0, g12 = 0, b12 = 0;
            double r13 = 0, g13 = 0, b13 = 0;
            double r14 = 0, g14 = 0, b14 = 0;
            double r15 = 0, g15 = 0, b15 = 0;
            double r16 = 0, g16 = 0, b16 = 0;

            for (int dy = -filter_offset; dy <= filter_offset; ++dy) {
                int ny = y + dy;
                if (ny < 0 || ny >= height) continue;

                for (int dx = -filter_offset; dx <= filter_offset; ++dx) {
                    int filter_index = (dy + filter_offset) * FILTER_SIZE + (dx + filter_offset);
                    float fval = filter[filter_index];

                    int nx1 = x + dx;
                    int nx2 = x + dx + 1;
                    int nx3 = x + dx + 2;
                    int nx4 = x + dx + 3;
                    int nx5 = x + dx + 4;
                    int nx6 = x + dx + 5;
                    int nx7 = x + dx + 6;
                    int nx8 = x + dx + 7;
                    int nx9 = x + dx + 8;
                    int nx10 = x + dx + 9;
                    int nx11 = x + dx + 10;
                    int nx12 = x + dx + 11;
                    int nx13 = x + dx + 12;
                    int nx14 = x + dx + 13;
                    int nx15 = x + dx + 14;
                    int nx16 = x + dx + 15;

                    if (nx1 >= 0 && nx1 < width) {
                        int pixel_index1 = ny * width + nx1;
                        if (dx == -filter_offset && dy == -filter_offset) {
                            __builtin_prefetch(&input[pixel_index1 + prefetch_distance], 0, 1);
                        }
                        Pixel p1 = input[pixel_index1];
                        r1 += p1.r * fval;
                        g1 += p1.g * fval;
                        b1 += p1.b * fval;
                    }
                    if (nx2 >= 0 && nx2 < width) {
                        int pixel_index2 = ny * width + nx2;
                        Pixel p2 = input[pixel_index2];
                        r2 += p2.r * fval;
                        g2 += p2.g * fval;
                        b2 += p2.b * fval;
                    }
                    if (nx3 >= 0 && nx3 < width) {
                        int pixel_index3 = ny * width + nx3;
                        Pixel p3 = input[pixel_index3];
                        r3 += p3.r * fval;
                        g3 += p3.g * fval;
                        b3 += p3.b * fval;
                    }
                    if (nx4 >= 0 && nx4 < width) {
                        int pixel_index4 = ny * width + nx4;
                        Pixel p4 = input[pixel_index4];
                        r4 += p4.r * fval;
                        g4 += p4.g * fval;
                        b4 += p4.b * fval;
                    }
                    if (nx5 >= 0 && nx5 < width) {
                        int pixel_index5 = ny * width + nx5;
                        Pixel p5 = input[pixel_index5];
                        r5 += p5.r * fval;
                        g5 += p5.g * fval;
                        b5 += p5.b * fval;
                    }
                    if (nx6 >= 0 && nx6 < width) {
                        int pixel_index6 = ny * width + nx6;
                        Pixel p6 = input[pixel_index6];
                        r6 += p6.r * fval;
                        g6 += p6.g * fval;
                        b6 += p6.b * fval;
                    }
                    if (nx7 >= 0 && nx7 < width) {
                        int pixel_index7 = ny * width + nx7;
                        Pixel p7 = input[pixel_index7];
                        r7 += p7.r * fval;
                        g7 += p7.g * fval;
                        b7 += p7.b * fval;
                    }
                    if (nx8 >= 0 && nx8 < width) {
                        int pixel_index8 = ny * width + nx8;
                        Pixel p8 = input[pixel_index8];
                        r8 += p8.r * fval;
                        g8 += p8.g * fval;
                        b8 += p8.b * fval;
                    }
                    if (nx9 >= 0 && nx9 < width) {
                        int pixel_index9 = ny * width + nx9;
                        Pixel p9 = input[pixel_index9];
                        r9 += p9.r * fval;
                        g9 += p9.g * fval;
                        b9 += p9.b * fval;
                    }
                    if (nx10 >= 0 && nx10 < width) {
                        int pixel_index10 = ny * width + nx10;
                        Pixel p10 = input[pixel_index10];
                        r10 += p10.r * fval;
                        g10 += p10.g * fval;
                        b10 += p10.b * fval;
                    }
                    if (nx11 >= 0 && nx11 < width) {
                        int pixel_index11 = ny * width + nx11;
                        Pixel p11 = input[pixel_index11];
                        r11 += p11.r * fval;
                        g11 += p11.g * fval;
                        b11 += p11.b * fval;
                    }
                    if (nx12 >= 0 && nx12 < width) {
                        int pixel_index12 = ny * width + nx12;
                        Pixel p12 = input[pixel_index12];
                        r12 += p12.r * fval;
                        g12 += p12.g * fval;
                        b12 += p12.b * fval;
                    }
                    if (nx13 >= 0 && nx13 < width) {
                        int pixel_index13 = ny * width + nx13;
                        Pixel p13 = input[pixel_index13];
                        r13 += p13.r * fval;
                        g13 += p13.g * fval;
                        b13 += p13.b * fval;
                    }
                    if (nx14 >= 0 && nx14 < width) {
                        int pixel_index14 = ny * width + nx14;
                        Pixel p14 = input[pixel_index14];
                        r14 += p14.r * fval;
                        g14 += p14.g * fval;
                        b14 += p14.b * fval;
                    }
                    if (nx15 >= 0 && nx15 < width) {
                        int pixel_index15 = ny * width + nx15;
                        Pixel p15 = input[pixel_index15];
                        r15 += p15.r * fval;
                        g15 += p15.g * fval;
                        b15 += p15.b * fval;
                    }
                    if (nx16 >= 0 && nx16 < width) {
                        int pixel_index16 = ny * width + nx16;
                        Pixel p16 = input[pixel_index16];
                        r16 += p16.r * fval;
                        g16 += p16.g * fval;
                        b16 += p16.b * fval;
                    }
                }
            }

            // 값의 범위를 0-255로 클램핑
            r1 = r1 < 0 ? 0 : (r1 > 255 ? 255 : r1);
            g1 = g1 < 0 ? 0 : (g1 > 255 ? 255 : g1);
            b1 = b1 < 0 ? 0 : (b1 > 255 ? 255 : b1);
            r2 = r2 < 0 ? 0 : (r2 > 255 ? 255 : r2);
            g2 = g2 < 0 ? 0 : (g2 > 255 ? 255 : g2);
            b2 = b2 < 0 ? 0 : (b2 > 255 ? 255 : b2);
            r3 = r3 < 0 ? 0 : (r3 > 255 ? 255 : r3);
            g3 = g3 < 0 ? 0 : (g3 > 255 ? 255 : g3);
            b3 = b3 < 0 ? 0 : (b3 > 255 ? 255 : b3);
            r4 = r4 < 0 ? 0 : (r4 > 255 ? 255 : r4);
            g4 = g4 < 0 ? 0 : (g4 > 255 ? 255 : g4);
            b4 = b4 < 0 ? 0 : (b4 > 255 ? 255 : b4);
            r5 = r5 < 0 ? 0 : (r5 > 255 ? 255 : r5);
            g5 = g5 < 0 ? 0 : (g5 > 255 ? 255 : g5);
            b5 = b5 < 0 ? 0 : (b5 > 255 ? 255 : b5);
            r6 = r6 < 0 ? 0 : (r6 > 255 ? 255 : r6);
            g6 = g6 < 0 ? 0 : (g6 > 255 ? 255 : g6);
            b6 = b6 < 0 ? 0 : (b6 > 255 ? 255 : b6);
            r7 = r7 < 0 ? 0 : (r7 > 255 ? 255 : r7);
            g7 = g7 < 0 ? 0 : (g7 > 255 ? 255 : g7);
            b7 = b7 < 0 ? 0 : (b7 > 255 ? 255 : b7);
            r8 = r8 < 0 ? 0 : (r8 > 255 ? 255 : r8);
            g8 = g8 < 0 ? 0 : (g8 > 255 ? 255 : g8);
            b8 = b8 < 0 ? 0 : (b8 > 255 ? 255 : b8);
            r9 = r9 < 0 ? 0 : (r9 > 255 ? 255 : r9);
            g9 = g9 < 0 ? 0 : (g9 > 255 ? 255 : g9);
            b9 = b9 < 0 ? 0 : (b9 > 255 ? 255 : b9);
            r10 = r10 < 0 ? 0 : (r10 > 255 ? 255 : r10);
            g10 = g10 < 0 ? 0 : (g10 > 255 ? 255 : g10);
            b10 = b10 < 0 ? 0 : (b10 > 255 ? 255 : b10);
            r11 = r11 < 0 ? 0 : (r11 > 255 ? 255 : r11);
            g11 = g11 < 0 ? 0 : (g11 > 255 ? 255 : g11);
            b11 = b11 < 0 ? 0 : (b11 > 255 ? 255 : b11);
            r12 = r12 < 0 ? 0 : (r12 > 255 ? 255 : r12);
            g12 = g12 < 0 ? 0 : (g12 > 255 ? 255 : g12);
            b12 = b12 < 0 ? 0 : (b12 > 255 ? 255 : b12);
            r13 = r13 < 0 ? 0 : (r13 > 255 ? 255 : r13);
            g13 = g13 < 0 ? 0 : (g13 > 255 ? 255 : g13);
            b13 = b13 < 0 ? 0 : (b13 > 255 ? 255 : b13);
            r14 = r14 < 0 ? 0 : (r14 > 255 ? 255 : r14);
            g14 = g14 < 0 ? 0 : (g14 > 255 ? 255 : g14);
            b14 = b14 < 0 ? 0 : (b14 > 255 ? 255 : b14);
            r15 = r15 < 0 ? 0 : (r15 > 255 ? 255 : r15);
            g15 = g15 < 0 ? 0 : (g15 > 255 ? 255 : g15);
            b15 = b15 < 0 ? 0 : (b15 > 255 ? 255 : b15);
            r16 = r16 < 0 ? 0 : (r16 > 255 ? 255 : r16);
            g16 = g16 < 0 ? 0 : (g16 > 255 ? 255 : g16);
            b16 = b16 < 0 ? 0 : (b16 > 255 ? 255 : b16);

            int output_index1 = y * width + x;
            output[output_index1].r = (unsigned char)r1;
            output[output_index1].g = (unsigned char)g1;
            output[output_index1].b = (unsigned char)b1;

            if (x + 1 < width) {
                int output_index2 = y * width + x + 1;
                output[output_index2].r = (unsigned char)r2;
                output[output_index2].g = (unsigned char)g2;
                output[output_index2].b = (unsigned char)b2;
            }

            if (x + 2 < width) {
                int output_index3 = y * width + x + 2;
                output[output_index3].r = (unsigned char)r3;
                output[output_index3].g = (unsigned char)g3;
                output[output_index3].b = (unsigned char)b3;
            }

            if (x + 3 < width) {
                int output_index4 = y * width + x + 3;
                output[output_index4].r = (unsigned char)r4;
                output[output_index4].g = (unsigned char)g4;
                output[output_index4].b = (unsigned char)b4;
            }

            if (x + 4 < width) {
                int output_index5 = y * width + x + 4;
                output[output_index5].r = (unsigned char)r5;
                output[output_index5].g = (unsigned char)g5;
                output[output_index5].b = (unsigned char)b5;
            }

            if (x + 5 < width) {
                int output_index6 = y * width + x + 5;
                output[output_index6].r = (unsigned char)r6;
                output[output_index6].g = (unsigned char)g6;
                output[output_index6].b = (unsigned char)b6;
            }

            if (x + 6 < width) {
                int output_index7 = y * width + x + 6;
                output[output_index7].r = (unsigned char)r7;
                output[output_index7].g = (unsigned char)g7;
                output[output_index7].b = (unsigned char)b7;
            }

            if (x + 7 < width) {
                int output_index8 = y * width + x + 7;
                output[output_index8].r = (unsigned char)r8;
                output[output_index8].g = (unsigned char)g8;
                output[output_index8].b = (unsigned char)b8;
            }

            if (x + 8 < width) {
                int output_index9 = y * width + x + 8;
                output[output_index9].r = (unsigned char)r9;
                output[output_index9].g = (unsigned char)g9;
                output[output_index9].b = (unsigned char)b9;
            }

            if (x + 9 < width) {
                int output_index10 = y * width + x + 9;
                output[output_index10].r = (unsigned char)r10;
                output[output_index10].g = (unsigned char)g10;
                output[output_index10].b = (unsigned char)b10;
            }

            if (x + 10 < width) {
                int output_index11 = y * width + x + 10;
                output[output_index11].r = (unsigned char)r11;
                output[output_index11].g = (unsigned char)g11;
                output[output_index11].b = (unsigned char)b11;
            }

            if (x + 11 < width) {
                int output_index12 = y * width + x + 11;
                output[output_index12].r = (unsigned char)r12;
                output[output_index12].g = (unsigned char)g12;
                output[output_index12].b = (unsigned char)b12;
            }

            if (x + 12 < width) {
                int output_index13 = y * width + x + 12;
                output[output_index13].r = (unsigned char)r13;
                output[output_index13].g = (unsigned char)g13;
                output[output_index13].b = (unsigned char)b13;
            }

            if (x + 13 < width) {
                int output_index14 = y * width + x + 13;
                output[output_index14].r = (unsigned char)r14;
                output[output_index14].g = (unsigned char)g14;
                output[output_index14].b = (unsigned char)b14;
            }

            if (x + 14 < width) {
                int output_index15 = y * width + x + 14;
                output[output_index15].r = (unsigned char)r15;
                output[output_index15].g = (unsigned char)g15;
                output[output_index15].b = (unsigned char)b15;
            }

            if (x + 15 < width) {
                int output_index16 = y * width + x + 15;
                output[output_index16].r = (unsigned char)r16;
                output[output_index16].g = (unsigned char)g16;
                output[output_index16].b = (unsigned char)b16;
            }
        }
    }
}

