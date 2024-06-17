#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"


#define FILTER_SIZE 3
#define FILTER_RADIUS 1

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* restrict input = (Pixel*)args[2];
    Pixel* restrict output = (Pixel*)args[3];
    float* restrict filter = (float*)args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r = 0.0, g = 0.0, b = 0.0;

            int ym1 = y - 1;
            int yp1 = y + 1;
            int xm1 = x - 1;
            int xp1 = x + 1;

            if (y > 0) {
                if (x > 0) {
                    int idx = (xm1) + (ym1) * width;
                    r += input[idx].r * filter[0];
                    g += input[idx].g * filter[0];
                    b += input[idx].b * filter[0];
                }
                int idx = x + (ym1) * width;
                r += input[idx].r * filter[1];
                g += input[idx].g * filter[1];
                b += input[idx].b * filter[1];
                if (x < width - 1) {
                    int idx = (xp1) + (ym1) * width;
                    r += input[idx].r * filter[2];
                    g += input[idx].g * filter[2];
                    b += input[idx].b * filter[2];
                }
            }

            if (x > 0) {
                int idx = (xm1) + y * width;
                r += input[idx].r * filter[3];
                g += input[idx].g * filter[3];
                b += input[idx].b * filter[3];
            }
            int idx = x + y * width;
            r += input[idx].r * filter[4];
            g += input[idx].g * filter[4];
            b += input[idx].b * filter[4];
            if (x < width - 1) {
                int idx = (xp1) + y * width;
                r += input[idx].r * filter[5];
                g += input[idx].g * filter[5];
                b += input[idx].b * filter[5];
            }

            if (y < height - 1) {
                if (x > 0) {
                    int idx = (xm1) + (yp1) * width;
                    r += input[idx].r * filter[6];
                    g += input[idx].g * filter[6];
                    b += input[idx].b * filter[6];
                }
                int idx = x + (yp1) * width;
                r += input[idx].r * filter[7];
                g += input[idx].g * filter[7];
                b += input[idx].b * filter[7];
                if (x < width - 1) {
                    int idx = (xp1) + (yp1) * width;
                    r += input[idx].r * filter[8];
                    g += input[idx].g * filter[8];
                    b += input[idx].b * filter[8];
                }
            }

            Pixel p;
            p.r = (unsigned char)(r < 0.0 ? 0 : (r > 255.0 ? 255 : r));
            p.g = (unsigned char)(g < 0.0 ? 0 : (g > 255.0 ? 255 : g));
            p.b = (unsigned char)(b < 0.0 ? 0 : (b > 255.0 ? 255 : b));

            output[x + y * width] = p;
        }
    }
}
