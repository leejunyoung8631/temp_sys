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
static Pixel convolution_edge(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dy = -1; dy < 2; ++dy){
        for (int dx = -1; dx < 2; ++dx){
            if ((y + dy) < 0 || (y + dy) >= height)
                continue;

            if ((x + dx) < 0 || (x + dx) >= width)
                continue;

            r += input[(x+dx)+(y+dy)*width].r * filter[(dx+1)+(dy+1)*3];
            g += input[(x+dx)+(y+dy)*width].g * filter[(dx+1)+(dy+1)*3];
            b += input[(x+dx)+(y+dy)*width].b * filter[(dx+1)+(dy+1)*3];
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    Pixel p;
    memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}



static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;


    r += input[(x-1)+(y-1)*width].r * filter[(0)+(0)*3];
    g += input[(x-1)+(y-1)*width].g * filter[(0)+(0)*3];
    b += input[(x-1)+(y-1)*width].b * filter[(0)+(0)*3];

    r += input[(x)+(y-1)*width].r * filter[(1)+(0)*3];
    g += input[(x)+(y-1)*width].g * filter[(1)+(0)*3];
    b += input[(x)+(y-1)*width].b * filter[(1)+(0)*3];

    r += input[(x+1)+(y-1)*width].r * filter[(2)+(0)*3];
    g += input[(x+1)+(y-1)*width].g * filter[(2)+(0)*3];
    b += input[(x+1)+(y-1)*width].b * filter[(2)+(0)*3];

    r += input[(x-1)+(y)*width].r * filter[(0)+(1)*3];
    g += input[(x-1)+(y)*width].g * filter[(0)+(1)*3];
    b += input[(x-1)+(y)*width].b * filter[(0)+(1)*3];

    r += input[(x)+(y)*width].r * filter[(1)+(1)*3];
    g += input[(x)+(y)*width].g * filter[(1)+(1)*3];
    b += input[(x)+(y)*width].b * filter[(1)+(1)*3];

    r += input[(x+1)+(y)*width].r * filter[(2)+(1)*3];
    g += input[(x+1)+(y)*width].g * filter[(2)+(1)*3];
    b += input[(x+1)+(y)*width].b * filter[(2)+(1)*3];

    r += input[(x-1)+(y+1)*width].r * filter[(0)+(2)*3];
    g += input[(x-1)+(y+1)*width].g * filter[(0)+(2)*3];
    b += input[(x-1)+(y+1)*width].b * filter[(0)+(2)*3];

    r += input[(x)+(y+1)*width].r * filter[(1)+(2)*3];
    g += input[(x)+(y+1)*width].g * filter[(1)+(2)*3];
    b += input[(x)+(y+1)*width].b * filter[(1)+(2)*3];

    r += input[(x+1)+(y+1)*width].r * filter[(2)+(2)*3];
    g += input[(x+1)+(y+1)*width].g * filter[(2)+(2)*3];
    b += input[(x+1)+(y+1)*width].b * filter[(2)+(2)*3];


    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    memset(&p, 0, sizeof(p));

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

    Pixel* p = (Pixel*)malloc(sizeof(Pixel));
    for(int y=0;y<2;++y) {

        for (int x = 0; x < width; x += 32) {
            *p = convolution_edge(input, x, y, width, height, filter);

            output[x + y * width].r = p->r;
            output[x + y * width].g = p->g;
            output[x + y * width].b = p->b;

            *p = convolution_edge(input, x + 1, y, width, height, filter);

            output[(x + 1) + y * width].r = p->r;
            output[(x + 1) + y * width].g = p->g;
            output[(x + 1) + y * width].b = p->b;

            *p = convolution_edge(input, x + 2, y, width, height, filter);

            output[(x + 2) + y * width].r = p->r;
            output[(x + 2) + y * width].g = p->g;
            output[(x + 2) + y * width].b = p->b;

            *p = convolution_edge(input, x + 3, y, width, height, filter);

            output[(x + 3) + y * width].r = p->r;
            output[(x + 3) + y * width].g = p->g;
            output[(x + 3) + y * width].b = p->b;


            *p = convolution_edge(input, x + 4, y, width, height, filter);

            output[(x + 4) + y * width].r = p->r;
            output[(x + 4) + y * width].g = p->g;
            output[(x + 4) + y * width].b = p->b;

            *p = convolution_edge(input, x + 5, y, width, height, filter);

            output[(x + 5) + y * width].r = p->r;
            output[(x + 5) + y * width].g = p->g;
            output[(x + 5) + y * width].b = p->b;

            *p = convolution_edge(input, x + 6, y, width, height, filter);

            output[(x + 6) + y * width].r = p->r;
            output[(x + 6) + y * width].g = p->g;
            output[(x + 6) + y * width].b = p->b;

            *p = convolution_edge(input, x + 7, y, width, height, filter);

            output[(x + 7) + y * width].r = p->r;
            output[(x + 7) + y * width].g = p->g;
            output[(x + 7) + y * width].b = p->b;

            *p = convolution_edge(input, x + 8, y, width, height, filter);

            output[(x + 8) + y * width].r = p->r;
            output[(x + 8) + y * width].g = p->g;
            output[(x + 8) + y * width].b = p->b;

            *p = convolution_edge(input, x + 9, y, width, height, filter);

            output[(x + 9) + y * width].r = p->r;
            output[(x + 9) + y * width].g = p->g;
            output[(x + 9) + y * width].b = p->b;

            *p = convolution_edge(input, x + 10, y, width, height, filter);

            output[(x + 10) + y * width].r = p->r;
            output[(x + 10) + y * width].g = p->g;
            output[(x + 10) + y * width].b = p->b;

            *p = convolution_edge(input, x + 11, y, width, height, filter);

            output[(x + 11) + y * width].r = p->r;
            output[(x + 11) + y * width].g = p->g;
            output[(x + 11) + y * width].b = p->b;

            *p = convolution_edge(input, x + 12, y, width, height, filter);

            output[(x + 12) + y * width].r = p->r;
            output[(x + 12) + y * width].g = p->g;
            output[(x + 12) + y * width].b = p->b;

            *p = convolution_edge(input, x + 13, y, width, height, filter);

            output[(x + 13) + y * width].r = p->r;
            output[(x + 13) + y * width].g = p->g;
            output[(x + 13) + y * width].b = p->b;

            *p = convolution_edge(input, x + 14, y, width, height, filter);

            output[(x + 14) + y * width].r = p->r;
            output[(x + 14) + y * width].g = p->g;
            output[(x + 14) + y * width].b = p->b;

            *p = convolution_edge(input, x + 15, y, width, height, filter);

            output[(x + 15) + y * width].r = p->r;
            output[(x + 15) + y * width].g = p->g;
            output[(x + 15) + y * width].b = p->b;

            *p = convolution_edge(input, x + 16, y, width, height, filter);

            output[(x + 16) + y * width].r = p->r;
            output[(x + 16) + y * width].g = p->g;
            output[(x + 16) + y * width].b = p->b;


            *p = convolution_edge(input, x + 17, y, width, height, filter);

            output[(x + 17) + y * width].r = p->r;
            output[(x + 17) + y * width].g = p->g;
            output[(x + 17) + y * width].b = p->b;

            *p = convolution_edge(input, x + 18, y, width, height, filter);

            output[(x + 18) + y * width].r = p->r;
            output[(x + 18) + y * width].g = p->g;
            output[(x + 18) + y * width].b = p->b;

            *p = convolution_edge(input, x + 19, y, width, height, filter);

            output[(x + 19) + y * width].r = p->r;
            output[(x + 19) + y * width].g = p->g;
            output[(x + 19) + y * width].b = p->b;

            *p = convolution_edge(input, x + 20, y, width, height, filter);

            output[(x + 20) + y * width].r = p->r;
            output[(x + 20) + y * width].g = p->g;
            output[(x + 20) + y * width].b = p->b;

            *p = convolution_edge(input, x + 21, y, width, height, filter);

            output[(x + 21) + y * width].r = p->r;
            output[(x + 21) + y * width].g = p->g;
            output[(x + 21) + y * width].b = p->b;

            *p = convolution_edge(input, x + 22, y, width, height, filter);

            output[(x + 22) + y * width].r = p->r;
            output[(x + 22) + y * width].g = p->g;
            output[(x + 22) + y * width].b = p->b;

            *p = convolution_edge(input, x + 23, y, width, height, filter);

            output[(x + 23) + y * width].r = p->r;
            output[(x + 23) + y * width].g = p->g;
            output[(x + 23) + y * width].b = p->b;

            *p = convolution_edge(input, x + 24, y, width, height, filter);

            output[(x + 24) + y * width].r = p->r;
            output[(x + 24) + y * width].g = p->g;
            output[(x + 24) + y * width].b = p->b;

            *p = convolution_edge(input, x + 25, y, width, height, filter);

            output[(x + 25) + y * width].r = p->r;
            output[(x + 25) + y * width].g = p->g;
            output[(x + 25) + y * width].b = p->b;

            *p = convolution_edge(input, x + 26, y, width, height, filter);

            output[(x + 26) + y * width].r = p->r;
            output[(x + 26) + y * width].g = p->g;
            output[(x + 26) + y * width].b = p->b;

            *p = convolution_edge(input, x + 27, y, width, height, filter);

            output[(x + 27) + y * width].r = p->r;
            output[(x + 27) + y * width].g = p->g;
            output[(x + 27) + y * width].b = p->b;


            *p = convolution_edge(input, x + 28, y, width, height, filter);

            output[(x + 28) + y * width].r = p->r;
            output[(x + 28) + y * width].g = p->g;
            output[(x + 28) + y * width].b = p->b;

            *p = convolution_edge(input, x + 29, y, width, height, filter);

            output[(x + 29) + y * width].r = p->r;
            output[(x + 29) + y * width].g = p->g;
            output[(x + 29) + y * width].b = p->b;

            *p = convolution_edge(input, x + 30, y, width, height, filter);

            output[(x + 30) + y * width].r = p->r;
            output[(x + 30) + y * width].g = p->g;
            output[(x + 30) + y * width].b = p->b;

            *p = convolution_edge(input, x + 31, y, width, height, filter);

            output[(x + 31) + y * width].r = p->r;
            output[(x + 31) + y * width].g = p->g;
            output[(x + 31) + y * width].b = p->b;

        }
    }//up

    for (int y = 2; y < height-2; ++y) {

        *p = convolution_edge(input, 0, y, width, height, filter);

        output[0+y*width].r = p->r;
        output[0+y*width].g = p->g;
        output[0+y*width].b = p->b;

        *p = convolution_edge(input, 1, y, width, height, filter);

        output[(1)+y*width].r = p->r;
        output[(1)+y*width].g = p->g;
        output[(1)+y*width].b = p->b;

        *p = convolution_edge(input, 2, y, width, height, filter);

        output[(2)+y*width].r = p->r;
        output[(2)+y*width].g = p->g;
        output[(2)+y*width].b = p->b;

        *p = convolution(input, 3, y, width, height, filter);

        output[(3)+y*width].r = p->r;
        output[(3)+y*width].g = p->g;
        output[(3)+y*width].b = p->b;


        *p = convolution(input, 4, y, width, height, filter);

        output[(4)+y*width].r = p->r;
        output[(4)+y*width].g = p->g;
        output[(4)+y*width].b = p->b;

        *p = convolution(input, 5, y, width, height, filter);

        output[(5)+y*width].r = p->r;
        output[(5)+y*width].g = p->g;
        output[(5)+y*width].b = p->b;

        *p = convolution(input, 6, y, width, height, filter);

        output[(6)+y*width].r = p->r;
        output[(6)+y*width].g = p->g;
        output[(6)+y*width].b = p->b;

        *p = convolution(input, 7, y, width, height, filter);

        output[(7)+y*width].r = p->r;
        output[(7)+y*width].g = p->g;
        output[(7)+y*width].b = p->b;

        *p = convolution(input, 8, y, width, height, filter);

        output[(8)+y*width].r = p->r;
        output[(8)+y*width].g = p->g;
        output[(8)+y*width].b = p->b;

        *p = convolution(input, 9, y, width, height, filter);

        output[(9)+y*width].r = p->r;
        output[(9)+y*width].g = p->g;
        output[(9)+y*width].b = p->b;

        *p = convolution(input, 10, y, width, height, filter);

        output[(10)+y*width].r = p->r;
        output[(10)+y*width].g = p->g;
        output[(10)+y*width].b = p->b;

        *p = convolution(input, 11, y, width, height, filter);

        output[(11)+y*width].r = p->r;
        output[(11)+y*width].g = p->g;
        output[(11)+y*width].b = p->b;

        *p = convolution(input, 12, y, width, height, filter);

        output[(12)+y*width].r = p->r;
        output[(12)+y*width].g = p->g;
        output[(12)+y*width].b = p->b;

        *p = convolution(input, 13, y, width, height, filter);

        output[(13)+y*width].r = p->r;
        output[(13)+y*width].g = p->g;
        output[(13)+y*width].b = p->b;

        *p = convolution(input, 14, y, width, height, filter);

        output[(14)+y*width].r = p->r;
        output[(14)+y*width].g = p->g;
        output[(14)+y*width].b = p->b;

        *p = convolution(input, 15, y, width, height, filter);

        output[(15)+y*width].r = p->r;
        output[(15)+y*width].g = p->g;
        output[(15)+y*width].b = p->b;


        for (int x = 16; x < width-16; x+=32) {

            *p = convolution(input, x, y, width, height, filter);

            output[x+y*width].r = p->r;
            output[x+y*width].g = p->g;
            output[x+y*width].b = p->b;

            *p = convolution(input, x+1, y, width, height, filter);

            output[(x+1)+y*width].r = p->r;
            output[(x+1)+y*width].g = p->g;
            output[(x+1)+y*width].b = p->b;

            *p = convolution(input, x+2, y, width, height, filter);

            output[(x+2)+y*width].r = p->r;
            output[(x+2)+y*width].g = p->g;
            output[(x+2)+y*width].b = p->b;

            *p = convolution(input, x+3, y, width, height, filter);

            output[(x+3)+y*width].r = p->r;
            output[(x+3)+y*width].g = p->g;
            output[(x+3)+y*width].b = p->b;


            *p = convolution(input, x+4, y, width, height, filter);

            output[(x+4)+y*width].r = p->r;
            output[(x+4)+y*width].g = p->g;
            output[(x+4)+y*width].b = p->b;

            *p = convolution(input, x+5, y, width, height, filter);

            output[(x+5)+y*width].r = p->r;
            output[(x+5)+y*width].g = p->g;
            output[(x+5)+y*width].b = p->b;

            *p = convolution(input, x+6, y, width, height, filter);

            output[(x+6)+y*width].r = p->r;
            output[(x+6)+y*width].g = p->g;
            output[(x+6)+y*width].b = p->b;

            *p = convolution(input, x+7, y, width, height, filter);

            output[(x+7)+y*width].r = p->r;
            output[(x+7)+y*width].g = p->g;
            output[(x+7)+y*width].b = p->b;

            *p = convolution(input, x+8, y, width, height, filter);

            output[(x+8)+y*width].r = p->r;
            output[(x+8)+y*width].g = p->g;
            output[(x+8)+y*width].b = p->b;

            *p = convolution(input, x+9, y, width, height, filter);

            output[(x+9)+y*width].r = p->r;
            output[(x+9)+y*width].g = p->g;
            output[(x+9)+y*width].b = p->b;

            *p = convolution(input, x+10, y, width, height, filter);

            output[(x+10)+y*width].r = p->r;
            output[(x+10)+y*width].g = p->g;
            output[(x+10)+y*width].b = p->b;

            *p = convolution(input, x+11, y, width, height, filter);

            output[(x+11)+y*width].r = p->r;
            output[(x+11)+y*width].g = p->g;
            output[(x+11)+y*width].b = p->b;

            *p = convolution(input, x+12, y, width, height, filter);

            output[(x+12)+y*width].r = p->r;
            output[(x+12)+y*width].g = p->g;
            output[(x+12)+y*width].b = p->b;

            *p = convolution(input, x+13, y, width, height, filter);

            output[(x+13)+y*width].r = p->r;
            output[(x+13)+y*width].g = p->g;
            output[(x+13)+y*width].b = p->b;

            *p = convolution(input, x+14, y, width, height, filter);

            output[(x+14)+y*width].r = p->r;
            output[(x+14)+y*width].g = p->g;
            output[(x+14)+y*width].b = p->b;

            *p = convolution(input, x+15, y, width, height, filter);

            output[(x+15)+y*width].r = p->r;
            output[(x+15)+y*width].g = p->g;
            output[(x+15)+y*width].b = p->b;

            *p = convolution(input, x+16, y, width, height, filter);

            output[(x+16)+y*width].r = p->r;
            output[(x+16)+y*width].g = p->g;
            output[(x+16)+y*width].b = p->b;

            *p = convolution(input, x+17, y, width, height, filter);

            output[(x+17)+y*width].r = p->r;
            output[(x+17)+y*width].g = p->g;
            output[(x+17)+y*width].b = p->b;

            *p = convolution(input, x+18, y, width, height, filter);

            output[(x+18)+y*width].r = p->r;
            output[(x+18)+y*width].g = p->g;
            output[(x+18)+y*width].b = p->b;

            *p = convolution(input, x+19, y, width, height, filter);

            output[(x+19)+y*width].r = p->r;
            output[(x+19)+y*width].g = p->g;
            output[(x+19)+y*width].b = p->b;

            *p = convolution(input, x+20, y, width, height, filter);

            output[(x+20)+y*width].r = p->r;
            output[(x+20)+y*width].g = p->g;
            output[(x+20)+y*width].b = p->b;

            *p = convolution(input, x+21, y, width, height, filter);

            output[(x+21)+y*width].r = p->r;
            output[(x+21)+y*width].g = p->g;
            output[(x+21)+y*width].b = p->b;

            *p = convolution(input, x+22, y, width, height, filter);

            output[(x+22)+y*width].r = p->r;
            output[(x+22)+y*width].g = p->g;
            output[(x+22)+y*width].b = p->b;

            *p = convolution(input, x+23, y, width, height, filter);

            output[(x+23)+y*width].r = p->r;
            output[(x+23)+y*width].g = p->g;
            output[(x+23)+y*width].b = p->b;

            *p = convolution(input, x+24, y, width, height, filter);

            output[(x+24)+y*width].r = p->r;
            output[(x+24)+y*width].g = p->g;
            output[(x+24)+y*width].b = p->b;

            *p = convolution(input, x+25, y, width, height, filter);

            output[(x+25)+y*width].r = p->r;
            output[(x+25)+y*width].g = p->g;
            output[(x+25)+y*width].b = p->b;

            *p = convolution(input, x+26, y, width, height, filter);

            output[(x+26)+y*width].r = p->r;
            output[(x+26)+y*width].g = p->g;
            output[(x+26)+y*width].b = p->b;

            *p = convolution(input, x+27, y, width, height, filter);

            output[(x+27)+y*width].r = p->r;
            output[(x+27)+y*width].g = p->g;
            output[(x+27)+y*width].b = p->b;


            *p = convolution(input, x+28, y, width, height, filter);

            output[(x+28)+y*width].r = p->r;
            output[(x+28)+y*width].g = p->g;
            output[(x+28)+y*width].b = p->b;

            *p = convolution(input, x+29, y, width, height, filter);

            output[(x+29)+y*width].r = p->r;
            output[(x+29)+y*width].g = p->g;
            output[(x+29)+y*width].b = p->b;

            *p = convolution(input, x+30, y, width, height, filter);

            output[(x+30)+y*width].r = p->r;
            output[(x+30)+y*width].g = p->g;
            output[(x+30)+y*width].b = p->b;

            *p = convolution(input, x+31, y, width, height, filter);

            output[(x+31)+y*width].r = p->r;
            output[(x+31)+y*width].g = p->g;
            output[(x+31)+y*width].b = p->b;


            }



        *p = convolution_edge(input, width-1, y, width, height, filter);

        output[(width-1)+y*width].r = p->r;
        output[(width-1)+y*width].g = p->g;
        output[(width-1)+y*width].b = p->b;

        *p = convolution_edge(input, width-2, y, width, height, filter);

        output[(width-2)+y*width].r = p->r;
        output[(width-2)+y*width].g = p->g;
        output[(width-2)+y*width].b = p->b;

        *p = convolution(input, width-3, y, width, height, filter);

        output[(width-3)+y*width].r = p->r;
        output[(width-3)+y*width].g = p->g;
        output[(width-3)+y*width].b = p->b;


        *p = convolution(input, width-4, y, width, height, filter);

        output[(width-4)+y*width].r = p->r;
        output[(width-4)+y*width].g = p->g;
        output[(width-4)+y*width].b = p->b;

        *p = convolution(input, width-5, y, width, height, filter);

        output[(width-5)+y*width].r = p->r;
        output[(width-5)+y*width].g = p->g;
        output[(width-5)+y*width].b = p->b;

        *p = convolution(input, width-6, y, width, height, filter);

        output[(width-6)+y*width].r = p->r;
        output[(width-6)+y*width].g = p->g;
        output[(width-6)+y*width].b = p->b;

        *p = convolution(input, width-7, y, width, height, filter);

        output[(width-7)+y*width].r = p->r;
        output[(width-7)+y*width].g = p->g;
        output[(width-7)+y*width].b = p->b;

        *p = convolution(input, width-8, y, width, height, filter);

        output[(width-8)+y*width].r = p->r;
        output[(width-8)+y*width].g = p->g;
        output[(width-8)+y*width].b = p->b;

        *p = convolution(input, width-9, y, width, height, filter);

        output[(width-9)+y*width].r = p->r;
        output[(width-9)+y*width].g = p->g;
        output[(width-9)+y*width].b = p->b;

        *p = convolution(input, width-10, y, width, height, filter);

        output[(width-10)+y*width].r = p->r;
        output[(width-10)+y*width].g = p->g;
        output[(width-10)+y*width].b = p->b;

        *p = convolution(input, width-11, y, width, height, filter);

        output[(width-11)+y*width].r = p->r;
        output[(width-11)+y*width].g = p->g;
        output[(width-11)+y*width].b = p->b;

        *p = convolution(input, width-12, y, width, height, filter);

        output[(width-12)+y*width].r = p->r;
        output[(width-12)+y*width].g = p->g;
        output[(width-12)+y*width].b = p->b;

        *p = convolution(input, width-13, y, width, height, filter);

        output[(width-13)+y*width].r = p->r;
        output[(width-13)+y*width].g = p->g;
        output[(width-13)+y*width].b = p->b;

        *p = convolution(input, width-14, y, width, height, filter);

        output[(width-14)+y*width].r = p->r;
        output[(width-14)+y*width].g = p->g;
        output[(width-14)+y*width].b = p->b;

        *p = convolution(input, width-15, y, width, height, filter);

        output[(width-15)+y*width].r = p->r;
        output[(width-15)+y*width].g = p->g;
        output[(width-15)+y*width].b = p->b;

        *p = convolution(input, width-16, y, width, height, filter);

        output[(width-16)+y*width].r = p->r;
        output[(width-16)+y*width].g = p->g;
        output[(width-16)+y*width].b = p->b;





    }//middle

    for(int y=height-2;y<height;++y) {

        for (int x = 0; x < width; x += 32) {
            *p = convolution_edge(input, x, y, width, height, filter);

            output[x + y * width].r = p->r;
            output[x + y * width].g = p->g;
            output[x + y * width].b = p->b;

            *p = convolution_edge(input, x + 1, y, width, height, filter);

            output[(x + 1) + y * width].r = p->r;
            output[(x + 1) + y * width].g = p->g;
            output[(x + 1) + y * width].b = p->b;

            *p = convolution_edge(input, x + 2, y, width, height, filter);

            output[(x + 2) + y * width].r = p->r;
            output[(x + 2) + y * width].g = p->g;
            output[(x + 2) + y * width].b = p->b;

            *p = convolution_edge(input, x + 3, y, width, height, filter);

            output[(x + 3) + y * width].r = p->r;
            output[(x + 3) + y * width].g = p->g;
            output[(x + 3) + y * width].b = p->b;


            *p = convolution_edge(input, x + 4, y, width, height, filter);

            output[(x + 4) + y * width].r = p->r;
            output[(x + 4) + y * width].g = p->g;
            output[(x + 4) + y * width].b = p->b;

            *p = convolution_edge(input, x + 5, y, width, height, filter);

            output[(x + 5) + y * width].r = p->r;
            output[(x + 5) + y * width].g = p->g;
            output[(x + 5) + y * width].b = p->b;

            *p = convolution_edge(input, x + 6, y, width, height, filter);

            output[(x + 6) + y * width].r = p->r;
            output[(x + 6) + y * width].g = p->g;
            output[(x + 6) + y * width].b = p->b;

            *p = convolution_edge(input, x + 7, y, width, height, filter);

            output[(x + 7) + y * width].r = p->r;
            output[(x + 7) + y * width].g = p->g;
            output[(x + 7) + y * width].b = p->b;

            *p = convolution_edge(input, x + 8, y, width, height, filter);

            output[(x + 8) + y * width].r = p->r;
            output[(x + 8) + y * width].g = p->g;
            output[(x + 8) + y * width].b = p->b;

            *p = convolution_edge(input, x + 9, y, width, height, filter);

            output[(x + 9) + y * width].r = p->r;
            output[(x + 9) + y * width].g = p->g;
            output[(x + 9) + y * width].b = p->b;

            *p = convolution_edge(input, x + 10, y, width, height, filter);

            output[(x + 10) + y * width].r = p->r;
            output[(x + 10) + y * width].g = p->g;
            output[(x + 10) + y * width].b = p->b;

            *p = convolution_edge(input, x + 11, y, width, height, filter);

            output[(x + 11) + y * width].r = p->r;
            output[(x + 11) + y * width].g = p->g;
            output[(x + 11) + y * width].b = p->b;

            *p = convolution_edge(input, x + 12, y, width, height, filter);

            output[(x + 12) + y * width].r = p->r;
            output[(x + 12) + y * width].g = p->g;
            output[(x + 12) + y * width].b = p->b;

            *p = convolution_edge(input, x + 13, y, width, height, filter);

            output[(x + 13) + y * width].r = p->r;
            output[(x + 13) + y * width].g = p->g;
            output[(x + 13) + y * width].b = p->b;

            *p = convolution_edge(input, x + 14, y, width, height, filter);

            output[(x + 14) + y * width].r = p->r;
            output[(x + 14) + y * width].g = p->g;
            output[(x + 14) + y * width].b = p->b;

            *p = convolution_edge(input, x + 15, y, width, height, filter);

            output[(x + 15) + y * width].r = p->r;
            output[(x + 15) + y * width].g = p->g;
            output[(x + 15) + y * width].b = p->b;

            *p = convolution_edge(input, x + 16, y, width, height, filter);

            output[(x + 16) + y * width].r = p->r;
            output[(x + 16) + y * width].g = p->g;
            output[(x + 16) + y * width].b = p->b;


            *p = convolution_edge(input, x + 17, y, width, height, filter);

            output[(x + 17) + y * width].r = p->r;
            output[(x + 17) + y * width].g = p->g;
            output[(x + 17) + y * width].b = p->b;

            *p = convolution_edge(input, x + 18, y, width, height, filter);

            output[(x + 18) + y * width].r = p->r;
            output[(x + 18) + y * width].g = p->g;
            output[(x + 18) + y * width].b = p->b;

            *p = convolution_edge(input, x + 19, y, width, height, filter);

            output[(x + 19) + y * width].r = p->r;
            output[(x + 19) + y * width].g = p->g;
            output[(x + 19) + y * width].b = p->b;

            *p = convolution_edge(input, x + 20, y, width, height, filter);

            output[(x + 20) + y * width].r = p->r;
            output[(x + 20) + y * width].g = p->g;
            output[(x + 20) + y * width].b = p->b;

            *p = convolution_edge(input, x + 21, y, width, height, filter);

            output[(x + 21) + y * width].r = p->r;
            output[(x + 21) + y * width].g = p->g;
            output[(x + 21) + y * width].b = p->b;

            *p = convolution_edge(input, x + 22, y, width, height, filter);

            output[(x + 22) + y * width].r = p->r;
            output[(x + 22) + y * width].g = p->g;
            output[(x + 22) + y * width].b = p->b;

            *p = convolution_edge(input, x + 23, y, width, height, filter);

            output[(x + 23) + y * width].r = p->r;
            output[(x + 23) + y * width].g = p->g;
            output[(x + 23) + y * width].b = p->b;

            *p = convolution_edge(input, x + 24, y, width, height, filter);

            output[(x + 24) + y * width].r = p->r;
            output[(x + 24) + y * width].g = p->g;
            output[(x + 24) + y * width].b = p->b;

            *p = convolution_edge(input, x + 25, y, width, height, filter);

            output[(x + 25) + y * width].r = p->r;
            output[(x + 25) + y * width].g = p->g;
            output[(x + 25) + y * width].b = p->b;

            *p = convolution_edge(input, x + 26, y, width, height, filter);

            output[(x + 26) + y * width].r = p->r;
            output[(x + 26) + y * width].g = p->g;
            output[(x + 26) + y * width].b = p->b;

            *p = convolution_edge(input, x + 27, y, width, height, filter);

            output[(x + 27) + y * width].r = p->r;
            output[(x + 27) + y * width].g = p->g;
            output[(x + 27) + y * width].b = p->b;


            *p = convolution_edge(input, x + 28, y, width, height, filter);

            output[(x + 28) + y * width].r = p->r;
            output[(x + 28) + y * width].g = p->g;
            output[(x + 28) + y * width].b = p->b;

            *p = convolution_edge(input, x + 29, y, width, height, filter);

            output[(x + 29) + y * width].r = p->r;
            output[(x + 29) + y * width].g = p->g;
            output[(x + 29) + y * width].b = p->b;

            *p = convolution_edge(input, x + 30, y, width, height, filter);

            output[(x + 30) + y * width].r = p->r;
            output[(x + 30) + y * width].g = p->g;
            output[(x + 30) + y * width].b = p->b;

            *p = convolution_edge(input, x + 31, y, width, height, filter);

            output[(x + 31) + y * width].r = p->r;
            output[(x + 31) + y * width].g = p->g;
            output[(x + 31) + y * width].b = p->b;

        }
    }//down

    free(p);



}