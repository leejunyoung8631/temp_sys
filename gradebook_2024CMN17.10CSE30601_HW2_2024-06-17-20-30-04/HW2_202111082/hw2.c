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


__inline static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    float r = 0;
    float g = 0;
    float b = 0;
    
    int a;
    //Pixel *input1;
    int ym = y-1;
    int ya = y+1;
    int xm = x-1;
    int xa = x+1;
    int bb;
    float fil;

    if (ym >= 0){
        bb= ym*width;
        if (xm >= 0){
            a = bb + xm;
            fil = filter[0];
            //input1 = &input[a];
            r += input[a].r *fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
            }
            a = bb + x;
            fil = filter[1];
            //input1 = &input[a];
            //r += input1->r * filter[1];
            //g += input1->g * filter[1];
            //b += input1->b * filter[1];
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
        if (xa < width){
            a = bb+ xa;
            fil = filter[2];
            //input1 = &input[a];
            //r += input1->r * filter[2];
            //g += input1->g * filter[2];
            //b += input1->b * filter[2];
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
            }
        }
            
        bb= y*width;
        fil = filter[3];
        if (xm >= 0){
            a = bb + xm;
        //input1 = &input[a];
        //r += input1->r * filter[3];
        //g += input1->g * filter[3];
        //b += input1->b * filter[3];
        r += input[a].r * fil;
        g += input[a].g * fil;
        b += input[a].b * fil;
            }
            a = bb + x;
            fil = filter[4];
            //input1 = &input[a];
            //r += input1->r * filter[4];
            //g += input1->g * filter[4];
            //b += input1->b * filter[4];
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
        if (xa < width){
            a = bb + xa;
            fil = filter[5];
            //input1 = &input[a];
            //r += input1->r * filter[5];
            //g += input1->g * filter[5];
            //b += input1->b * filter[5];
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
            }

            
    if (ya< height){
        bb= ya*width;
        fil = filter[6];
        if (xm >= 0 ){
            a = bb + xm;
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
            }
            a = bb + x;
            fil = filter[7];
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
        if (xa < width){
            a = bb + xa;
            fil = filter[8];
            r += input[a].r * fil;
            g += input[a].g * fil;
            b += input[a].b * fil;
            }
        }

    if (r > 255) r = 255;
    else if (r < 0) r = 0;
    if (g > 255) g = 255;
    else if (g < 0) g = 0;
    if (b > 255) b = 255;
    else if (b < 0) b = 0;

    
    Pixel p;
    memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

__inline void filter_optimized(void* args[]) {
    int width = *(unsigned int*)args[0];
    int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    
    Pixel* p = (Pixel*)malloc(sizeof(Pixel));
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            *p = convolution(input, x, y, width, height, filter);
            
            int xyw = x+(y*width);
            unsigned char  pr = p->r;
            unsigned char  pg = p->g;
            unsigned char  pb = p->b;
            output[xyw].r = pr;
            output[xyw].g = pg;
            output[xyw].b = pb;
            
            //Pixel *xyw = &output[x+y*width];
            //xyw->r = p->r;
            //xyw->g = p->g;
            //xyw->b = p->b;

        }
    }
    free(p);
}

