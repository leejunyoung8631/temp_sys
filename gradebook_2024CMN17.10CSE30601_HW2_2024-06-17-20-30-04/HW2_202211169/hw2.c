#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    const int block_size = 16;
    int stride = width;

    for (int bx = 0; bx < width; bx += block_size) {
        for (int by = 0; by < height; by += block_size) {
            int max_x = (bx + block_size < width) ? bx + block_size : width;
            int max_y = (by + block_size < height) ? by + block_size : height;

            for (int x = bx; x < max_x; x += 4) {
                for (int y = by; y < max_y; ++y) {
                    double r1 = 0, g1 = 0, b1 = 0;
                    double r2 = 0, g2 = 0, b2 = 0;
                    double r3 = 0, g3 = 0, b3 = 0;
                    double r4 = 0, g4 = 0, b4 = 0;

                    for (int dy = -1; dy <= 1; ++dy) {
                        int y_d = y + dy;
                        if (y_d < 0 || y_d >= height) continue;

                        int fy = (dy + 1) * 3; 
                        for (int dx = -1; dx <= 1; ++dx) {
                            int fx = (dx + 1);
                            float f = filter[fx + fy];

                            int x_d1 = x + dx;
                            int x_d2 = x + 1 + dx;
                            int x_d3 = x + 2 + dx;
                            int x_d4 = x + 3 + dx;

                            if (x_d1 >= 0 && x_d1 < width) {
                                int idx1 = x_d1 + y_d * stride;
                                r1 += input[idx1].r * f;
                                g1 += input[idx1].g * f;
                                b1 += input[idx1].b * f;
                            }
                            if (x_d2 >= 0 && x_d2 < width && x + 1 < max_x) {
                                int idx2 = x_d2 + y_d * stride;
                                r2 += input[idx2].r * f;
                                g2 += input[idx2].g * f;
                                b2 += input[idx2].b * f;
                            }
                            if (x_d3 >= 0 && x_d3 < width && x + 2 < max_x) {
                                int idx3 = x_d3 + y_d * stride; 
                                r3 += input[idx3].r * f;
                                g3 += input[idx3].g * f;
                                b3 += input[idx3].b * f;
                            }
                            if (x_d4 >= 0 && x_d4 < width && x + 3 < max_x) {
                                int idx4 = x_d4 + y_d * stride;
                                r4 += input[idx4].r * f;
                                g4 += input[idx4].g * f;
                                b4 += input[idx4].b * f;
                            }
                        }
                    }

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

                    Pixel p1 = {(unsigned char)r1, (unsigned char)g1, (unsigned char)b1};
                    Pixel p2 = {(unsigned char)r2, (unsigned char)g2, (unsigned char)b2};
                    Pixel p3 = {(unsigned char)r3, (unsigned char)g3, (unsigned char)b3};
                    Pixel p4 = {(unsigned char)r4, (unsigned char)g4, (unsigned char)b4};

                    int yw = y * stride; 
                    output[x + yw] = p1;
                    if (x + 1 < max_x) {
                        output[x + 1 + yw] = p2;
                    }
                    if (x + 2 < max_x) {
                        output[x + 2 + yw] = p3;
                    }
                    if (x + 3 < max_x) {
                        output[x + 3 + yw] = p4;
                    }
                }
            }
        }
    }
}
