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

static Pixel* img2pimg(Pixel* img, int width, int height) {
    int p_width = width + 2;
    int p_heigth = height + 2;

    Pixel *pimg = (Pixel *)malloc((p_heigth*p_width) * sizeof(Pixel));
    Pixel *src = img;
    Pixel *dst = pimg + (p_width + 1);
    int cpsize = width*sizeof(Pixel);

    for (int i = 0; i < height; i++) {
        memcpy(dst, src, cpsize);
        dst += p_width;
        src += width;
    }
    
    return pimg;
}

static void convolution(Pixel *input, Pixel *output, int width, int height, float* kernel) {
    double r = 0;
    double g = 0;
    double b = 0;

    Pixel *pinput = img2pimg(input, width, height); // zero padded image
    int p_width = width+2;
    
    int offset = p_width;
    Pixel *p_src = pinput + offset;
    Pixel *p_lu, *p_u, *p_ru;   // (left up, up, right up) for p_src
    Pixel *p_l, *p_r;           // (left rigth) for p_src
    Pixel *p_ld, *p_d, *p_rd;   // (left down, down, right down) for p_src
    Pixel *p_dst = output;      // caculated r, g, b are stored in p_dst

    // kernel has circular symmetry
    float kv = kernel[0]; // kernel vertex value
    float ke = kernel[1]; // kernel edge value
    float kc = kernel[4]; // kernel center value

    // adjacency pixel access operator
    int up = -p_width;
    int down = +p_width;
    int left = -1;
    int right = +1;

    int left_up = left+up;
    int right_up = right+up;
    int left_down = left+down;
    int right_down = right+down;

    // convolution
    for (int row = 0; row < height; row++) {
        p_src++;
        for (int col = 0; col < width; col++) {
            p_l =   p_src + (left);
            p_u =   p_src + (up);
            p_r =   p_src + (right);
            p_d =   p_src + (down);
            
            p_lu =  p_src + (left_up);
            p_ru =  p_src + (right_up);
            p_ld =  p_src + (left_down);
            p_rd =  p_src + (right_down);

            r = kv * (p_lu->r + p_ru->r + p_ld->r + p_rd->r) + ke * (p_l->r + p_u->r + p_r->r + p_d->r) + kc * (p_src->r);
            g = kv * (p_lu->g + p_ru->g + p_ld->g + p_rd->g) + ke * (p_l->g + p_u->g + p_r->g + p_d->g) + kc * (p_src->g);
            b = kv * (p_lu->b + p_ru->b + p_ld->b + p_rd->b) + ke * (p_l->b + p_u->b + p_r->b + p_d->b) + kc * (p_src->b);

            p_dst->r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            p_dst->g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            p_dst->b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

            p_src++;
            p_dst++;
        }
        p_src++;
    }
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    convolution(input, output, width, height, filter);
}
