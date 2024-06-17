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
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];


    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0;
            float g = 0;
            float b = 0;
            
            int idx = x + y * width;
            int yy = y - 1;
            
            if (!(yy < 0 || yy > height - 1)){
                int xx = x - 2;
                xx++;
                
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx - 1 - width];
                    float fil = filter[0];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
        
                xx++;
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx - width];
                    float fil = filter[1];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
        
                xx++;
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx + (1 - width)];
                    float fil = filter[2];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
            }
            yy++;
            if (!(yy < 0 || yy > height - 1)){
                int xx = x - 2;
                xx++;
                
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx - 1];
                    float fil = filter[3];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
        
                xx++;
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx];
                    float fil = filter[4];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
        
                xx++;
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx + 1];
                    float fil = filter[5];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
            }
            yy++;
            if (!(yy < 0 || yy > height - 1)){
                int xx = x - 2;
                xx++;
                
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx - 1 + width];
                    float fil = filter[6];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
        
                xx++;
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx + width];
                    float fil = filter[7];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
        
                xx++;
                if (!(xx < 0 || xx > width - 1)){
                    Pixel in = input[idx + (1 + width)];
                    float fil = filter[8];

                    r += in.r * fil;
                    g += in.g * fil;
                    b += in.b * fil;
                }
            }

            Pixel p;

            p.r = r < 0 ? (unsigned char) 0 : (r > 255 ? (unsigned char) 255 : (unsigned char) r);
            p.g = g < 0 ? (unsigned char) 0 : (g > 255 ? (unsigned char) 255 : (unsigned char) g);
            p.b = b < 0 ? (unsigned char) 0 : (b > 255 ? (unsigned char) 255 : (unsigned char) b);
            output[idx] = p;
        }
    }
}
