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


//3
inline static Pixel convolution(const Pixel* input, int x, int y, const int width, const int height, const float* filter, const char boundary) { 
    int r=0;
    int g=0;
    int b=0;
    
    if (!boundary) { 
        const Pixel* p0 = input + (y - 1) * width + (x - 1);
        const Pixel* p1=p0+1;
        const Pixel* p2=p0+2;
        const Pixel* p3=p0+width;
        const Pixel* p4=p0+width+1;
        const Pixel* p5=p0+width+2;
        const Pixel* p6=p0+2*width;
        const Pixel* p7=p0+2*width+1;
        const Pixel* p8=p0+2*width+2;
        
        r+=p0->r*filter[0];
        g+=p0->g*filter[0];
        b+=p0->b*filter[0];
        r+=p1->r*filter[1];
        g+=p1->g*filter[1];
        b+=p1->b*filter[1];
        r+=p2->r*filter[2];
        g+=p2->g*filter[2];
        b+=p2->b*filter[2];
        r+=p3->r*filter[3];
        g+=p3->g*filter[3];
        b+=p3->b*filter[3];
        r+=p4->r*filter[4];
        g+=p4->g*filter[4];
        b+=p4->b*filter[4];
        r+=p5->r*filter[5];
        g+=p5->g*filter[5];
        b+=p5->b*filter[5];
        r+=p6->r*filter[6];
        g+=p6->g*filter[6];
        b+=p6->b*filter[6];
        r+=p7->r*filter[7];
        g+=p7->g*filter[7];
        b+=p7->b*filter[7];
        r+=p8->r*filter[8];
        g+=p8->g*filter[8];
        b+=p8->b*filter[8];
        
        
    }
    
    else {
        for (int dy = -1; dy < 2; ++dy) {
            int ydy=y+dy;
            if ((ydy) < 0 || (ydy) >= height)
                    continue;
            int dy3=3*dy;
            const Pixel* p=input+ydy*width;
            for (int dx = -1; dx < 2; ++dx) {
                int xdx=x+dx;
                if ((xdx) < 0 || (xdx) >= width)
                    continue;
                const Pixel* pp=p+xdx;
                int index2=dx+4+dy3;
                r += pp->r * filter[index2];
                g += pp->g * filter[index2];
                b += pp->b * filter[index2];
            }
        }
    }
    
    
        

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p={(unsigned char)r, (unsigned char)g, (unsigned char)b};

    return p;
}

void filter_optimized(void* args[]) {
    const unsigned int width = *(unsigned int*)args[0];
    const unsigned int height = *(unsigned int*)args[1];
    const Pixel* input = args[2];
    Pixel* output = args[3];
    const float* filter = args[4];
    
    int x=0;
    for (int y = 0; y < height; ++y) {
        const char temp=(y==0||y==height-1);
        for (x=0; x < width-2; x+=3) { //2 : 2.8  //3 : 3.1
            const char boundary1=(temp||x==0)?1:0;
            const char boundary2=temp;
            const char boundary3=(temp||x==width-3)?1:0;
            *output++=convolution(input, x, y, width, height, filter, boundary1);
            *output++=convolution(input, x+1, y, width, height, filter, boundary2);
            *output++=convolution(input, x+2, y, width, height, filter, boundary3);
        }
        for (;x<width;x++){
            const char boundary1=(y==0||y==height-1||x==width-1)?1:0;
            *output++=convolution(input, x, y, width, height, filter, boundary1);
        }
    }
}

