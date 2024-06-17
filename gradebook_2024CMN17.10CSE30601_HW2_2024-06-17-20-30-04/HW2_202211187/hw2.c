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

#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

static Pixel convolution(
        Pixel* restrict input, int x, int y, int width, int height, float* restrict filter) {
    float r = 0.;
    float g = 0.;
    float b = 0.;
    int filter_index = 0;
    
    for (int dy = -1; dy < 2; ++dy) {
    
        int yy = y + dy;
        
        if (yy < 0 || yy >= height) {
            filter_index += 3;
            continue;
        }
        
        int yy_width = yy*width;
        for (int dx = -1; dx < 2; ++dx, ++filter_index) {
        
            int xx = x + dx;
            
            if (xx < 0 || xx >= width) {
                continue;
            }
            
            float filter_value = filter[filter_index];
            Pixel p_input = input[xx+yy_width];
            
            r += (float)p_input.r * filter_value;
            g += (float)p_input.g * filter_value;
            b += (float)p_input.b * filter_value;
        }
    }
    
    Pixel p;
    p.r = (unsigned char)CLAMP(r, 0., 255.);
    p.g = (unsigned char)CLAMP(g, 0., 255.);
    p.b = (unsigned char)CLAMP(b, 0., 255.);

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int* restrict) args[0];
    unsigned int height = *(unsigned int* restrict) args[1];
    Pixel* restrict input = args[2];
    Pixel* restrict output = args[3];
    float* restrict filter = args[4];

    for (int y = 0; y < height; ++y) {
    	int y_width = y*width;
        for (int x = 0; x < width; ++x) {
            output[x+y_width] = convolution(input, x, y, width, height, filter);
        }
    }
}
