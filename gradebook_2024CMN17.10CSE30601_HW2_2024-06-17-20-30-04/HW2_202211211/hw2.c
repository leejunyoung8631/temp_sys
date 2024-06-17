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

// Optimized convolution function
static inline Pixel convolution_optimized(
    Pixel* input, int x, int y, int width, int height, float* filter) {
    float r = 0.0f, g = 0.0f, b = 0.0f;  // Use float instead of double for better performance on most architectures
    int x_n1 = x - 1, x_p1 = x + 1;  // Precompute common indices for better readability and minor speedup
    Pixel* input_ptr;
    Pixel* input_num;

    // Loop unrolling for dy = -1
    input_num = input + (y - 1) * width + x_n1;
    if (y - 1 >= 0) {  // Check if within bounds
        input_ptr = input_num;
        // dx = -1
        if (x_n1 >= 0) {  // Check if within bounds
            r += input_ptr->r * filter[0];
            g += input_ptr->g * filter[0];
            b += input_ptr->b * filter[0];
        }
        input_ptr++;  // Move to the next pixel
        // dx = 0
        if (x >= 0) {  // Check if within bounds
            r += input_ptr->r * filter[1];
            g += input_ptr->g * filter[1];
            b += input_ptr->b * filter[1];
        }
        input_ptr++;  // Move to the next pixel
        // dx = 1
        if (x_p1 < width) {  // Check if within bounds
            r += input_ptr->r * filter[2];
            g += input_ptr->g * filter[2];
            b += input_ptr->b * filter[2];
        }
    }

    // Loop unrolling for dy = 0
    input_num += width;
    input_ptr = input_num;
    // dx = -1
    if (x_n1 >= 0) {  // Check if within bounds
        r += input_ptr->r * filter[3];
        g += input_ptr->g * filter[3];
        b += input_ptr->b * filter[3];
    }
    input_ptr++;  // Move to the next pixel
    // dx = 0
    if (x >= 0) {  // Check if within bounds
        r += input_ptr->r * filter[4];
        g += input_ptr->g * filter[4];
        b += input_ptr->b * filter[4];
    }
    input_ptr++;  // Move to the next pixel
    // dx = 1
    if (x_p1 < width) {  // Check if within bounds
        r += input_ptr->r * filter[5];
        g += input_ptr->g * filter[5];
        b += input_ptr->b * filter[5];
    }

    // Loop unrolling for dy = 1
    if (y + 1 < height) {  // Check if within bounds
        input_num += width;
        input_ptr = input_num;
        // dx = -1
        if (x_n1 >= 0) {  // Check if within bounds
            r += input_ptr->r * filter[6];
            g += input_ptr->g * filter[6];
            b += input_ptr->b * filter[6];
        }
        input_ptr++;  // Move to the next pixel
        // dx = 0
        if (x >= 0) {  // Check if within bounds
            r += input_ptr->r * filter[7];
            g += input_ptr->g * filter[7];
            b += input_ptr->b * filter[7];
        }
        input_ptr++;  // Move to the next pixel
        // dx = 1
        if (x_p1 < width) {  // Check if within bounds
            r += input_ptr->r * filter[8];
            g += input_ptr->g * filter[8];
            b += input_ptr->b * filter[8];
        }
    }

    // Clamp the values to [0, 255] and convert to unsigned char
    r = (r < 0.0f) ? 0.0f : (r > 255.0f) ? 255.0f : r;
    g = (g < 0.0f) ? 0.0f : (g > 255.0f) ? 255.0f : g;
    b = (b < 0.0f) ? 0.0f : (b > 255.0f) ? 255.0f : b;

    Pixel p;
    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    
    unsigned int x, y;
    Pixel* output_ptr = output;

    // Precompute filter for better memory access patterns
    float precomputed_filter[9] = {0};
    precomputed_filter[0] = filter[0];
    precomputed_filter[1] = filter[1];
    precomputed_filter[2] = filter[2];
    precomputed_filter[3] = filter[3];
    precomputed_filter[4] = filter[4];
    precomputed_filter[5] = filter[5];
    precomputed_filter[6] = filter[6];
    precomputed_filter[7] = filter[7];
    precomputed_filter[8] = filter[8];

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; x += 2) {
            if (x + 1 < width) {
                // Use optimized convolution function
                Pixel p0 = convolution_optimized(input, x, y, width, height, precomputed_filter);
                Pixel p1 = convolution_optimized(input, x + 1, y, width, height, precomputed_filter);

                // Store the results directly in the output array
                *output_ptr++ = p0;
                *output_ptr++ = p1;
            } else {
                // Handle the case where the width is odd
                *output_ptr++ = convolution_optimized(input, x, y, width, height, precomputed_filter);
            }
        }
    }
}
