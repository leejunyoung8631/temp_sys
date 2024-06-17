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


void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    
    int y_width = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
        
	    double r = 0;
	    double g = 0;
	    double b = 0;
	    
	    int x_min = (x - 1 < 0) ? 0 : x - 1;
	    int x_max = (x + 1 >= width) ? width - 1 : x + 1;
	    int y_min = (y - 1 < 0) ? 0 : y - 1;
	    int y_max = (y + 1 >= height) ? height - 1 : y + 1;
	    int x_one = x-1;
	    int y_one = y-1;
	    int dy_width = y_min*width;
	    for (int dy = y_min; dy <= y_max; ++dy) {
	        int dx = x_min;
	        int limit = x_max-2;
	        int filter_y = dy - y_one;
            for (dx = x_min; dx <= limit; dx+=3) {
                int filter_x = dx - x_one;
                
                r = r+(input[dx + dy_width].r * filter[filter_x + filter_y * 3]
                + input[dx+1 + dy_width].r * filter[filter_x+1 + filter_y * 3]
                + input[dx+2 + dy_width].r * filter[filter_x+2 + filter_y * 3]);
                g = g+(input[dx + dy_width].g * filter[filter_x + filter_y * 3]
                + input[dx+1 + dy_width].g * filter[filter_x+1 + filter_y * 3]
                + input[dx+2 + dy_width].g * filter[filter_x+2 + filter_y * 3]);
                b = b+(input[dx + dy_width].b * filter[filter_x + filter_y * 3]
                + input[dx+1 + dy_width].b * filter[filter_x+1 + filter_y * 3]
                + input[dx+2 + dy_width].b * filter[filter_x+2 + filter_y * 3]);
            }
            for(; dx<=x_max;dx++){
                int filter_x = dx - x_one;
                r = r+(input[dx + dy_width].r * filter[filter_x + filter_y * 3]);
                g = g+(input[dx + dy_width].g * filter[filter_x + filter_y * 3]);
                b = b+(input[dx + dy_width].b * filter[filter_x + filter_y * 3]);
            }
            dy_width += width;
		
	    }

	    r = (r < 0) ? 0 : (r > 255) ? 255 : r;
	    g = (g < 0) ? 0 : (g > 255) ? 255 : g;
	    b = (b < 0) ? 0 : (b > 255) ? 255 : b;

        output[x+y_width].r = (unsigned char)r;
        output[x+y_width].g = (unsigned char)g;
        output[x+y_width].b = (unsigned char)b;

        }
        y_width += width;
    }
}
