#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

// Optimized convolution function without loops
static Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    // Precompute indices and filter weights
    int indices[9][2] = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1,  0}, {0,  0}, {1,  0},
        {-1,  1}, {0,  1}, {1,  1}
    };

    int dx, dy, ix, iy;
    Pixel* pixel;
    float f;

    // Manual unrolling of the loop for a 3x3 filter
    dx = indices[0][0]; dy = indices[0][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[0];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[1][0]; dy = indices[1][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[1];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[2][0]; dy = indices[2][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[2];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[3][0]; dy = indices[3][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[3];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[4][0]; dy = indices[4][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[4];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[5][0]; dy = indices[5][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[5];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[6][0]; dy = indices[6][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[6];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[7][0]; dy = indices[7][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[7];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    dx = indices[8][0]; dy = indices[8][1];
    ix = x + dx; iy = y + dy;
    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {
        pixel = &input[ix + iy * width];
        f = filter[8];
        r += pixel->r * f;
        g += pixel->g * f;
        b += pixel->b * f;
    }

    Pixel p;
    p.r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
    p.g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
    p.b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));

    return p;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    // Adjust tile size based on image dimensions
    int tile_size;
    if (width >= 1024 && height >= 1024) {
        tile_size = 1024;
    } else if (width >= 512 && height >= 512) {
        tile_size = 512;
    } else if (width >= 256 && height >= 256) {
        tile_size = 256;
    } else if (width >= 128 && height >= 128) {
        tile_size = 128;
    } else {
        tile_size = 64;
    }

    for (int tile_x = 0; tile_x < width; tile_x += tile_size) {
        int max_x = tile_x + tile_size > width ? width : tile_x + tile_size;
        for (int tile_y = 0; tile_y < height; tile_y += tile_size) {
            int max_y = tile_y + tile_size > height ? height : tile_y + tile_size;

            for (int y = tile_y; y < max_y; ++y) {
                Pixel* output_ptr = output + y * width + tile_x;
                for (int x = tile_x; x < max_x; ++x) {
                    *output_ptr = convolution(input, x, y, width, height, filter);
                    ++output_ptr;
                }
            }
        }
    }
}