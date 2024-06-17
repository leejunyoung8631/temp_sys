// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmplib.h"
#include "hw2.h"

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!

void filter_optimized(void* args[]) {
    const unsigned int width = *(unsigned int*)args[0];
    const unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    const float* filter = args[4];
    double tmp_output[width*3]; // 3 channels for RGB

    
    for (int y = 0; y < height; ++y) {
        memset(tmp_output, 0, width*sizeof(double)*3);
        int fy_start = (y > 0) * -1;
        int fy_end = (y < height - 1);
        for (int x = 0; x < width; ++x) {
            int fx_start = (x > 0) * -1;
            int fx_end = (x < width - 1);
            int x3 = x*3;
            double r = tmp_output[x3    ];
            double g = tmp_output[x3 + 1];
            double b = tmp_output[x3 + 2];
            for (int fy = fy_start; fy <= fy_end; ++fy){
                for (int fx = fx_start; fx <= fx_end; ++fx) {
                    float filter_value = filter[fx + fy * 3 + 4];
                    int input_offset = x + fx + (y+fy) * width;
                    r += input[input_offset].r * filter_value;
                    g += input[input_offset].g * filter_value;
                    b += input[input_offset].b * filter_value;
                }
            }
            int output_pt = x + y*width;
            output[output_pt].r = (unsigned char) fmax(0, fmin(255, r));
            output[output_pt].g = (unsigned char) fmax(0, fmin(255, g));
            output[output_pt].b = (unsigned char) fmax(0, fmin(255, b));
        }
    }
}