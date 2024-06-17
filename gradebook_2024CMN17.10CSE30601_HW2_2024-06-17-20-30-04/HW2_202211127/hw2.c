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

static inline void save_pixel(float r, float g, float b, Pixel* output) {
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    output->r = (unsigned char)r;
    output->g = (unsigned char)g;
    output->b = (unsigned char)b;
}

static inline void convolution_1(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x+1)+(y)*width].r * filter[5];
   	g += input[(x+1)+(y)*width].g * filter[5];
   	b += input[(x+1)+(y)*width].b * filter[5];

   	r += input[(x)+(y+1)*width].r * filter[7];
   	g += input[(x)+(y+1)*width].g * filter[7];
   	b += input[(x)+(y+1)*width].b * filter[7];

   	r += input[(x+1)+(y+1)*width].r * filter[8];
   	g += input[(x+1)+(y+1)*width].g * filter[8];
   	b += input[(x+1)+(y+1)*width].b * filter[8];
    save_pixel(r,g,b,&output[x + y * width]);
    return;
}

static inline void convolution_2(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;

   	r += input[(x-1)+(y)*width].r * filter[3];
   	g += input[(x-1)+(y)*width].g * filter[3];
   	b += input[(x-1)+(y)*width].b * filter[3];

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x+1)+(y)*width].r * filter[5];
   	g += input[(x+1)+(y)*width].g * filter[5];
   	b += input[(x+1)+(y)*width].b * filter[5];

   	r += input[(x-1)+(y+1)*width].r * filter[6];
   	g += input[(x-1)+(y+1)*width].g * filter[6];
   	b += input[(x-1)+(y+1)*width].b * filter[6];

   	r += input[(x)+(y+1)*width].r * filter[7];
   	g += input[(x)+(y+1)*width].g * filter[7];
   	b += input[(x)+(y+1)*width].b * filter[7];

   	r += input[(x+1)+(y+1)*width].r * filter[8];
   	g += input[(x+1)+(y+1)*width].g * filter[8];
   	b += input[(x+1)+(y+1)*width].b * filter[8];
    save_pixel(r,g,b,&output[x + y * width]);
}
static inline void convolution_3(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;
    

   	r += input[(x-1)+(y)*width].r * filter[3];
   	g += input[(x-1)+(y)*width].g * filter[3];
   	b += input[(x-1)+(y)*width].b * filter[3];

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x-1)+(y+1)*width].r * filter[6];
   	g += input[(x-1)+(y+1)*width].g * filter[6];
   	b += input[(x-1)+(y+1)*width].b * filter[6];

   	r += input[(x)+(y+1)*width].r * filter[7];
   	g += input[(x)+(y+1)*width].g * filter[7];
   	b += input[(x)+(y+1)*width].b * filter[7];
    save_pixel(r,g,b,&output[x + y * width]);
}

static inline void convolution_4(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;
    
	r += input[(x)+(y-1)*width].r * filter[1];
    g += input[(x)+(y-1)*width].g * filter[1];
    b += input[(x)+(y-1)*width].b * filter[1];	

	r += input[(x+1)+(y-1)*width].r * filter[2];
   	g += input[(x+1)+(y-1)*width].g * filter[2];
   	b += input[(x+1)+(y-1)*width].b * filter[2];


    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x+1)+(y)*width].r * filter[5];
   	g += input[(x+1)+(y)*width].g * filter[5];
   	b += input[(x+1)+(y)*width].b * filter[5];

   	r += input[(x)+(y+1)*width].r * filter[7];
   	g += input[(x)+(y+1)*width].g * filter[7];
   	b += input[(x)+(y+1)*width].b * filter[7];

   	r += input[(x+1)+(y+1)*width].r * filter[8];
   	g += input[(x+1)+(y+1)*width].g * filter[8];
   	b += input[(x+1)+(y+1)*width].b * filter[8];
    save_pixel(r,g,b,&output[x + y * width]);
}





// static inline void convolution_5_old(
//         Pixel* input, int x, int y, int width,float* filter, Pixel* output) {
//     float r = 0;
//     float g = 0;
//     float b = 0;
    
//     r += input[(x-1)+(y-1)*width].r * filter[0];
//     g += input[(x-1)+(y-1)*width].g * filter[0];
//     b += input[(x-1)+(y-1)*width].b * filter[0];
    
// 	r += input[(x)+(y-1)*width].r * filter[1];
//     g += input[(x)+(y-1)*width].g * filter[1];
//     b += input[(x)+(y-1)*width].b * filter[1];	

// 	r += input[(x+1)+(y-1)*width].r * filter[2];
//    	g += input[(x+1)+(y-1)*width].g * filter[2];
//    	b += input[(x+1)+(y-1)*width].b * filter[2];

//    	r += input[(x-1)+(y)*width].r * filter[3];
//    	g += input[(x-1)+(y)*width].g * filter[3];
//    	b += input[(x-1)+(y)*width].b * filter[3];

//     r += input[(x)+(y)*width].r * filter[4];
//     g += input[(x)+(y)*width].g * filter[4];
//     b += input[(x)+(y)*width].b * filter[4];

//    	r += input[(x+1)+(y)*width].r * filter[5];
//    	g += input[(x+1)+(y)*width].g * filter[5];
//    	b += input[(x+1)+(y)*width].b * filter[5];

//    	r += input[(x-1)+(y+1)*width].r * filter[6];
//    	g += input[(x-1)+(y+1)*width].g * filter[6];
//    	b += input[(x-1)+(y+1)*width].b * filter[6];

//    	r += input[(x)+(y+1)*width].r * filter[7];
//    	g += input[(x)+(y+1)*width].g * filter[7];
//    	b += input[(x)+(y+1)*width].b * filter[7];

//    	r += input[(x+1)+(y+1)*width].r * filter[8];
//    	g += input[(x+1)+(y+1)*width].g * filter[8];
//    	b += input[(x+1)+(y+1)*width].b * filter[8];
//     save_pixel(r,g,b,&output[x + y * width]);
// }






static inline void convolution_5_2by2(
        Pixel* input, int x, int y, int width, float* filter, Pixel* output) {
    float r[4] = {0, 0, 0, 0};
    float g[4] = {0, 0, 0, 0};
    float b[4] = {0, 0, 0, 0};

    int positions[4] = {x-1 + (y-1)*width,x + (y-1)*width,x-1 + y*width,x + y*width};

    int idx0 = positions[0];
    int idx1 = positions[1];
    int idx2 = positions[2];
    int idx3 = positions[3];
    float weight = filter[0];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    weight = filter[1];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    weight = filter[2];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    idx0 +=(width-2);
    idx1 +=(width-2);
    idx2 +=(width-2);
    idx3 +=(width-2);
    weight = filter[3];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    weight = filter[4];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight; 

    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    weight = filter[5];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight; 

    idx0 +=(width-2);
    idx1 +=(width-2);
    idx2 +=(width-2);
    idx3 +=(width-2);
    weight = filter[6];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;  

    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    weight = filter[7];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;  

    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    weight = filter[8];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    save_pixel(r[0], g[0], b[0], &output[x + y * width]);
    save_pixel(r[1], g[1], b[1], &output[x + 1 + y * width]);
    save_pixel(r[2], g[2], b[2], &output[x + (y + 1) * width]);
    save_pixel(r[3], g[3], b[3], &output[x + 1 + (y + 1) * width]);
}

static inline void convolution_5_4by4(
        Pixel* input, int x, int y, int width, float* filter, Pixel* output) {
    float r[16] = {0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0};
    float g[16] = {0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0};
    float b[16] = {0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0};

    int positions[16] = {
        x-1 + (y-1)*width,x + (y-1)*width,x+1 + (y-1)*width,x+2 + (y-1)*width, 
        x-1 + (y)*width,x + (y)*width,x+1 + (y)*width,x+2 + (y)*width, 
        x-1 + (y+1)*width,x + (y+1)*width,x+1 + (y+1)*width,x+2 + (y+1)*width, 
        x-1 + (y+2)*width,x + (y+2)*width,x+1 + (y+2)*width,x+2 + (y+2)*width                
    };

    int idx0 = positions[0];
    int idx1 = positions[1];
    int idx2 = positions[2];
    int idx3 = positions[3];
    int idx4 = positions[4];
    int idx5 = positions[5];
    int idx6 = positions[6];
    int idx7 = positions[7];
    int idx8 = positions[8];
    int idx9 = positions[9];
    int idx10 = positions[10];
    int idx11 = positions[11];
    int idx12 = positions[12];
    int idx13 = positions[13];
    int idx14 = positions[14];
    int idx15 = positions[15];
    float weight = filter[0];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;
    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    idx4 +=1;
    idx5 +=1;
    idx6 +=1;
    idx7 +=1;
    idx8 +=1;
    idx9 +=1;
    idx10 +=1;
    idx11 +=1;
    idx12 +=1;
    idx13 +=1;
    idx14 +=1;
    idx15 +=1;
    weight = filter[1];

 
    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;
    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    idx4 +=1;
    idx5 +=1;
    idx6 +=1;
    idx7 +=1;
    idx8 +=1;
    idx9 +=1;
    idx10 +=1;
    idx11 +=1;
    idx12 +=1;
    idx13 +=1;
    idx14 +=1;
    idx15 +=1;
    weight = filter[2];

   
    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;

    idx0 +=(width-2);
    idx1 +=(width-2);
    idx2 +=(width-2);
    idx3 +=(width-2);
    idx4 +=(width-2);
    idx5 +=(width-2);
    idx6 +=(width-2);
    idx7 +=(width-2);
    idx8 +=(width-2);
    idx9 +=(width-2);
    idx10 +=(width-2);
    idx11 +=(width-2);
    idx12 +=(width-2);
    idx13 +=(width-2);
    idx14 +=(width-2);
    idx15 +=(width-2);
    weight = filter[3];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;
    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    idx4 +=1;
    idx5 +=1;
    idx6 +=1;
    idx7 +=1;
    idx8 +=1;
    idx9 +=1;
    idx10 +=1;
    idx11 +=1;
    idx12 +=1;
    idx13 +=1;
    idx14 +=1;
    idx15 +=1;
    weight = filter[4];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;
    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    idx4 +=1;
    idx5 +=1;
    idx6 +=1;
    idx7 +=1;
    idx8 +=1;
    idx9 +=1;
    idx10 +=1;
    idx11 +=1;
    idx12 +=1;
    idx13 +=1;
    idx14 +=1;
    idx15 +=1;
    weight = filter[5];

r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;

    idx0 +=(width-2);
    idx1 +=(width-2);
    idx2 +=(width-2);
    idx3 +=(width-2);
    idx4 +=(width-2);
    idx5 +=(width-2);
    idx6 +=(width-2);
    idx7 +=(width-2);
    idx8 +=(width-2);
    idx9 +=(width-2);
    idx10 +=(width-2);
    idx11 +=(width-2);
    idx12 +=(width-2);
    idx13 +=(width-2);
    idx14 +=(width-2);
    idx15 +=(width-2);
    weight = filter[6];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;
    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    idx4 +=1;
    idx5 +=1;
    idx6 +=1;
    idx7 +=1;
    idx8 +=1;
    idx9 +=1;
    idx10 +=1;
    idx11 +=1;
    idx12 +=1;
    idx13 +=1;
    idx14 +=1;
    idx15 +=1;
    weight = filter[7];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;
    idx0 +=1;
    idx1 +=1;
    idx2 +=1;
    idx3 +=1;
    idx4 +=1;
    idx5 +=1;
    idx6 +=1;
    idx7 +=1;
    idx8 +=1;
    idx9 +=1;
    idx10 +=1;
    idx11 +=1;
    idx12 +=1;
    idx13 +=1;
    idx14 +=1;
    idx15 +=1;
    weight = filter[8];

    r[0] += (&input[idx0])->r * weight;
    g[0] += (&input[idx0])->g * weight;
    b[0] += (&input[idx0])->b * weight;

    r[1] += (&input[idx1])->r * weight;
    g[1] += (&input[idx1])->g * weight;
    b[1] += (&input[idx1])->b * weight;
    
    r[2] += (&input[idx2])->r * weight;
    g[2] += (&input[idx2])->g * weight;
    b[2] += (&input[idx2])->b * weight;

    r[3] += (&input[idx3])->r * weight;
    g[3] += (&input[idx3])->g * weight;
    b[3] += (&input[idx3])->b * weight;

    r[4] += (&input[idx4])->r * weight;
    g[4] += (&input[idx4])->g * weight;
    b[4] += (&input[idx4])->b * weight;

    r[5] += (&input[idx5])->r * weight;
    g[5] += (&input[idx5])->g * weight;
    b[5] += (&input[idx5])->b * weight;
    
    r[6] += (&input[idx6])->r * weight;
    g[6] += (&input[idx6])->g * weight;
    b[6] += (&input[idx6])->b * weight;

    r[7] += (&input[idx7])->r * weight;
    g[7] += (&input[idx7])->g * weight;
    b[7] += (&input[idx7])->b * weight;

    r[8] += (&input[idx8])->r * weight;
    g[8] += (&input[idx8])->g * weight;
    b[8] += (&input[idx8])->b * weight;

    r[9] += (&input[idx9])->r * weight;
    g[9] += (&input[idx9])->g * weight;
    b[9] += (&input[idx9])->b * weight;
    
    r[10] += (&input[idx10])->r * weight;
    g[10] += (&input[idx10])->g * weight;
    b[10] += (&input[idx10])->b * weight;

    r[11] += (&input[idx11])->r * weight;
    g[11] += (&input[idx11])->g * weight;
    b[11] += (&input[idx11])->b * weight;

    r[12] += (&input[idx12])->r * weight;
    g[12] += (&input[idx12])->g * weight;
    b[12] += (&input[idx12])->b * weight;

    r[13] += (&input[idx13])->r * weight;
    g[13] += (&input[idx13])->g * weight;
    b[13] += (&input[idx13])->b * weight;
    
    r[14] += (&input[idx14])->r * weight;
    g[14] += (&input[idx14])->g * weight;
    b[14] += (&input[idx14])->b * weight;

    r[15] += (&input[idx15])->r * weight;
    g[15] += (&input[idx15])->g * weight;
    b[15] += (&input[idx15])->b * weight;

    save_pixel(r[0], g[0], b[0], &output[x + y * width]);
    save_pixel(r[1], g[1], b[1], &output[x + 1 + y * width]);
    save_pixel(r[2], g[2], b[2], &output[x + 2+ y * width]);
    save_pixel(r[3], g[3], b[3], &output[x + 3 + y * width]);
    save_pixel(r[4], g[4], b[4], &output[x + (y+1) * width]);
    save_pixel(r[5], g[5], b[5], &output[x + 1 + (y+1) * width]);
    save_pixel(r[6], g[6], b[6], &output[x + 2+ (y+1) * width]);
    save_pixel(r[7], g[7], b[7], &output[x + 3 + (y+1) * width]);
    save_pixel(r[8], g[8], b[8], &output[x + (y+2) * width]);
    save_pixel(r[9], g[9], b[9], &output[x + 1 + (y+2) * width]);
    save_pixel(r[10], g[10], b[10], &output[x + 2+ (y+2) * width]);
    save_pixel(r[11], g[11], b[11], &output[x + 3 + (y+2) * width]);
    save_pixel(r[12], g[12], b[12], &output[x + (y+3) * width]);
    save_pixel(r[13], g[13], b[13], &output[x + 1 + (y+3) * width]);
    save_pixel(r[14], g[14], b[14], &output[x + 2+ (y+3) * width]);
    save_pixel(r[15], g[15], b[15], &output[x + 3 + (y+3) * width]);
}





// static inline void convolution_5(
//         Pixel* input, int x, int y, int width, float* filter, Pixel* output) {
//     float r[4] = {0, 0, 0, 0};
//     float g[4] = {0, 0, 0, 0};
//     float b[4] = {0, 0, 0, 0};

//     int positions[4][9] = {
//         {x-1 + (y-1)*width, x + (y-1)*width, x+1 + (y-1)*width, x-1 + y*width, x + y*width, x+1 + y*width, x-1 + (y+1)*width, x + (y+1)*width, x+1 + (y+1)*width},
//         {x + (y-1)*width, x+1 + (y-1)*width, x+2 + (y-1)*width, x + y*width, x+1 + y*width, x+2 + y*width, x + (y+1)*width, x+1 + (y+1)*width, x+2 + (y+1)*width},
//         {x-1 + y*width, x + y*width, x+1 + y*width, x-1 + (y+1)*width, x + (y+1)*width, x+1 + (y+1)*width, x-1 + (y+2)*width, x + (y+2)*width, x+1 + (y+2)*width},
//         {x + y*width, x+1 + y*width, x+2 + y*width, x + (y+1)*width, x+1 + (y+1)*width, x+2 + (y+1)*width, x + (y+2)*width, x+1 + (y+2)*width, x+2 + (y+2)*width}
//     };

//     int idx0 = positions[0][0];
//     int idx1 = positions[1][0];
//     int idx2 = positions[2][0];
//     int idx3 = positions[3][0];
//     float weight = filter[0];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;

//     idx0 = positions[0][1];
//     idx1 = positions[1][1];
//     idx2 = positions[2][1];
//     idx3 = positions[3][1];
//     weight = filter[1];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;

//     idx0 = positions[0][2];
//     idx1 = positions[1][2];
//     idx2 = positions[2][2];
//     idx3 = positions[3][2];
//     weight = filter[2];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;
    
//     idx0 = positions[0][3];
//     idx1 = positions[1][3];
//     idx2 = positions[2][3];
//     idx3 = positions[3][3];
//     weight = filter[3];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;    
    
//     idx0 = positions[0][4];
//     idx1 = positions[1][4];
//     idx2 = positions[2][4];
//     idx3 = positions[3][4];
//     weight = filter[4];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;    
    
//     idx0 = positions[0][5];
//     idx1 = positions[1][5];
//     idx2 = positions[2][5];
//     idx3 = positions[3][5];
//     weight = filter[5];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;    

//     idx0 = positions[0][6];
//     idx1 = positions[1][6];
//     idx2 = positions[2][6];
//     idx3 = positions[3][6];
//     weight = filter[6];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;    

//     idx0 = positions[0][7];
//     idx1 = positions[1][7];
//     idx2 = positions[2][7];
//     idx3 = positions[3][7];
//     weight = filter[7];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;    

//     idx0 = positions[0][8];
//     idx1 = positions[1][8];
//     idx2 = positions[2][8];
//     idx3 = positions[3][8];
//     weight = filter[8];

//     r[0] += input[idx0].r * weight;
//     g[0] += input[idx0].g * weight;
//     b[0] += input[idx0].b * weight;

//     r[1] += input[idx1].r * weight;
//     g[1] += input[idx1].g * weight;
//     b[1] += input[idx1].b * weight;

//     r[2] += input[idx2].r * weight;
//     g[2] += input[idx2].g * weight;
//     b[2] += input[idx2].b * weight;

//     r[3] += input[idx3].r * weight;
//     g[3] += input[idx3].g * weight;
//     b[3] += input[idx3].b * weight;

//     save_pixel(r[0], g[0], b[0], &output[x + y * width]);
//     save_pixel(r[1], g[1], b[1], &output[x + 1 + y * width]);
//     save_pixel(r[2], g[2], b[2], &output[x + (y + 1) * width]);
//     save_pixel(r[3], g[3], b[3], &output[x + 1 + (y + 1) * width]);
// }






static inline void convolution_6(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;
    
    r += input[(x-1)+(y-1)*width].r * filter[0];
    g += input[(x-1)+(y-1)*width].g * filter[0];
    b += input[(x-1)+(y-1)*width].b * filter[0];
    
	r += input[(x)+(y-1)*width].r * filter[1];
    g += input[(x)+(y-1)*width].g * filter[1];
    b += input[(x)+(y-1)*width].b * filter[1];	

   	r += input[(x-1)+(y)*width].r * filter[3];
   	g += input[(x-1)+(y)*width].g * filter[3];
   	b += input[(x-1)+(y)*width].b * filter[3];

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x-1)+(y+1)*width].r * filter[6];
   	g += input[(x-1)+(y+1)*width].g * filter[6];
   	b += input[(x-1)+(y+1)*width].b * filter[6];

   	r += input[(x)+(y+1)*width].r * filter[7];
   	g += input[(x)+(y+1)*width].g * filter[7];
   	b += input[(x)+(y+1)*width].b * filter[7];
    save_pixel(r,g,b,&output[x + y * width]);
    return;
}

static inline void convolution_7(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;
    
	r += input[(x)+(y-1)*width].r * filter[1];
    g += input[(x)+(y-1)*width].g * filter[1];
    b += input[(x)+(y-1)*width].b * filter[1];	

	r += input[(x+1)+(y-1)*width].r * filter[2];
   	g += input[(x+1)+(y-1)*width].g * filter[2];
   	b += input[(x+1)+(y-1)*width].b * filter[2];

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x+1)+(y)*width].r * filter[5];
   	g += input[(x+1)+(y)*width].g * filter[5];
   	b += input[(x+1)+(y)*width].b * filter[5];
    save_pixel(r,g,b,&output[x + y * width]);
    return;
}

static inline void convolution_8(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;

    r += input[(x-1)+(y-1)*width].r * filter[0];
    g += input[(x-1)+(y-1)*width].g * filter[0];
    b += input[(x-1)+(y-1)*width].b * filter[0];
    
	r += input[(x)+(y-1)*width].r * filter[1];
    g += input[(x)+(y-1)*width].g * filter[1];
    b += input[(x)+(y-1)*width].b * filter[1];	

	r += input[(x+1)+(y-1)*width].r * filter[2];
   	g += input[(x+1)+(y-1)*width].g * filter[2];
   	b += input[(x+1)+(y-1)*width].b * filter[2];

   	r += input[(x-1)+(y)*width].r * filter[3];
   	g += input[(x-1)+(y)*width].g * filter[3];
   	b += input[(x-1)+(y)*width].b * filter[3];

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];

   	r += input[(x+1)+(y)*width].r * filter[5];
   	g += input[(x+1)+(y)*width].g * filter[5];
   	b += input[(x+1)+(y)*width].b * filter[5];
    save_pixel(r,g,b,&output[x + y * width]);
    return;
}

static inline void convolution_9(
        Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output) {
    float r = 0;
    float g = 0;
    float b = 0;
    r += input[(x-1)+(y-1)*width].r * filter[0];
    g += input[(x-1)+(y-1)*width].g * filter[0];
    b += input[(x-1)+(y-1)*width].b * filter[0];
    
	r += input[(x)+(y-1)*width].r * filter[1];
    g += input[(x)+(y-1)*width].g * filter[1];
    b += input[(x)+(y-1)*width].b * filter[1];	

   	r += input[(x-1)+(y)*width].r * filter[3];
   	g += input[(x-1)+(y)*width].g * filter[3];
   	b += input[(x-1)+(y)*width].b * filter[3];

    r += input[(x)+(y)*width].r * filter[4];
    g += input[(x)+(y)*width].g * filter[4];
    b += input[(x)+(y)*width].b * filter[4];
    save_pixel(r,g,b,&output[x + y * width]);
    return;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    
    convolution_1(input, 0, 0, width, height, filter, output);
    for (int x = 1; x < width-1 ; ++x) {
            convolution_2(input, x, 0, width, height, filter, output);
    }
    convolution_3(input, width-1, 0, width, height, filter, output);
    for(int y = 1; y < height - 4; y+=4){
        for (int x = 1; x < width - 4; x+=4) {
            convolution_5_4by4(input, x, y , width, filter, output);
        }
        convolution_5_2by2(input, width-3, y , width, filter, output);
        convolution_5_2by2(input, width-3, y +2, width, filter, output);
        
        convolution_4(input, 0, y , width, height, filter, output);
        convolution_4(input, 0, y + 1, width, height, filter, output);
        convolution_6(input, width-1, y, width, height, filter, output);
        convolution_6(input, width-1, y + 1, width, height, filter, output);
        convolution_4(input, 0, y +2, width, height, filter, output);
        convolution_4(input, 0, y + 3, width, height, filter, output);
        convolution_6(input, width-1, y+2, width, height, filter, output);
        convolution_6(input, width-1, y + +3, width, height, filter, output);
    }
    for (int x = 1; x < width - 2; x+=2) {
        convolution_5_2by2(input, x, height-3, width, filter, output);
    }
    convolution_4(input, 0, height-3 , width, height, filter, output);
    convolution_4(input, 0, height-2, width, height, filter, output);
    convolution_6(input, width-1, height-3, width, height, filter, output);
    convolution_6(input, width-1, height-2, width, height, filter, output);
    convolution_7(input, 0, height-1, width, height, filter, output);
    for (int x = 1; x < width-1 ; ++x) {
            convolution_8(input, x, height-1, width, height, filter, output);
    }
    convolution_9(input, width-1, height-1, width, height, filter, output);
}