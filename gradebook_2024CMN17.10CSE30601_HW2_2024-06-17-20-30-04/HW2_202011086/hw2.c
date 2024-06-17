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
    unsigned int width = *(unsigned int *) args[0];
    unsigned int height = *(unsigned int *) args[1];
    Pixel *input = args[2];
    Pixel *output = args[3];
    float *filter = args[4];

    // int type based filter

    int filter2[9];
    for (int i = 0; i < 9; ++i) {
        filter2[i] = (int) (4096 * filter[i]);
    }

    //int type base filter
    //


    //
    //temp data

    Pixel temp[4 * height];
    int height2 = 2 * height ;
    int height3 = 3 * height ;
    int height4 = 4 * height ;

    //inner pixel calculation

    for (int y = 1; y < height - 1; ++y) {
        int pos = width * (y - 1);
        temp[y - 1].r = input[pos].r;
        temp[y - 1].g = input[pos].g;
        temp[y - 1].b = input[pos].b;
        temp[y - 1 + height].r = input[pos + 1].r;
        temp[y - 1 + height].g = input[pos + 1].g;
        temp[y - 1 + height].b = input[pos + 1].b;

        for (int x = 1; x < width - 1; ++x) {
            register int r = 0;
            register int g = 0;
            register int b = 0;
            int base_pos = x + y * width;
            r += input[base_pos - width - 1].r * filter2[0];
            r += input[base_pos - width].r * filter2[1];
            r += input[base_pos - width + 1].r * filter2[2];
            r += input[base_pos - 1].r * filter2[3];
            r += input[base_pos].r * filter2[4];
            r += input[base_pos + 1].r * filter2[5];
            r += input[base_pos + width - 1].r * filter2[6];
            r += input[base_pos + width].r * filter2[7];
            r += input[base_pos + width + 1].r * filter2[8];
            g += input[base_pos - width - 1].g * filter2[0];
            g += input[base_pos - width].g * filter2[1];
            g += input[base_pos - width + 1].g * filter2[2];
            g += input[base_pos - 1].g * filter2[3];
            g += input[base_pos].g * filter2[4];
            g += input[base_pos + 1].g * filter2[5];
            g += input[base_pos + width - 1].g * filter2[6];
            g += input[base_pos + width].g * filter2[7];
            g += input[base_pos + width + 1].g * filter2[8];
            b += input[base_pos - width - 1].b * filter2[0];
            b += input[base_pos - width].b * filter2[1];
            b += input[base_pos - width + 1].b * filter2[2];
            b += input[base_pos - 1].b * filter2[3];
            b += input[base_pos].b * filter2[4];
            b += input[base_pos + 1].b * filter2[5];
            b += input[base_pos + width - 1].b * filter2[6];
            b += input[base_pos + width].b * filter2[7];
            b += input[base_pos + width + 1].b * filter2[8];

            output[base_pos].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >> 12));
            output[base_pos].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >> 12));
            output[base_pos].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >> 12));
        }
        temp[y - 1 + height2].r = input[pos + width - 2].r;
        temp[y - 1 + height2].g = input[pos + width - 2].g;
        temp[y - 1 + height2].b = input[pos + width - 2].b;
        temp[y - 1 + height3].r = input[pos + width - 1].r;
        temp[y - 1 + height3].g = input[pos + width - 1].g;
        temp[y - 1 + height3].b = input[pos + width - 1].b;

    }
    for (int i = 0; i < 2; ++i) {
        int pos = width * (height - 2 + i) ;
        temp[height - 2 + i].r = input[pos].r;
        temp[height - 2 + i].g = input[pos].g;
        temp[height - 2 + i].b = input[pos].b;
        temp[height2 - 2 + i].r = input[pos + 1].r;
        temp[height2 - 2 + i].g = input[pos + 1].g;
        temp[height2 - 2 + i].b = input[pos + 1].b;
        temp[height3 - 2 + i].r = input[pos+ width - 2].r;
        temp[height3 - 2 + i].g = input[pos + width - 2].g;
        temp[height3 - 2 + i].b = input[pos + width - 2].b;
        temp[height4 - 2 + i].r = input[pos + width - 1].r;
        temp[height4 - 2 + i].g = input[pos + width - 1].g;
        temp[height4 - 2 + i].b = input[pos + width - 1].b;
    }








    // inner part calculate


    // 가로 (1 , 0) -> ( width-1 , 0 )
    for (int x = 1; x < width - 1; ++x) {
        register int r = 0;
        register int g = 0;
        register int b = 0;
        r += input[x - 1].r * filter2[3];
        r += input[x].r * filter2[4];
        r += input[x + 1].r * filter2[5];
        r += input[x + width - 1].r * filter2[6];
        r += input[x + width].r * filter2[7];
        r += input[x + width + 1].r * filter2[8];
        g += input[x - 1].g * filter2[3];
        g += input[x].g * filter2[4];
        g += input[x + 1].g * filter2[5];
        g += input[x + width - 1].g * filter2[6];
        g += input[x + width].g * filter2[7];
        g += input[x + width + 1].g * filter2[8];
        b += input[x - 1].b * filter2[3];
        b += input[x].b * filter2[4];
        b += input[x + 1].b * filter2[5];
        b += input[x + width - 1].b * filter2[6];
        b += input[x + width].b * filter2[7];
        b += input[x + width + 1].b * filter2[8];
        output[x].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >> 12));
        output[x].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >> 12));
        output[x].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >> 12));
    }

    // (1, height-1) -> (width-1 , height -1 )

    for (int x = 1; x < width - 1; ++x) {
        register int r = 0;
        register int g = 0;
        register int b = 0;
        int base_pos = x + (height - 1) * width;
        r += input[base_pos - width - 1].r * filter2[0];
        r += input[base_pos - width].r * filter2[1];
        r += input[base_pos - width + 1].r * filter2[2];
        r += input[base_pos - 1].r * filter2[3];
        r += input[base_pos].r * filter2[4];
        r += input[base_pos + 1].r * filter2[5];


        g += input[base_pos - width - 1].g * filter2[0];
        g += input[base_pos - width].g * filter2[1];
        g += input[base_pos - width + 1].g * filter2[2];
        g += input[base_pos - 1].g * filter2[3];
        g += input[base_pos].g * filter2[4];
        g += input[base_pos + 1].g * filter2[5];


        b += input[base_pos - width - 1].b * filter2[0];
        b += input[base_pos - width].b * filter2[1];
        b += input[base_pos - width + 1].b * filter2[2];
        b += input[base_pos - 1].b * filter2[3];
        b += input[base_pos].b * filter2[4];
        b += input[base_pos + 1].b * filter2[5];


        output[base_pos].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >>12 ));
        output[base_pos].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >>12));
        output[base_pos].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >>12));
    }


    for (int y = 1; y < height - 1; ++y) {
        register int r = 0;
        register int g = 0;
        register int b = 0;
        r += temp[y - 1].r * filter2[1];
        r += temp[y - 1 + height].r * filter2[2];

        r += temp[y].r * filter2[4];
        r += temp[y + height].r * filter2[5];

        r += temp[y + 1].r * filter2[7];
        r += temp[y + 1 + height].r * filter2[8];


        g += temp[y - 1].g * filter2[1];
        g += temp[y - 1 + height].g * filter2[2];

        g += temp[y].g * filter2[4];
        g += temp[y + height].g * filter2[5];

        g += temp[y + 1].g * filter2[7];
        g += temp[y + 1 + height].g * filter2[8];


        b += temp[y - 1].b * filter2[1];
        b += temp[y - 1 + height].b * filter2[2];

        b += temp[y].b * filter2[4];
        b += temp[y + height].b * filter2[5];

        b += temp[y + 1].b * filter2[7];
        b += temp[y + 1 + height].b * filter2[8];


        output[width * y].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >>12));
        output[width * y].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >>12));
        output[width * y].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >>12));
    }
    for (int y = 1; y < height - 1; ++y) {
        register int r = 0;
        register int g = 0;
        register int b = 0;

        r += temp[y - 1 + height2].r * filter2[0];
        r += temp[y - 1 + height3].r * filter2[1];

        r += temp[y + height2].r * filter2[3];
        r += temp[y + height3].r * filter2[4];

        r += temp[y + 1 + height2].r * filter2[6];
        r += temp[y + 1 + height3].r * filter2[7];

        g += temp[y - 1 + height2].g * filter2[0];
        g += temp[y - 1 + height3].g * filter2[1];

        g += temp[y + height2].g * filter2[3];
        g += temp[y + height3].g * filter2[4];

        g += temp[y + 1 + height2].g * filter2[6];
        g += temp[y + 1 + height3].g * filter2[7];

        b += temp[y - 1 + height2].b * filter2[0];
        b += temp[y - 1 + height3].b * filter2[1];

        b += temp[y + height2].b * filter2[3];
        b += temp[y + height3].b * filter2[4];

        b += temp[y + 1 + height2].b * filter2[6];
        b += temp[y + 1 + height3].b * filter2[7];


        output[(y + 1) * width - 1].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >>12));
        output[(y + 1) * width - 1].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >>12));
        output[(y + 1) * width - 1].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >>12));
    }


    for(int i = 0 ; i<1 ; ++i) {
        register int r = 0;
        register int g = 0;
        register int b = 0;

        r += temp[0].r * filter2[4];
        g += temp[0].g * filter2[4];
        b += temp[0].b * filter2[4];

        r += temp[1].r * filter2[7];
        g += temp[1].g * filter2[7];
        b += temp[1].b * filter2[7];

        r += temp[0 + height].r * filter2[5];
        g += temp[0 + height].g * filter2[5];
        b += temp[0 + height].b * filter2[5];

        r += temp[1 + height].r * filter2[8];
        g += temp[1 + height].g * filter2[8];
        b += temp[1 + height].b * filter2[8];

        output[0].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >> 12));
        output[0].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >> 12));
        output[0].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >> 12));
        r = 0 ;
        g = 0 ;
        b = 0 ;



        r += temp[height2].r * filter2[3];
        g += temp[height2].g * filter2[3];
        b += temp[height2].b * filter2[3];

        r += temp[1 + height2].r * filter2[6];
        g += temp[1 + height2].g * filter2[6];
        b += temp[1 + height2].b * filter2[6];

        r += temp[height3].r * filter2[4];
        g += temp[height3].g * filter2[4];
        b += temp[height3].b * filter2[4];

        r += temp[1 + height3].r * filter2[7];
        g += temp[1 + height3].g * filter2[7];
        b += temp[1 + height3].b * filter2[7];

        output[width - 1].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >> 12));
        output[width - 1].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >> 12));
        output[width - 1].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >> 12));
        r = 0 ;
        g = 0 ;
        b = 0 ;


        r += temp[height - 2].r * filter2[1];
        g += temp[height - 2].g * filter2[1];
        b += temp[height - 2].b * filter2[1];

        r += temp[height - 1].r * filter2[4];
        g += temp[height - 1].g * filter2[4];
        b += temp[height - 1].b * filter2[4];

        r += temp[height2 - 2].r * filter2[2];
        g += temp[height2 - 2].g * filter2[2];
        b += temp[height2 - 2].b * filter2[2];

        r += temp[height2 - 1].r * filter2[5];
        g += temp[height2 - 1].g * filter2[5];
        b += temp[height2 - 1].b * filter2[5];

        output[width * (height - 1)].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >> 12));
        output[width * (height - 1)].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >> 12));
        output[width * (height - 1)].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >> 12));
        r = 0 ;
        g = 0 ;
        b = 0 ;


        r += temp[height3 - 2].r * filter2[0];
        g += temp[height3 - 2].g * filter2[0];
        b += temp[height3 - 2].b * filter2[0];

        r += temp[height3 - 1].r * filter2[3];
        g += temp[height3 - 1].g * filter2[3];
        b += temp[height3 - 1].b * filter2[3];

        r += temp[height4 - 2].r * filter2[1];
        g += temp[height4 - 2].g * filter2[1];
        b += temp[height4 - 2].b * filter2[1];

        r += temp[height4 - 1].r * filter2[4];
        g += temp[height4 - 1].g * filter2[4];
        b += temp[height4 - 1].b * filter2[4];

        output[width * height - 1].r = (unsigned char) (r < 0 ? 0 : (r > 1044480 ? 255 : r >> 12));
        output[width * height - 1].g = (unsigned char) (g < 0 ? 0 : (g > 1044480 ? 255 : g >> 12));
        output[width * height - 1].b = (unsigned char) (b < 0 ? 0 : (b > 1044480 ? 255 : b >> 12));
    }
    //
}