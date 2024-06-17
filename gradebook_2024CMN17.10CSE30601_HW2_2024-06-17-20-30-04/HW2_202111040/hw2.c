#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bmplib.h"
#include "hw2.h"

static Pixel convolution(Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    int dx, dy;
    for (dy = -1; dy <= 1; ++dy) {
        for (dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;

            if ((unsigned)nx < width && (unsigned)ny < height) {
                Pixel* pixel = &input[nx + ny * width];
                float coeff = filter[(dx + 1) + (dy + 1) * 3];

                r += pixel->r * coeff;
                g += pixel->g * coeff;
                b += pixel->b * coeff;
            }
        }
    }

    r = r < 0 ? 0 : (r > 255 ? 255 : r);
    g = g < 0 ? 0 : (g > 255 ? 255 : g);
    b = b < 0 ? 0 : (b > 255 ? 255 : b);

    Pixel p = {(unsigned char)r, (unsigned char)g, (unsigned char)b};
    return p;
}

void filter_baseline(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            output[x + y * width] = convolution(input, x, y, width, height, filter);
        }
    }
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r = 0, g = 0, b = 0;

            // Precompute bounds
            int x_minus_1 = x - 1;
            int x_plus_1 = x + 1;
            int y_minus_1 = y - 1;
            int y_plus_1 = y + 1;

            // Unroll the loop manually
            if ((unsigned)x_minus_1 < width && (unsigned)y_minus_1 < height) {
                Pixel* pixel = &input[x_minus_1 + y_minus_1 * width];
                r += pixel->r * filter[0];
                g += pixel->g * filter[0];
                b += pixel->b * filter[0];
            }
            if ((unsigned)x < width && (unsigned)y_minus_1 < height) {
                Pixel* pixel = &input[x + y_minus_1 * width];
                r += pixel->r * filter[1];
                g += pixel->g * filter[1];
                b += pixel->b * filter[1];
            }
            if ((unsigned)x_plus_1 < width && (unsigned)y_minus_1 < height) {
                Pixel* pixel = &input[x_plus_1 + y_minus_1 * width];
                r += pixel->r * filter[2];
                g += pixel->g * filter[2];
                b += pixel->b * filter[2];
            }
            if ((unsigned)x_minus_1 < width && (unsigned)y < height) {
                Pixel* pixel = &input[x_minus_1 + y * width];
                r += pixel->r * filter[3];
                g += pixel->g * filter[3];
                b += pixel->b * filter[3];
            }
            if ((unsigned)x < width && (unsigned)y < height) {
                Pixel* pixel = &input[x + y * width];
                r += pixel->r * filter[4];
                g += pixel->g * filter[4];
                b += pixel->b * filter[4];
            }
            if ((unsigned)x_plus_1 < width && (unsigned)y < height) {
                Pixel* pixel = &input[x_plus_1 + y * width];
                r += pixel->r * filter[5];
                g += pixel->g * filter[5];
                b += pixel->b * filter[5];
            }
            if ((unsigned)x_minus_1 < width && (unsigned)y_plus_1 < height) {
                Pixel* pixel = &input[x_minus_1 + y_plus_1 * width];
                r += pixel->r * filter[6];
                g += pixel->g * filter[6];
                b += pixel->b * filter[6];
            }
            if ((unsigned)x < width && (unsigned)y_plus_1 < height) {
                Pixel* pixel = &input[x + y_plus_1 * width];
                r += pixel->r * filter[7];
                g += pixel->g * filter[7];
                b += pixel->b * filter[7];
            }
            if ((unsigned)x_plus_1 < width && (unsigned)y_plus_1 < height) {
                Pixel* pixel = &input[x_plus_1 + y_plus_1 * width];
                r += pixel->r * filter[8];
                g += pixel->g * filter[8];
                b += pixel->b * filter[8];
            }

            // Clamp color values to the range [0, 255]
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);

            // Assign to output pixel
            Pixel p = {(unsigned char)r, (unsigned char)g, (unsigned char)b};
            output[x + y * width] = p;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input BMP> <output BMP>\n", argv[0]);
        return 1;
    }

    BMP* bmp = load_bmp(argv[1]);
    if (bmp == NULL) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    unsigned int width = bmp->width;
    unsigned int height = bmp->height;
    Pixel* input = bmp->pixels;

    Pixel* output_baseline = (Pixel*)malloc(width * height * sizeof(Pixel));
    Pixel* output_optimized = (Pixel*)malloc(width * height * sizeof(Pixel));
    if (output_baseline == NULL || output_optimized == NULL) {
        fprintf(stderr, "Error allocating memory for output image\n");
        unload_bmp(bmp);
        if (output_baseline) free(output_baseline);
        if (output_optimized) free(output_optimized);
        return 1;
    }

    // Define filter kernel
    float filter[9] = {
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0
    };

    void* args_baseline[5] = {&width, &height, input, output_baseline, filter};
    void* args_optimized[5] = {&width, &height, input, output_optimized, filter};

    // Baseline filter timing
    clock_t start_baseline = clock();
    filter_baseline(args_baseline);
    clock_t end_baseline = clock();
    double time_spent_baseline = (double)(end_baseline - start_baseline) / CLOCKS_PER_SEC;
    printf("Baseline filter average time: %f seconds\n", time_spent_baseline);

    // Optimized filter timing
    clock_t start_optimized = clock();
    filter_optimized(args_optimized);
    clock_t end_optimized = clock();
    double time_spent_optimized = (double)(end_optimized - start_optimized) / CLOCKS_PER_SEC;
    printf("Optimized filter average time: %f seconds\n", time_spent_optimized);

    // Speedup calculation
    double speedup = time_spent_baseline / time_spent_optimized;
    printf("Your speedup: %f\n", speedup);

    fill_bmp(bmp, output_optimized);
    save_bmp(bmp, argv[2]);

    unload_bmp(bmp);
    free(output_baseline);
    free(output_optimized);

    return 0;
}
