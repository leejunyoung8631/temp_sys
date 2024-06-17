#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

#define BLOCK_SIZE 32

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];
    int width_unrolled = (width / 16) * 16;  // Unroll 16 pixels at a time for processing
    // Process the image in blocks to reduce cache misses and improve data locality
    for (int by = 0; by < height; by += BLOCK_SIZE) {
        int max_y = by + BLOCK_SIZE < height ? by + BLOCK_SIZE : height;
        for (int bx = 0; bx < width; bx += BLOCK_SIZE) {
            int max_x = bx + BLOCK_SIZE < width ? bx + BLOCK_SIZE : width;
            for (int y = by; y < max_y; ++y) {
                for (int x = bx; x < max_x; x += 16) {  // Unroll the inner loop to process 16 pixels at a time
                    float val_r[16] = {0}, val_g[16] = {0}, val_b[16] = {0};
                    for (int dy = -1; dy <= 1; ++dy) {
                        int ny = y + dy;
                        if (ny < 0 || ny >= height) continue;
                        int rowIndexOffset = ny * width;
                        for (int dx = -1; dx <= 1; ++dx) {
                            int filterIndex = (dy + 1) * 3 + (dx + 1);
                            float filterValue = filter[filterIndex];
                            Pixel* p = (input + rowIndexOffset) + (x + dx);  // Pointer to the start pixel
                            for (int i = 0; i < 16; ++i) {
                                if (x + dx + i < width) {
                                    val_r[i] += filterValue*p[i].r;
                                    val_g[i] += filterValue*p[i].g;
                                    val_b[i] += filterValue*p[i].b;
                                }
                            }
                        }
                    }
                    int base_idx = y * width + x;\
                   
                    output[base_idx].r = (unsigned char)(val_r[0] > 255 ? 255 : val_r[0]);
                    output[base_idx].g = (unsigned char)(val_g[0] > 255 ? 255 : val_g[0]);
                    output[base_idx].b = (unsigned char)(val_b[0] > 255 ? 255 : val_b[0]);

                    output[base_idx + 1].r = (unsigned char)(val_r[1] > 255 ? 255 : val_r[1]);
                    output[base_idx + 1].g = (unsigned char)(val_g[1] > 255 ? 255 : val_g[1]);
                    output[base_idx + 1].b = (unsigned char)(val_b[1] > 255 ? 255 : val_b[1]);

                    output[base_idx + 2].r = (unsigned char)(val_r[2] > 255 ? 255 : val_r[2]);
                    output[base_idx + 2].g = (unsigned char)(val_g[2] > 255 ? 255 : val_g[2]);
                    output[base_idx + 2].b = (unsigned char)(val_b[2] > 255 ? 255 : val_b[2]);

                    output[base_idx + 3].r = (unsigned char)(val_r[3] > 255 ? 255 : val_r[3]);
                    output[base_idx + 3].g = (unsigned char)(val_g[3] > 255 ? 255 : val_g[3]);
                    output[base_idx + 3].b = (unsigned char)(val_b[3] > 255 ? 255 : val_b[3]);

                    output[base_idx + 4].r = (unsigned char)(val_r[4] > 255 ? 255 : val_r[4]);
                    output[base_idx + 4].g = (unsigned char)(val_g[4] > 255 ? 255 : val_g[4]);
                    output[base_idx + 4].b = (unsigned char)(val_b[4] > 255 ? 255 : val_b[4]);

                    output[base_idx + 5].r = (unsigned char)(val_r[5] > 255 ? 255 : val_r[5]);
                    output[base_idx + 5].g = (unsigned char)(val_g[5] > 255 ? 255 : val_g[5]);
                    output[base_idx + 5].b = (unsigned char)(val_b[5] > 255 ? 255 : val_b[5]);

                    output[base_idx + 6].r = (unsigned char)(val_r[6] > 255 ? 255 : val_r[6]);
                    output[base_idx + 6].g = (unsigned char)(val_g[6] > 255 ? 255 : val_g[6]);
                    output[base_idx + 6].b = (unsigned char)(val_b[6] > 255 ? 255 : val_b[6]);

                    output[base_idx + 7].r = (unsigned char)(val_r[7] > 255 ? 255 : val_r[7]);
                    output[base_idx + 7].g = (unsigned char)(val_g[7] > 255 ? 255 : val_g[7]);
                    output[base_idx + 7].b = (unsigned char)(val_b[7] > 255 ? 255 : val_b[7]);

                    output[base_idx + 8].r = (unsigned char)(val_r[8] > 255 ? 255 : val_r[8]);
                    output[base_idx + 8].g = (unsigned char)(val_g[8] > 255 ? 255 : val_g[8]);
                    output[base_idx + 8].b = (unsigned char)(val_b[8] > 255 ? 255 : val_b[8]);

                    output[base_idx + 9].r = (unsigned char)(val_r[9] > 255 ? 255 : val_r[9]);
                    output[base_idx + 9].g = (unsigned char)(val_g[9] > 255 ? 255 : val_g[9]);
                    output[base_idx + 9].b = (unsigned char)(val_b[9] > 255 ? 255 : val_b[9]);

                    output[base_idx + 10].r = (unsigned char)(val_r[10] > 255 ? 255 : val_r[10]);
                    output[base_idx + 10].g = (unsigned char)(val_g[10] > 255 ? 255 : val_g[10]);
                    output[base_idx + 10].b = (unsigned char)(val_b[10] > 255 ? 255 : val_b[10]);

                    output[base_idx + 11].r = (unsigned char)(val_r[11] > 255 ? 255 : val_r[11]);
                    output[base_idx + 11].g = (unsigned char)(val_g[11] > 255 ? 255 : val_g[11]);
                    output[base_idx + 11].b = (unsigned char)(val_b[11] > 255 ? 255 : val_b[11]);

                    output[base_idx + 12].r = (unsigned char)(val_r[12] > 255 ? 255 : val_r[12]);
                    output[base_idx + 12].g = (unsigned char)(val_g[12] > 255 ? 255 : val_g[12]);
                    output[base_idx + 12].b = (unsigned char)(val_b[12] > 255 ? 255 : val_b[12]);

                    output[base_idx + 13].r = (unsigned char)(val_r[13] > 255 ? 255 : val_r[13]);
                    output[base_idx + 13].g = (unsigned char)(val_g[13] > 255 ? 255 : val_g[13]);
                    output[base_idx + 13].b = (unsigned char)(val_b[13] > 255 ? 255 : val_b[13]);

                    output[base_idx + 14].r = (unsigned char)(val_r[14] > 255 ? 255 : val_r[14]);
                    output[base_idx + 14].g = (unsigned char)(val_g[14] > 255 ? 255 : val_g[14]);
                    output[base_idx + 14].b = (unsigned char)(val_b[14] > 255 ? 255 : val_b[14]);

                    output[base_idx + 15].r = (unsigned char)(val_r[15] > 255 ? 255 : val_r[15]);
                    output[base_idx + 15].g = (unsigned char)(val_g[15] > 255 ? 255 : val_g[15]);
                    output[base_idx + 15].b = (unsigned char)(val_b[15] > 255 ? 255 : val_b[15]);

                }
            }
        }
    }
}


