#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

static inline Pixel convolution_optimized(
        const Pixel* input, int x, int y, int width, int height, const float* filter) {
    double r = 0, g = 0, b = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int ix = x + dx;
            int iy = y + dy;

            if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
                const Pixel* pixel = &input[ix + iy * width];
                float filter_value = filter[(dx + 1) + (dy + 1) * 3];
                r += pixel->r * filter_value;
                g += pixel->g * filter_value;
                b += pixel->b * filter_value;
            }
        }
    }

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; x += 5) {
            double r1 = 0, g1 = 0, b1 = 0;
            double r2 = 0, g2 = 0, b2 = 0;
            double r3 = 0, g3 = 0, b3 = 0;
            double r4 = 0, g4 = 0, b4 = 0;
            double r5 = 0, g5 = 0, b5 = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                int ny = y + dy;
                if (ny < 0 || ny >= height) continue;

                for (int dx = -1; dx <= 1; ++dx) {
                    int nx1 = x + dx;
                    int nx2 = x + dx + 1;
                    int nx3 = x + dx + 2;
                    int nx4 = x + dx + 3;
                    int nx5 = x + dx + 4;

                    int filter_index = (dy + 1) * 3 + (dx + 1);

                    if (nx1 >= 0 && nx1 < width) {
                        int pixel_index1 = ny * width + nx1;
                        r1 += input[pixel_index1].r * filter[filter_index];
                        g1 += input[pixel_index1].g * filter[filter_index];
                        b1 += input[pixel_index1].b * filter[filter_index];

                        if (dx == -1 && dy == -1) {
                            __builtin_prefetch(&input[pixel_index1 + 5], 0, 1);
                        }
                    }

                    if (nx2 >= 0 && nx2 < width) {
                        int pixel_index2 = ny * width + nx2;
                        r2 += input[pixel_index2].r * filter[filter_index];
                        g2 += input[pixel_index2].g * filter[filter_index];
                        b2 += input[pixel_index2].b * filter[filter_index];
                    }

                    if (nx3 >= 0 && nx3 < width) {
                        int pixel_index3 = ny * width + nx3;
                        r3 += input[pixel_index3].r * filter[filter_index];
                        g3 += input[pixel_index3].g * filter[filter_index];
                        b3 += input[pixel_index3].b * filter[filter_index];
                    }

                    if (nx4 >= 0 && nx4 < width) {
                        int pixel_index4 = ny * width + nx4;
                        r4 += input[pixel_index4].r * filter[filter_index];
                        g4 += input[pixel_index4].g * filter[filter_index];
                        b4 += input[pixel_index4].b * filter[filter_index];
                    }

                    if (nx5 >= 0 && nx5 < width) {
                        int pixel_index5 = ny * width + nx5;
                        r5 += input[pixel_index5].r * filter[filter_index];
                        g5 += input[pixel_index5].g * filter[filter_index];
                        b5 += input[pixel_index5].b * filter[filter_index];
                    }
                }
            }

            // 결과 클램핑 및 저장
            r1 = (r1 < 0) ? 0 : ((r1 > 255) ? 255 : r1);
            g1 = (g1 < 0) ? 0 : ((g1 > 255) ? 255 : g1);
            b1 = (b1 < 0) ? 0 : ((b1 > 255) ? 255 : b1);
            output[y * width + x].r = (unsigned char)r1;
            output[y * width + x].g = (unsigned char)g1;
            output[y * width + x].b = (unsigned char)b1;

            if (x + 1 < width) {
                r2 = (r2 < 0) ? 0 : ((r2 > 255) ? 255 : r2);
                g2 = (g2 < 0) ? 0 : ((g2 > 255) ? 255 : g2);
                b2 = (b2 < 0) ? 0 : ((b2 > 255) ? 255 : b2);
                output[y * width + x + 1].r = (unsigned char)r2;
                output[y * width + x + 1].g = (unsigned char)g2;
                output[y * width + x + 1].b = (unsigned char)b2;
            }

            if (x + 2 < width) {
                r3 = (r3 < 0) ? 0 : ((r3 > 255) ? 255 : r3);
                g3 = (g3 < 0) ? 0 : ((g3 > 255) ? 255 : g3);
                b3 = (b3 < 0) ? 0 : ((b3 > 255) ? 255 : b3);
                output[y * width + x + 2].r = (unsigned char)r3;
                output[y * width + x + 2].g = (unsigned char)g3;
                output[y * width + x + 2].b = (unsigned char)b3;
            }

            if (x + 3 < width) {
                r4 = (r4 < 0) ? 0 : ((r4 > 255) ? 255 : r4);
                g4 = (g4 < 0) ? 0 : ((g4 > 255) ? 255 : g4);
                b4 = (b4 < 0) ? 0 : ((b4 > 255) ? 255 : b4);
                output[y * width + x + 3].r = (unsigned char)r4;
                output[y * width + x + 3].g = (unsigned char)g4;
                output[y * width + x + 3].b = (unsigned char)b4;
            }

            if (x + 4 < width) {
                r5 = (r5 < 0) ? 0 : ((r5 > 255) ? 255 : r5);
                g5 = (g5 < 0) ? 0 : ((g5 > 255) ? 255 : g5);
                b5 = (b5 < 0) ? 0 : ((b5 > 255) ? 255 : b5);
                output[y * width + x + 4].r = (unsigned char)r5;
                output[y * width + x + 4].g = (unsigned char)g5;
                output[y * width + x + 4].b = (unsigned char)b5;
            }
        }
    }
}
