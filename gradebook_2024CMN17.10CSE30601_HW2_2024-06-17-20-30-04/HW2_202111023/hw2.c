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

typedef struct 
{
    double r;
    double g;
    double b;
} Pixel_double;


static void convolution(
        Pixel* input, Pixel_double* output, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;
    


    for (int row = 0; row < height; row++) {
        int row_idx = row * width;
        for (int col = 0; col < width-2; col++) {
            

            int col_idx = row_idx + col;
            Pixel input_0 = input[col_idx], input_1 = input[col_idx + 1], input_2 = input[col_idx + 2];

            for (int kh = 2; kh >= 0; kh--) {
                int kh3 = kh*3;
                r = (input_0.r * filter[kh3]) + (input_1.r * filter[kh3 + 1]) + (input_2.r * filter[kh3 + 2]);
                g = (input_0.g * filter[kh3]) + (input_1.g * filter[kh3 + 1]) + (input_2.g * filter[kh3 + 2]);
                b = (input_0.b * filter[kh3]) + (input_1.b * filter[kh3 + 1]) + (input_2.b * filter[kh3 + 2]);
                int output_idx = (row *(width-2)) + col - (kh - 3 + 2)*(width - 2) - (width-2);
                
                if ((row == 0 && (kh == 2 || kh == 1)) || (row == 1 && kh == 2) || (row == (width-1) && (kh == 0 || kh == 1)) || (row == (width-2) && kh == 0)) {
                    continue;
                }
                else {
                    output[output_idx].r += r;
                    output[output_idx].g += g;
                    output[output_idx].b += b;
                }
            }
        }
    }
}


void add_padding(Pixel *original, int rows, int cols, int padding, Pixel *padded) {
    int padded_rows = rows + 2 * padding;
    int padded_cols = cols + 2 * padding;

    for (int i = 0; i < padded_rows; ++i) {
        for (int j = 0; j < padded_cols; ++j) {
            if ((i >= padding) && (i < rows + padding) && (j >= padding) && (j < cols + padding)) {
                int original_row = i - padding;
                int original_col = j - padding;
                int pad_idx = i * padded_cols + j;
                int ori_idx = original_row * cols + original_col;
                padded[pad_idx].r = original[ori_idx].r;
                padded[pad_idx].g = original[ori_idx].g;
                padded[pad_idx].b = original[ori_idx].b;
            }
        }
    }
}


void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    //zero padding
    int new_width = width + 2;
    int new_height = height + 2;
    Pixel* padd_image = (Pixel*)calloc(new_width * new_height, sizeof(Pixel));
    add_padding(input, height, width, 1, padd_image);


    Pixel_double* output_double = (Pixel_double*)calloc(width * height, sizeof(Pixel_double));
    convolution(padd_image, output_double, new_width, new_height, filter);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int idx = j + i*width;
            output_double[idx].r = output_double[idx].r < 0 ? 0 : output_double[idx].r > 255 ? 255 : output_double[idx].r;
            output_double[idx].g = output_double[idx].g < 0 ? 0 : output_double[idx].g > 255 ? 255 : output_double[idx].g;
            output_double[idx].b = output_double[idx].b < 0 ? 0 : output_double[idx].b > 255 ? 255 : output_double[idx].b;
            output[idx].r = (unsigned char)output_double[idx].r;
            output[idx].g = (unsigned char)output_double[idx].g;
            output[idx].b = (unsigned char)output_double[idx].b;
        }
    }

    free(padd_image);
    free(output_double);
}