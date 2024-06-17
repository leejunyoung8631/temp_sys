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
#define BLOCK_SIZE 128


void filter_optimized(void* args[]) {
	unsigned int width = *(unsigned int*)args[0];
	unsigned int height = *(unsigned int*)args[1];
	Pixel* input = args[2];
	Pixel* output = args[3];
	float* filter = args[4];

	Pixel* temp_output = (Pixel*)malloc(width * height * sizeof(Pixel));
	if (temp_output == NULL) {
		fprintf(stderr, "Failed to allocate memory for temporary output.\n");
		return;
	}

	for (int by = 0; by < height; by += BLOCK_SIZE) {
		for (int bx = 0; bx < width; bx += BLOCK_SIZE) {
			int block_width = (bx + BLOCK_SIZE > width) ? width - bx : BLOCK_SIZE;
			int block_height = (by + BLOCK_SIZE > height) ? height - by : BLOCK_SIZE;

			for (int y = by; y < by + block_height; ++y) {
				Pixel* output_row = &temp_output[y*width];
				for (int x = bx; x < bx + block_width; ++x) {
                    double r = 0;
                    double g = 0;
                    double b = 0;

                    int a1 = x-1+(y-1)*width;
                    int a2 = x+(y-1)*width;
                    int a3 = x+1+(y-1)*width;
                    int a4 = x-1+(y*width);
                    int a5 = x+(y*width);
                    int a6 = x+1+(y*width);
                    int a7 = x-1+((y+1)*width);
                    int a8 = x+((y+1)*width);
                    int a9 = x+1+((y+1)*width);
                    
                    int al[9] = {a1, a2, a3, a4, a5, a6, a7, a8, a9};  // a list
                    int bd[9] = {0,0,0,0,0,0,0,0,0};  // boundary list(경계조건 확인용)

                    if (x-1 < 0) {
                        bd[0] = 1;
                        bd[3] = 1;
                        bd[6] = 1;
                    } else if (x+1 >= width) {
                        bd[2] = 1;
                        bd[5] = 1;
                        bd[8] = 1;
                    }
                    if (y-1 < 0) {
                        bd[0] = 1;
                        bd[1] = 1;
                        bd[2] = 1;
                    } else if (y+1 >= height) {
                        bd[6] = 1;
                        bd[7] = 1;
                        bd[8] = 1;
                    }

                    for (int i = 0; i < 9; ++i) {
                        if (bd[i]) {
                            continue;
                        }
                        Pixel ip = input[al[i]];
                        float f = filter[i];
                        r += ip.r * f;
                        g += ip.g * f;
                        b += ip.b * f;
                    }

                    if (r < 0) r = 0;
                    if (g < 0) g = 0;
                    if (b < 0) b = 0;

                    if (r > 255) r = 255;
                    if (g > 255) g = 255;
                    if (b > 255) b = 255;


                    Pixel p = { .r = (unsigned char)r, .g = (unsigned char)g, .b = (unsigned char)b };
					output_row[x] = p;
				}
			}
		}
	}
	memcpy(output, temp_output, width * height * sizeof(Pixel));
	free(temp_output);
}