#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

#define CACHE_LINE_SIZE 64
#define PIXELS_PER_LINE (CACHE_LINE_SIZE / sizeof(Pixel))

static Pixel convolution_optimized(Pixel *image, int x, int y, int imageWidth, int imageHeight, float *filterKernel) {
    double redChannel = 0, greenChannel = 0, blueChannel = 0;
    const int startX = x - 1, endX = x + 1;
    const int startY = y - 1, endY = y + 1;
    int filterIndex = 0;

    for (int currentY = startY; currentY <= endY; ++currentY) {
        if (currentY < 0 || currentY >= imageHeight) {
            filterIndex += 3; 
            continue;
        }
        Pixel *rowStart = image + currentY * imageWidth;

        for (int currentX = startX; currentX <= endX; ++currentX, ++filterIndex) {
            if (currentX < 0 || currentX >= imageWidth) continue;
            Pixel *currentPixel = rowStart + currentX;
            redChannel += currentPixel->r * filterKernel[filterIndex];
            greenChannel += currentPixel->g * filterKernel[filterIndex];
            blueChannel += currentPixel->b * filterKernel[filterIndex];
        }
    }

    return (Pixel){
        .r = (unsigned char)(redChannel < 0 ? 0 : (redChannel > 255 ? 255 : redChannel)),
        .g = (unsigned char)(greenChannel < 0 ? 0 : (greenChannel > 255 ? 255 : greenChannel)),
        .b = (unsigned char)(blueChannel < 0 ? 0 : (blueChannel > 255 ? 255 : blueChannel))
    };
}

void filter_optimized(void *arguments[]) {
    unsigned int imageWidth = *(unsigned int *)arguments[0];
    unsigned int imageHeight = *(unsigned int *)arguments[1];
    Pixel *inputImage = arguments[2];
    Pixel *outputImage = arguments[3];
    float *filterKernel = arguments[4];

    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            outputImage[y * imageWidth + x] = convolution_optimized(inputImage, x, y, imageWidth, imageHeight, filterKernel);
        }
    }
}
