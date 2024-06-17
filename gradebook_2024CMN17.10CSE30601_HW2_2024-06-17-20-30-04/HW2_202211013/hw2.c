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
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    

    register int x;
    register int y;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; x += 2) {
            float r = 0;
            float g = 0;
            float b = 0;

            float r1 = 0;
            float g1 = 0;
            float b1 = 0;

            for (int dy = -1; dy < 2; ++dy){
                int y_dy = y + dy;
                if ((y_dy) < 0 || (y_dy) >= height)
                    continue;
                int x1 = x + (-1);
                int x4 = x + 2;
                int tmp1 = (x1)+(y_dy)*width;
                int tmp2 = (dy+1)*3;
                int tmp3 = tmp1 + 1;
                int tmp4 = tmp2 + 1;
                int tmp5 = tmp1 + 2;
                int tmp6 = tmp2 + 2;
                int tmp7 = tmp1 + 3;
                
                if ((x1) >= 0 ) {
                    r += input[tmp1].r * filter[tmp2];
                    g += input[tmp1].g * filter[tmp2];
                    b += input[tmp1].b * filter[tmp2];
                }
                r1 += input[tmp3].r * filter[tmp2];
                g1 += input[tmp3].g * filter[tmp2];
                b1 += input[tmp3].b * filter[tmp2];

                r += input[tmp3].r * filter[tmp4];
                g += input[tmp3].g * filter[tmp4];
                b += input[tmp3].b * filter[tmp4];

                r1 += input[tmp5].r * filter[tmp4];
                g1 += input[tmp5].g * filter[tmp4];
                b1 += input[tmp5].b * filter[tmp4];

                r += input[tmp5].r * filter[tmp6];
                g += input[tmp5].g * filter[tmp6];
                b += input[tmp5].b * filter[tmp6];

                if (x4 < width) {
                    r1 += input[tmp7].r * filter[tmp6];
                    g1 += input[tmp7].g * filter[tmp6];
                    b1 += input[tmp7].b * filter[tmp6];
                }     
            }
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);
            r1 = r1 < 0 ? 0 : (r1 > 255 ? 255 : r1);
            g1 = g1 < 0 ? 0 : (g1 > 255 ? 255 : g1);
            b1 = b1 < 0 ? 0 : (b1 > 255 ? 255 : b1);


            int idx = x+y*width;
            output[idx].r = (unsigned char)r;
            output[idx].g = (unsigned char)g;
            output[idx++].b = (unsigned char)b;
            output[idx].r = (unsigned char)r1;
            output[idx].g = (unsigned char)g1;
            output[idx].b = (unsigned char)b1;
        }
    }
}