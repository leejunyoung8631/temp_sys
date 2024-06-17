#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmplib.h"
#include "hw2.h"

#define BLOCK_SIZE 128    

void filter_optimized(void* args[]) {    
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter_a = args[4];
    
    float filter[9];
    for (int i = 0; i < 9; i++){
        filter[i] = filter_a[i];}
    
    for (int yy = 0; yy < height; yy += BLOCK_SIZE){
        for (int xx = 0; xx < width; xx += BLOCK_SIZE){
            int max_y = fmin(yy + BLOCK_SIZE, height);
            int max_x = fmin(xx + BLOCK_SIZE, width);
            for (int y = yy; y < max_y; y++) {
                for (int x = xx; x < max_x; x++) {
                    double r= 0;
                    double g = 0;
                    double b = 0;
                    if (x > 0 && y > 0 && x < width - 1 && y < height - 1) {
                        r += input[(x - 1) + (y - 1) * width].r * filter[0] + input[x + (y - 1) * width].r * filter[1] + input[(x + 1) + (y - 1) * width].r * filter[2];
                        g += input[(x - 1) + (y - 1) * width].g * filter[0] + input[x + (y - 1) * width].g * filter[1] + input[(x + 1) + (y - 1) * width].g * filter[2];
                        b += input[(x - 1) + (y - 1) * width].b * filter[0] + input[x + (y - 1) * width].b * filter[1] + input[(x + 1) + (y - 1) * width].b * filter[2];

                        r += input[(x - 1) + y * width].r * filter[3] + input[x + y * width].r * filter[4] + input[(x + 1) + y * width].r * filter[5];
                        g += input[(x - 1) + y * width].g * filter[3] + input[x + y * width].g * filter[4] + input[(x + 1) + y * width].g * filter[5];
                        b += input[(x - 1) + y * width].b * filter[3] + input[x + y * width].b * filter[4] + input[(x + 1) + y * width].b * filter[5];

                        r += input[(x - 1) + (y + 1) * width].r * filter[6] + input[x + (y + 1) * width].r * filter[7] + input[(x + 1) + (y + 1) * width].r * filter[8];
                        g += input[(x - 1) + (y + 1) * width].g * filter[6] + input[x + (y + 1) * width].g * filter[7] + input[(x + 1) + (y + 1) * width].g * filter[8];
                        b += input[(x - 1) + (y + 1) * width].b * filter[6] + input[x + (y + 1) * width].b * filter[7] + input[(x + 1) + (y + 1) * width].b * filter[8];
                    }
                    
                    else {
                        for (int dy = -1; dy <= 1; ++dy) {
                            for (int dx = -1; dx <= 1; ++dx) {
                                int nx = x + dx;
                                int ny = y + dy;
                                if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                                    Pixel current_pixel = input[nx + ny * width];
                                    float current_filter = filter[(dx + 1) + (dy + 1) * 3];

                                    r += current_pixel.r * current_filter;
                                    g += current_pixel.g * current_filter;
                                    b += current_pixel.b * current_filter;
                                }
                            }
                        }
                    }
                    
                    if (r < 0) r = 0;
                    if (g < 0) g = 0;
                    if (b < 0) b = 0;
                    
                    if (r > 255) r = 255;
                    if (g > 255) g = 255;
                    if (b > 255) b = 255;
                    
                    output[x + y * width].r = (unsigned char)r;
                    output[x + y * width].g = (unsigned char)g;
                    output[x + y * width].b = (unsigned char)b;
                }
            }
        }
    }
}
