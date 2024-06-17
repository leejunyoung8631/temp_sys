//8th
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* restrict input = (Pixel* restrict)args[2];
    Pixel* restrict output = (Pixel* restrict)args[3];
    float* restrict filter = (float* restrict)args[4];

    // 필터 요소를 레지스터에 저장
    float f0 = filter[0], f1 = filter[1], f2 = filter[2];
    float f3 = filter[3], f4 = filter[4], f5 = filter[5];
    float f6 = filter[6], f7 = filter[7], f8 = filter[8];

    // 내부 픽셀에 대해 필터 적용
    for (unsigned int y = 1; y < height - 1; ++y) {
        for (unsigned int x = 1; x < width - 1; ++x) {
            double r = 0, g = 0, b = 0;

            Pixel* in_ptr = &input[(y - 1) * width + (x - 1)];

            r += in_ptr[0].r * f0 + in_ptr[1].r * f1 + in_ptr[2].r * f2;
            g += in_ptr[0].g * f0 + in_ptr[1].g * f1 + in_ptr[2].g * f2;
            b += in_ptr[0].b * f0 + in_ptr[1].b * f1 + in_ptr[2].b * f2;

            in_ptr += width;
            r += in_ptr[0].r * f3 + in_ptr[1].r * f4 + in_ptr[2].r * f5;
            g += in_ptr[0].g * f3 + in_ptr[1].g * f4 + in_ptr[2].g * f5;
            b += in_ptr[0].b * f3 + in_ptr[1].b * f4 + in_ptr[2].b * f5;

            in_ptr += width;
            r += in_ptr[0].r * f6 + in_ptr[1].r * f7 + in_ptr[2].r * f8;
            g += in_ptr[0].g * f6 + in_ptr[1].g * f7 + in_ptr[2].g * f8;
            b += in_ptr[0].b * f6 + in_ptr[1].b * f7 + in_ptr[2].b * f8;

            Pixel p;
            p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

            output[y * width + x] = p;
        }
    }

    // 경계 처리
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (x > 0 && x < width - 1 && y > 0 && y < height - 1) {
                continue; 
            }

            double r = 0, g = 0, b = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                int yy = y + dy;
                if (yy < 0 || yy >= height) continue;

                for (int dx = -1; dx <= 1; ++dx) {
                    int xx = x + dx;
                    if (xx < 0 || xx >= width) continue;

                    Pixel* in_ptr = &input[yy * width + xx];
                    float fe = filter[(dy + 1) * 3 + (dx + 1)];

                    r += in_ptr->r * fe;
                    g += in_ptr->g * fe;
                    b += in_ptr->b * fe;
                }
            }

            Pixel p;
            p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

            output[y * width + x] = p;
        }
    }
}
