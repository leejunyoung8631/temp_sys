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

/*
static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    unsigned long long wy = (y-1)*width;
    int fy = 0;


    
    // for (int dy = -1; dy < 2; ++dy) {
        
    //     for (dx = -1; dx < 2; ++dx) {
    //         //if ( !( (y + dy) < 0 || (y + dy) >= height || (x + dx) < 0 || (x + dx) >= width ) ) {
    //         if ( (y + dy) > -1 && (y + dy) < height && (x + dx) > -1 && (x + dx) < width )  {
    //             r += input[(x+dx)+wy].r * filter[(dx+1)+fy];
    //             g += input[(x+dx)+wy].g * filter[(dx+1)+fy];
    //             b += input[(x+dx)+wy].b * filter[(dx+1)+fy];
    //         }
    //     }

    //     wy += width;
    //     fy += 3;
    // }
    


    // dy = -1
    if ( y > 0 ) {
        if ( x > 0 ) {    // dx = -1
            r += input[(x-1)+wy].r * filter[fy];
            g += input[(x-1)+wy].g * filter[fy];
            b += input[(x-1)+wy].b * filter[fy];
        }

        r += input[x+wy].r * filter[1+fy];  // dx = 0
        g += input[x+wy].g * filter[1+fy];
        b += input[x+wy].b * filter[1+fy];

        if ( (x + 1) < width ) {
            r += input[(x+1)+wy].r * filter[2+fy];
            g += input[(x+1)+wy].g * filter[2+fy];
            b += input[(x+1)+wy].b * filter[2+fy];
        }
    }

    wy += width;
    fy += 3;




    // dy = 0
    if ( x > 0 )  { // dx = -1
        r += input[(x-1)+wy].r * filter[fy];
        g += input[(x-1)+wy].g * filter[fy];
        b += input[(x-1)+wy].b * filter[fy];
    }

    //if ( 1 )  {   // dx = 0
        r += input[x+wy].r * filter[1+fy];
        g += input[x+wy].g * filter[1+fy];
        b += input[x+wy].b * filter[1+fy];
    //}

    if ( (x + 1) < width )  {   // dx = 1
        r += input[(x+1)+wy].r * filter[2+fy];
        g += input[(x+1)+wy].g * filter[2+fy];
        b += input[(x+1)+wy].b * filter[2+fy];
    }

    wy += width;
    fy += 3;




    // dy = 1
    if ( (y + 1) < height )  {
        if ( x > 0 )  { // dx = -1
            r += input[(x-1)+wy].r * filter[fy];
            g += input[(x-1)+wy].g * filter[fy];
            b += input[(x-1)+wy].b * filter[fy];
        }

        r += input[x+wy].r * filter[1+fy];  // dx = 0
        g += input[x+wy].g * filter[1+fy];
        b += input[x+wy].b * filter[1+fy];

        if ( (x + 1) < width )  {   // dx = 1
            r += input[(x+1)+wy].r * filter[2+fy];
            g += input[(x+1)+wy].g * filter[2+fy];
            b += input[(x+1)+wy].b * filter[2+fy];
        }
    }





    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    Pixel p;
    //memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}
*/

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];



    unsigned long long wy_l;

    double r;
    double g;
    double b;

    long long wy;
    // int fy;

    int x, y, x_end = width-1;
    
    float v_f0, v_f1, v_f2, v_f3, v_f4, v_f5, v_f6, v_f7, v_f8;
    v_f0 = filter[0];
    v_f1 = filter[1];
    v_f2 = filter[2];
    v_f3 = filter[3];
    v_f4 = filter[4];
    v_f5 = filter[5];
    v_f6 = filter[6];
    v_f7 = filter[7];
    v_f8 = filter[8];






    ////////////////////////////////////////////////////////////////
    // y = 0
    




    










    /////////////////////////////////////////////////////////////////
    // y = middle

    // x = 0
    wy_l = 0;
    for (y = 0; y < height; ++y) {
        r = 0; g = 0; b = 0;
        wy = (long long)(y-1)*width;

        if ( y > 0 ) {
            r += input[wy].r * v_f1;  // dx = 0
            g += input[wy].g * v_f1;
            b += input[wy].b * v_f1;
            r += input[1+wy].r * v_f2;
            g += input[1+wy].g * v_f2;
            b += input[1+wy].b * v_f2;
        }
        wy += width;

        r += input[wy].r * v_f4;   // dx = 0
        g += input[wy].g * v_f4;
        b += input[wy].b * v_f4;
        r += input[1+wy].r * v_f5; // dx = 1
        g += input[1+wy].g * v_f5;
        b += input[1+wy].b * v_f5;
        wy += width;

        if ( (y + 1) < height )  {
            r += input[wy].r * v_f7;  // dx = 0
            g += input[wy].g * v_f7;
            b += input[wy].b * v_f7;
            r += input[1+wy].r * v_f8; // dx = 1
            g += input[1+wy].g * v_f8;
            b += input[1+wy].b * v_f8;
        }

        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        output[wy_l].r = (unsigned char)r;
        output[wy_l].g = (unsigned char)g;
        output[wy_l].b = (unsigned char)b;

        wy_l += width;
    }







    // x = middle
    wy_l = 0;
    for (y = 0; y < height; ++y) {
        for (x = 1; x < x_end; ++x) {
            //Pixel* p = (Pixel*)malloc(sizeof(Pixel));
            //Pixel p = convolution(input, x, y, width, height, filter);

            r = 0;
            g = 0;
            b = 0;

            wy = (long long)(y-1)*width;
            // fy = 0;



            // dy = -1
            if ( y > 0 ) {
                //if ( x > 0 ) {    // dx = -1
                    r += input[(x-1)+wy].r * v_f0;
                    g += input[(x-1)+wy].g * v_f0;
                    b += input[(x-1)+wy].b * v_f0;
                //}

                r += input[x+wy].r * v_f1;  // dx = 0
                g += input[x+wy].g * v_f1;
                b += input[x+wy].b * v_f1;

                //if ( (x + 1) < width ) {
                    r += input[(x+1)+wy].r * v_f2;
                    g += input[(x+1)+wy].g * v_f2;
                    b += input[(x+1)+wy].b * v_f2;
                //}
            }

            wy += width;
            // fy += 3;



            // dy = 0
            //if ( x > 0 )  { // dx = -1
                r += input[(x-1)+wy].r * v_f3;
                g += input[(x-1)+wy].g * v_f3;
                b += input[(x-1)+wy].b * v_f3;
            //}

            //if ( 1 )  {   // dx = 0
                r += input[x+wy].r * v_f4;
                g += input[x+wy].g * v_f4;
                b += input[x+wy].b * v_f4;
            //}

            //if ( (x + 1) < width )  {   // dx = 1
                r += input[(x+1)+wy].r * v_f5;
                g += input[(x+1)+wy].g * v_f5;
                b += input[(x+1)+wy].b * v_f5;
            //}

            wy += width;
            // fy += 3;



            // dy = 1
            if ( (y + 1) < height )  {
                //if ( x > 0 )  { // dx = -1
                    r += input[(x-1)+wy].r * v_f6;
                    g += input[(x-1)+wy].g * v_f6;
                    b += input[(x-1)+wy].b * v_f6;
                //}

                r += input[x+wy].r * v_f7;  // dx = 0
                g += input[x+wy].g * v_f7;
                b += input[x+wy].b * v_f7;

                //if ( (x + 1) < width )  {   // dx = 1
                    r += input[(x+1)+wy].r * v_f8;
                    g += input[(x+1)+wy].g * v_f8;
                    b += input[(x+1)+wy].b * v_f8;
                //}
            }

            if (r < 0) r = 0;
            if (g < 0) g = 0;
            if (b < 0) b = 0;

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;

            //Pixel p;
            //memset(&p, 0, sizeof(p));

            //p.r = (unsigned char)r;
            //p.g = (unsigned char)g;
            //p.b = (unsigned char)b;

            output[x+wy_l].r = (unsigned char)r;
            output[x+wy_l].g = (unsigned char)g;
            output[x+wy_l].b = (unsigned char)b;

            //free(p);
        }
        wy_l += width;
    }
    
    
    
    
    
    
    
    
    
    // x = width-1
    wy_l = 0;
    x = x_end;
    for (y = 0; y < height; ++y) {
        r = 0; g = 0; b = 0;
        wy = (long long)(y-1)*width;

        if ( y > 0 ) {
            r += input[(x-1)+wy].r * v_f0;
            g += input[(x-1)+wy].g * v_f0;
            b += input[(x-1)+wy].b * v_f0;
            r += input[x+wy].r * v_f1;  // dx = 0
            g += input[x+wy].g * v_f1;
            b += input[x+wy].b * v_f1;
        }
        wy += width;

        r += input[(x-1)+wy].r * v_f3;
        g += input[(x-1)+wy].g * v_f3;
        b += input[(x-1)+wy].b * v_f3;
        r += input[x+wy].r * v_f4;
        g += input[x+wy].g * v_f4;
        b += input[x+wy].b * v_f4;
        wy += width;

        if ( (y + 1) < height )  {
            r += input[(x-1)+wy].r * v_f6;
            g += input[(x-1)+wy].g * v_f6;
            b += input[(x-1)+wy].b * v_f6;
            r += input[x+wy].r * v_f7;  // dx = 0
            g += input[x+wy].g * v_f7;
            b += input[x+wy].b * v_f7;
        }

        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;
        output[x+wy_l].r = (unsigned char)r;
        output[x+wy_l].g = (unsigned char)g;
        output[x+wy_l].b = (unsigned char)b;
    
        wy_l += width;
    }
    
    
    
    
    
}
