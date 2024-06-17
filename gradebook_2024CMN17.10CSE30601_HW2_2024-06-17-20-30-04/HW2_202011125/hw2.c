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



// ORIGINAL CODE
/*
static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
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

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Pixel* p = (Pixel*)malloc(sizeof(Pixel));
            *p = convolution(input, x, y, width, height, filter);

            output[x+y*width].r = p->r;
            output[x+y*width].g = p->g;
            output[x+y*width].b = p->b;

            free(p);
        }
    }
}
*/


// SPEED UP 1.26 (malloc remove, inline (default))
/*
static inline Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dy = -1; dy < 2; ++dy) {
        for (int dx = -1; dx < 2; ++dx) {
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


inline void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Pixel p;
            p = convolution(input, x, y, width, height, filter);

            output[x+y*width].r = p.r;
            output[x+y*width].g = p.g;
            output[x+y*width].b = p.b;
        }
    }
}
*/

// ONLY LOOP UNROLLING
/*
// int f00; int f01; int f02; int f10; int f11; int f12; int f20; int f21; int f22;

static inline Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    if (x > 0 && y > 0) {
        Pixel* p = &input[(x - 1) + (y - 1) * width];
        float f = filter[0];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (y > 0) {
        Pixel* p = &input[x + (y - 1) * width];
        float f = filter[1];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (x < width - 1 && y > 0) {
        Pixel* p = &input[(x + 1) + (y - 1) * width];
        float f = filter[2];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (x > 0) {
        Pixel* p = &input[(x - 1) + y * width];
        float f = filter[3];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    {
        Pixel* p = &input[x + y * width];
        float f = filter[4];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (x < width - 1) {
        Pixel* p = &input[(x + 1) + y * width];
        float f = filter[5];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (x > 0 && y < height - 1) {
        Pixel* p = &input[(x - 1) + (y + 1) * width];
        float f = filter[6];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (y < height - 1) {
        Pixel* p = &input[x + (y + 1) * width];
        float f = filter[7];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }

    if (x < width - 1 && y < height - 1) {
        Pixel* p = &input[(x + 1) + (y + 1) * width];
        float f = filter[8];
        r += p->r * f;
        g += p->g * f;
        b += p->b * f;
    }
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}


inline void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    // f00 = filter[0]; f01 = filter[1]; f02 = filter[2]; f10 = filter[3]; f11 = filter[4];
    // f12 = filter[5]; f20 = filter[6]; f21 = filter[7]; f22 = filter[8];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Pixel p;
            p = convolution(input, x, y, width, height, filter);

            output[x+y*width].r = p.r;
            output[x+y*width].g = p.g;
            output[x+y*width].b = p.b;
        }
    }
}

*/

// LOOP UNROLLING + Code motion (x + y*width) (filter)
/*
float f00; float f01; float f02; float f10; float f11; float f12; float f20; float f21; float f22;

static inline Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    int xy_width = x + y * width;

    if (x > 0 && y > 0) {
        Pixel* p = &input[xy_width - 1 - width];
        r += p->r * f00;
        g += p->g * f00;
        b += p->b * f00;
    }

    if (y > 0) {
        Pixel* p = &input[xy_width - width];
        r += p->r * f01;
        g += p->g * f01;
        b += p->b * f01;
    }

    if (x < width - 1 && y > 0) {
        Pixel* p = &input[xy_width - width + 1];
        r += p->r * f02;
        g += p->g * f02;
        b += p->b * f02;
    }

    if (x > 0) {
        Pixel* p = &input[xy_width - 1];
        r += p->r * f10;
        g += p->g * f10;
        b += p->b * f10;
    }

    {
        Pixel* p = &input[xy_width];
        r += p->r * f11;
        g += p->g * f11;
        b += p->b * f11;
    }

    if (x < width - 1) {
        Pixel* p = &input[xy_width + 1];
        r += p->r * f12;
        g += p->g * f12;
        b += p->b * f12;
    }

    if (x > 0 && y < height - 1) {
        Pixel* p = &input[xy_width + width -1];
        r += p->r * f20;
        g += p->g * f20;
        b += p->b * f20;
    }

    if (y < height - 1) {
        Pixel* p = &input[xy_width + width];
        r += p->r * f21;
        g += p->g * f21;
        b += p->b * f21;
    }

    if (x < width - 1 && y < height - 1) {
        Pixel* p = &input[xy_width + 1 + width];
        r += p->r * f22;
        g += p->g * f22;
        b += p->b * f22;
    }
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    // memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}


inline void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    f00 = filter[0]; f01 = filter[1]; f02 = filter[2]; f10 = filter[3]; f11 = filter[4];
    f12 = filter[5]; f20 = filter[6]; f21 = filter[7]; f22 = filter[8];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Pixel p;
            p = convolution(input, x, y, width, height, filter);

            output[x+y*width].r = p.r;
            output[x+y*width].g = p.g;
            output[x+y*width].b = p.b;
        }
    }
}

*/


// Float to Int
/*
int f00; int f01; int f02; int f10; int f11; int f12; int f20; int f21; int f22;

static inline Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    int r = 0;
    int g = 0;
    int b = 0;

    int xy_width = x + y * width;

    if (x > 0 && y > 0) {
        Pixel* p = &input[xy_width - 1 - width];
        r += (int)p->r * f00;
        g += (int)p->g * f00;
        b += (int)p->b * f00;
    }

    if (y > 0) {
        Pixel* p = &input[xy_width - width];
        r += (int)p->r * f01;
        g += (int)p->g * f01;
        b += (int)p->b * f01;
    }

    if (x < width - 1 && y > 0) {
        Pixel* p = &input[xy_width - width + 1];
        r += (int)p->r * f02;
        g += (int)p->g * f02;
        b += (int)p->b * f02;
    }

    if (x > 0) {
        Pixel* p = &input[xy_width - 1];
        r += (int)p->r * f10;
        g += (int)p->g * f10;
        b += (int)p->b * f10;
    }

    {
        Pixel* p = &input[xy_width];
        r += (int)p->r * f11;
        g += (int)p->g * f11;
        b += (int)p->b * f11;
    }

    if (x < width - 1) {
        Pixel* p = &input[xy_width + 1];
        r += (int)p->r * f12;
        g += (int)p->g * f12;
        b += (int)p->b * f12;
    }

    if (x > 0 && y < height - 1) {
        Pixel* p = &input[xy_width + width -1];
        r += (int)p->r * f20;
        g += (int)p->g * f20;
        b += (int)p->b * f20;
    }

    if (y < height - 1) {
        Pixel* p = &input[xy_width + width];
        r += (int)p->r * f21;
        g += (int)p->g * f21;
        b += (int)p->b * f21;
    }

    if (x < width - 1 && y < height - 1) {
        Pixel* p = &input[xy_width + 1 + width];
        r += (int)p->r * f22;
        g += (int)p->g * f22;
        b += (int)p->b * f22;
    }
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}


inline void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    f00 = filter[0]; f01 = filter[1]; f02 = filter[2]; f10 = filter[3]; f11 = filter[4];
    f12 = filter[5]; f20 = filter[6]; f21 = filter[7]; f22 = filter[8];

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Pixel p;
            p = convolution(input, x, y, width, height, filter);

            output[x+y*width].r = p.r;
            output[x+y*width].g = p.g;
            output[x+y*width].b = p.b;
        }
    }
}

*/


// Loop change (super scalar)
// /*s
int f00; int f01; int f02; int f10; int f11; int f12; int f20; int f21; int f22;

static inline Pixel convolution(
        Pixel* input, int x, int y, int width, int height) {
    int r = 0;
    int g = 0;
    int b = 0;

    int xy_width = x + y * width;

    if (x > 0 && y > 0) {
        Pixel* p = &input[xy_width - 1 - width];
        r += (int)p->r * f00;
        g += (int)p->g * f00;
        b += (int)p->b * f00;
    }

    if (y > 0) {
        Pixel* p = &input[xy_width - width];
        r += (int)p->r * f01;
        g += (int)p->g * f01;
        b += (int)p->b * f01;
    }

    if (x < width - 1 && y > 0) {
        Pixel* p = &input[xy_width - width + 1];
        r += (int)p->r * f02;
        g += (int)p->g * f02;
        b += (int)p->b * f02;
    }

    if (x > 0) {
        Pixel* p = &input[xy_width - 1];
        r += (int)p->r * f10;
        g += (int)p->g * f10;
        b += (int)p->b * f10;
    }

    {
        Pixel* p = &input[xy_width];
        r += (int)p->r * f11;
        g += (int)p->g * f11;
        b += (int)p->b * f11;
    }

    if (x < width - 1) {
        Pixel* p = &input[xy_width + 1];
        r += (int)p->r * f12;
        g += (int)p->g * f12;
        b += (int)p->b * f12;
    }

    if (x > 0 && y < height - 1) {
        Pixel* p = &input[xy_width + width -1];
        r += (int)p->r * f20;
        g += (int)p->g * f20;
        b += (int)p->b * f20;
    }

    if (y < height - 1) {
        Pixel* p = &input[xy_width + width];
        r += (int)p->r * f21;
        g += (int)p->g * f21;
        b += (int)p->b * f21;
    }

    if (x < width - 1 && y < height - 1) {
        Pixel* p = &input[xy_width + 1 + width];
        r += (int)p->r * f22;
        g += (int)p->g * f22;
        b += (int)p->b * f22;
    }
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}


inline void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    f00 = filter[0]; f01 = filter[1]; f02 = filter[2]; f10 = filter[3]; f11 = filter[4];
    f12 = filter[5]; f20 = filter[6]; f21 = filter[7]; f22 = filter[8];

    for (int y = 0; y < height; y+=2) {
        for (int x = 0; x < width; x+=2) {
            int xy_width = x + y*width;

            output[xy_width] = convolution(input, x, y, width, height);
            
            output[xy_width + 1] = convolution(input, x + 1, y, width, height);

            output[xy_width + width] = convolution(input, x, y + 1, width, height);
            
            output[xy_width + 1 + width] = convolution(input, x + 1, y + 1, width, height);

            // output[xy_width + width] = convolution(input, x, y + 1, width, height);
            
            // output[xy_width + 1 + width] = convolution(input, x + 1, y + 1, width, height);
            
        }
    }
}

// */





