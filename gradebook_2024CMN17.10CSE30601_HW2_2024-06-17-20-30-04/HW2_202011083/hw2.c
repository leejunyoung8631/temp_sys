#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

#define CLAMP(val) ((val) < 0 ? 0 : ((val) > 255 ? 255 : (val)))
#define PREFETCH(ptr) __builtin_prefetch(ptr, 0, 3)

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];
    const int y_offsets[3] = {-1, 0, 1};
    const int x_offsets[3] = {-1, 0, 1};
    float filter_weights[9];
    for (int i = 0; i < 9; ++i) {
        filter_weights[i] = filter[i];
    }
    Pixel aligned_input[width * height] __attribute__((aligned(16)));
    memcpy(aligned_input, input, width * height * sizeof(Pixel));

    for (unsigned int y = 1; y < height - 1; ++y) {
        for (unsigned int x = 1; x < width - 1; x += 8) {
            Pixel* out_pixel0 = &output[y * width + x];
            Pixel* out_pixel1 = &output[y * width + x + 1];
            Pixel* out_pixel2 = &output[y * width + x + 2];
            Pixel* out_pixel3 = &output[y * width + x + 3];
            Pixel* out_pixel4 = &output[y * width + x + 4];
            Pixel* out_pixel5 = &output[y * width + x + 5];
            Pixel* out_pixel6 = &output[y * width + x + 6];
            Pixel* out_pixel7 = &output[y * width + x + 7];

            float r[8] = {0.0f}, g[8] = {0.0f}, b[8] = {0.0f};

            for (int dy = 0; dy < 3; ++dy) {
                const Pixel* current_row = aligned_input + (y + y_offsets[dy]) * width + x - 1;
                PREFETCH(current_row + 16);
                for (int dx = 0; dx < 3; ++dx) {
                    float weight = filter_weights[dy * 3 + dx];
                    const Pixel* current_pixel0 = &current_row[dx];
                    const Pixel* current_pixel1 = &current_row[dx + 1];
                    const Pixel* current_pixel2 = &current_row[dx + 2];
                    const Pixel* current_pixel3 = &current_row[dx + 3];
                    const Pixel* current_pixel4 = &current_row[dx + 4];
                    const Pixel* current_pixel5 = &current_row[dx + 5];
                    const Pixel* current_pixel6 = &current_row[dx + 6];
                    const Pixel* current_pixel7 = &current_row[dx + 7];

                    r[0] += current_pixel0->r * weight;
                    g[0] += current_pixel0->g * weight;
                    b[0] += current_pixel0->b * weight;

                    r[1] += current_pixel1->r * weight;
                    g[1] += current_pixel1->g * weight;
                    b[1] += current_pixel1->b * weight;

                    r[2] += current_pixel2->r * weight;
                    g[2] += current_pixel2->g * weight;
                    b[2] += current_pixel2->b * weight;

                    r[3] += current_pixel3->r * weight;
                    g[3] += current_pixel3->g * weight;
                    b[3] += current_pixel3->b * weight;

                    r[4] += current_pixel4->r * weight;
                    g[4] += current_pixel4->g * weight;
                    b[4] += current_pixel4->b * weight;

                    r[5] += current_pixel5->r * weight;
                    g[5] += current_pixel5->g * weight;
                    b[5] += current_pixel5->b * weight;

                    r[6] += current_pixel6->r * weight;
                    g[6] += current_pixel6->g * weight;
                    b[6] += current_pixel6->b * weight;

                    r[7] += current_pixel7->r * weight;
                    g[7] += current_pixel7->g * weight;
                    b[7] += current_pixel7->b * weight;
                }
            }

            out_pixel0->r = CLAMP(r[0]);
            out_pixel0->g = CLAMP(g[0]);
            out_pixel0->b = CLAMP(b[0]);

            out_pixel1->r = CLAMP(r[1]);
            out_pixel1->g = CLAMP(g[1]);
            out_pixel1->b = CLAMP(b[1]);

            out_pixel2->r = CLAMP(r[2]);
            out_pixel2->g = CLAMP(g[2]);
            out_pixel2->b = CLAMP(b[2]);

            out_pixel3->r = CLAMP(r[3]);
            out_pixel3->g = CLAMP(g[3]);
            out_pixel3->b = CLAMP(b[3]);

            out_pixel4->r = CLAMP(r[4]);
            out_pixel4->g = CLAMP(g[4]);
            out_pixel4->b = CLAMP(b[4]);

            out_pixel5->r = CLAMP(r[5]);
            out_pixel5->g = CLAMP(g[5]);
            out_pixel5->b = CLAMP(b[5]);

            out_pixel6->r = CLAMP(r[6]);
            out_pixel6->g = CLAMP(g[6]);
            out_pixel6->b = CLAMP(b[6]);

            out_pixel7->r = CLAMP(r[7]);
            out_pixel7->g = CLAMP(g[7]);
            out_pixel7->b = CLAMP(b[7]);
        }
    }

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                float r = 0.0f, g = 0.0f, b = 0.0f;
                for (int dy = 0; dy < 3; ++dy) {
                    int yy = y + y_offsets[dy];
                    if (yy < 0 || yy >= height) continue;
                    for (int dx = 0; dx < 3; ++dx) {
                        int xx = x + x_offsets[dx];
                        if (xx < 0 || xx >= width) continue;
                        const Pixel* current_pixel = &aligned_input[yy * width + xx];
                        float weight = filter_weights[dy * 3 + dx];
                        r += current_pixel->r * weight;
                        g += current_pixel->g * weight;
                        b += current_pixel->b * weight;
                    }
                }
                output[y * width + x].r = CLAMP(r);
                output[y * width + x].g = CLAMP(g);
                output[y * width + x].b = CLAMP(b);
            }
        }
    }
}

