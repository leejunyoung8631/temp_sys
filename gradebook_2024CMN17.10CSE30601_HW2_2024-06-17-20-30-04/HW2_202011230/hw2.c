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
    double r = 0;
    double g = 0;
    double b = 0;    

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            r = 0;
            g = 0;
            b = 0;
            int max_x = x > 0;
            int min_x = x + 1 < width;
            int max_y = y > 0;
            int min_y = y + 1 < height;
            unsigned int out_idx = x+y*width;

            if (max_x && max_y){
                r += input[(x-1)+(y-1)*width].r * filter[0];
                g += input[(x-1)+(y-1)*width].g * filter[0];
                b += input[(x-1)+(y-1)*width].b * filter[0];
            }

            if (min_x && max_y){
                r += input[(x+1)+(y-1)*width].r * filter[2];
                g += input[(x+1)+(y-1)*width].g * filter[2];
                b += input[(x+1)+(y-1)*width].b * filter[2];
            }
            if (max_y){
                r += input[(x)+(y-1)*width].r * filter[1];
                g += input[(x)+(y-1)*width].g * filter[1];
                b += input[(x)+(y-1)*width].b * filter[1];
            }
            if (max_x){
                r += input[(x-1)+(y)*width].r * filter[3];
                g += input[(x-1)+(y)*width].g * filter[3];
                b += input[(x-1)+(y)*width].b * filter[3];
            }
            r += input[(x)+(y)*width].r * filter[4];
            g += input[(x)+(y)*width].g * filter[4];
            b += input[(x)+(y)*width].b * filter[4];
            if (min_x){
                r += input[(x+1)+(y)*width].r * filter[5];
                g += input[(x+1)+(y)*width].g * filter[5];
                b += input[(x+1)+(y)*width].b * filter[5];
            }
                        if (min_y){
                r += input[(x)+(y+1)*width].r * filter[7];
                g += input[(x)+(y+1)*width].g * filter[7];
                b += input[(x)+(y+1)*width].b * filter[7];
            }
                        if (min_x && min_y){
                r += input[(x+1)+(y+1)*width].r * filter[8];
                g += input[(x+1)+(y+1)*width].g * filter[8];
                b += input[(x+1)+(y+1)*width].b * filter[8];
            }
            if (max_x && min_y){
                r += input[(x-1)+(y+1)*width].r * filter[6];
                g += input[(x-1)+(y+1)*width].g * filter[6];
                b += input[(x-1)+(y+1)*width].b * filter[6];
            }

            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);


            output[out_idx].r = (unsigned char)r;
            output[out_idx].g = (unsigned char)g;
            output[out_idx].b = (unsigned char)b;
        }
    }
}