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

static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    
    int r = 0;
	int g = 0;
    int b = 0;
	int m = width >> 5;
	
	
	int ydy = y-1;
	if( ydy >= 0 && ydy < height){

			int xdx = x-1;
			int index1 = xdx+((ydy*m)<<5);
			int index2 = 0;
			int filtervalue = (int)filter[index2];
			if(xdx >=0 && xdx < width){
            	r += (int)input[index1].r *filtervalue;
            	g += (int)input[index1].g *filtervalue;
            	b += (int)input[index1].b *filtervalue;
			}

			xdx = x;
			if(xdx < width){
				index1++;
				index2++;
				filtervalue = (int)filter[index2];
            	r += (int)input[index1].r * filtervalue;
            	g += (int)input[index1].g * filtervalue;
            	b += (int)input[index1].b * filtervalue;
			}

			xdx = x+1;
			if(xdx < width){
				index1 = xdx+((ydy*m)<<5);
				index2 = 2;
				filtervalue = (int)filter[index2];
            	r += (int)input[index1].r * filtervalue;
            	g += (int)input[index1].g * filtervalue;
            	b += (int)input[index1].b * filtervalue;
			}
	}
    
	ydy = y;
	if ( ydy < height) {

			int xdx = x-1;
			int index1 = xdx+((ydy*m)<<5);
			int index2 = 1+(1<<1);
			int filtervalue = (int)filter[index2];
			if(xdx >=0 && xdx < width){
            	r += (int)input[index1].r *filtervalue;
            	g += (int)input[index1].g *filtervalue;
            	b += (int)input[index1].b *filtervalue;
			}

			xdx = x;
			if(xdx < width){
				index1++;
				index2++;
				filtervalue = (int)filter[index2];
            	r += (int)input[index1].r * filtervalue;
            	g += (int)input[index1].g * filtervalue;
            	b += (int)input[index1].b * filtervalue;
			}

			xdx = x+1;
			if(xdx < width){
				index1 = xdx+((ydy*m)<<5);
				index2 = 3+(1<<1);
				filtervalue = (int)filter[index2];
            	r += (int)input[index1].r * filtervalue;
            	g += (int)input[index1].g * filtervalue;
            	b += (int)input[index1].b * filtervalue;
			}
	}


	ydy = y+1;
	if ( ydy < height) {

			int xdx = x-1;
			int index1 = xdx+((ydy*m)<<5);
			int index2 = 2+(2<<1);
			int filtervalue = (int)filter[index2];
			if(xdx >=0 && xdx < width){
            	r += (int)input[index1].r *filtervalue;
            	g += (int)input[index1].g *filtervalue;
            	b += (int)input[index1].b *filtervalue;
			}

			xdx = x;
			if(xdx < width){
				index1++;
				index2++;
				filtervalue = (int)filter[index2];
            	r += (int)input[index1].r * filtervalue;
            	g += (int)input[index1].g * filtervalue;
            	b += (int)input[index1].b * filtervalue;
			}

			xdx = x+1;
			if(xdx < width){
				index1 = xdx+((ydy*m)<<5);
				index2 = 4+(2<<1);
				filtervalue = (int)filter[index2];
            	r += (int)input[index1].r * filtervalue;
            	g += (int)input[index1].g * filtervalue;
            	b += (int)input[index1].b * filtervalue;
			}
	}


    if (r < 0) r = 0;
	else if ( r> 255) r=255;
    if (g < 0) g = 0;
	else if ( g > 255 ) g= 255;
    if (b < 0) b = 0;
	else if (b > 255) b = 255;
    
    Pixel p;
	memset(&p, 0, 3);

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
	Pixel* p = malloc(3);

	int m = width >> 5;

    for (unsigned int y = 0; y < height; ++y) {

		for (unsigned int x = 0; x < width; x += 16){
			unsigned int xywidth = x+((y*m)<<5);

            *p = convolution(input, x, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+1, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+2, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+3, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+4, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+5, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+6, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+7, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+8, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+9, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+10, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+11, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+12, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+13, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+14, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

			xywidth +=1;
            *p = convolution(input, x+15, y, width, height, filter);
            output[xywidth].r = p->r;
            output[xywidth].g = p->g;
            output[xywidth].b = p->b;

        }
    }
	free(p);
}
