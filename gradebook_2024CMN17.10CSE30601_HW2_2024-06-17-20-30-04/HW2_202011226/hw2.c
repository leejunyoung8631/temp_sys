#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    
    int f0 = (int)(filter[0]);int f1 = (int)(filter[1]);int f2 = (int)(filter[2]);
    int f3 = (int)(filter[3]);int f4 = (int)(filter[4]);int f5 = (int)(filter[5]);
    int f6 = (int)(filter[6]);int f7 = (int)(filter[7]);int f8 = (int)(filter[8]);


    for (int x = 0; x < width; x++) {
            // Pixel 이 중복되지 않도록 필터 적용부를 완전히 언롤링
            int xm1 = x - 1; // x-1
            int xp1 = x + 1; // x+1
            //x는 고정되어 있는데 loop에서 계속해서 계산되므로 밖으로 뺌
            // Ensure boundary conditions are met
            int xm1_valid = xm1 >= 0;
            int xp1_valid = xp1 < width;

        for (int y = 0; y < height; y++) {
            int r = 0, g = 0, b = 0;

            // Pixel 이 중복되지 않도록 필터 적용부를 완전히 언롤링
            int ym1 = y - 1; // y-1
            int yp1 = y + 1; // y+1

            // Ensure boundary conditions are met
            int ym1_valid = ym1 >= 0;
            int yp1_valid = yp1 < height;

            // Top row
            if (ym1_valid) {
                int y1w =ym1 * width; // Same calcuation repeated 
                if (xm1_valid) {
                    Pixel p = input[y1w + xm1];
                    r += p.r * f0;
                    g += p.g * f0;
                    b += p.b * f0;
                }
                {
                    Pixel p = input[y1w + x];
                    r += p.r * f1;
                    g += p.g * f1;
                    b += p.b * f1;
                }
                if (xp1_valid) {
                    Pixel p = input[y1w + xp1];
                    r += p.r * f2;
                    g += p.g * f2;
                    b += p.b * f2;
                }
            }
            
            int yw = y * width;  //same calc
            // Middle row
            if (xm1_valid) {
                Pixel p = input[yw + xm1];
                r += p.r * f3;
                g += p.g * f3;
                b += p.b * f3;
            }
            {
                Pixel p = input[yw + x];
                r += p.r * f4;
                g += p.g * f4;
                b += p.b * f4;
            }
            if (xp1_valid) {
                Pixel p = input[yw + xp1];
                r += p.r * f5;
                g += p.g * f5;
                b += p.b * f5;
            }

            // Bottom row
            if (yp1_valid) {
                int yp1w= yp1 * width;
                if (xm1_valid) {
                    Pixel p = input[ yp1w + xm1];
                    r += p.r * f6;
                    g += p.g * f6;
                    b += p.b * f6;
                }
                {
                    Pixel p = input[yp1w + x];
                    r += p.r * f7;
                    g += p.g * f7;
                    b += p.b * f7;
                }
                if (xp1_valid) {
                    Pixel p = input[yp1w + xp1];
                    r += p.r * f8;
                    g += p.g * f8;
                    b += p.b * f8;
                }
            }

            // 클리핑 (클립 연산을 통합하여 성능 향상)
            r = r > 255 ? 255 : r < 0 ? 0 : r;
            g = g > 255 ? 255 : g < 0 ? 0 : g;
            b = b > 255 ? 255 : b < 0 ? 0 : b;

            output[yw + x] = (Pixel){(unsigned char)r, (unsigned char)g, (unsigned char)b};
        }
    }
}
