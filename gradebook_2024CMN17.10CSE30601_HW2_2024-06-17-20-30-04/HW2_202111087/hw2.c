#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmplib.h"
#include "hw2.h"

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    const float* filter = (const float*)args[4];
    Pixel pNW, pN, pNE, pW, pC, pE, pSW, pS, pSE;

    double r, g, b;
    int x, y;
    int rowOffset, pixelIndex;

    //내부
    rowOffset = 0;
    for (y = 1; y < height - 1; ++y) {
        rowOffset += width;

        pNW = input[rowOffset - width];
        pN  = input[rowOffset - width + 1];
        pW  = input[rowOffset];
        pC  = input[rowOffset + 1];
        pSW = input[rowOffset + width];
        pS  = input[rowOffset + width + 1];

        for (x = 1; x < width - 1; ++x) {
            pixelIndex = x + rowOffset;
            pNE = input[pixelIndex - width + 1];
            pE  = input[pixelIndex + 1];
            pSE = input[pixelIndex + width + 1];

            r = pNW.r * filter[0] + pN.r * filter[1] + pNE.r * filter[2] +
                pW.r * filter[3] + pC.r * filter[4] + pE.r * filter[5] +
                pSW.r * filter[6] + pS.r * filter[7] + pSE.r * filter[8];
            g = pNW.g * filter[0] + pN.g * filter[1] + pNE.g * filter[2] +
                pW.g * filter[3] + pC.g * filter[4] + pE.g * filter[5] +
                pSW.g * filter[6] + pS.g * filter[7] + pSE.g * filter[8];
            b = pNW.b * filter[0] + pN.b * filter[1] + pNE.b * filter[2] +
                pW.b * filter[3] + pC.b * filter[4] + pE.b * filter[5] +
                pSW.b * filter[6] + pS.b * filter[7] + pSE.b * filter[8];

            output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
            output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
            output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));
        
            pNW = pN;
            pN = pNE;
            pW = pC;
            pC = pE;
            pSW = pS;
            pS = pSE;
        }
    }

    // 가장자리 처리
    // 상단
    pixelIndex = 1;
    for (x = 1; x < width-1; ++x){
        pW  = input[pixelIndex - 1];
        pC  = input[pixelIndex];
        pE  = input[pixelIndex + 1];
        pSW = input[pixelIndex + width - 1];
        pS  = input[pixelIndex + width];
        pSE = input[pixelIndex + width + 1];

        r = pW.r * filter[3] + pC.r * filter[4] + pE.r * filter[5] +
            pSW.r * filter[6] + pS.r * filter[7] + pSE.r * filter[8];
        g = pW.g * filter[3] + pC.g * filter[4] + pE.g * filter[5] +
            pSW.g * filter[6] + pS.g * filter[7] + pSE.g * filter[8];
        b = pW.b * filter[3] + pC.b * filter[4] + pE.b * filter[5] +
            pSW.b * filter[6] + pS.b * filter[7] + pSE.b * filter[8];

        output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
        output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
        output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));

        pixelIndex++;
    }

    //하단
    pixelIndex = (height-1) * width + 1;
    for (x = 1; x < width-1; ++x){
        pNW = input[pixelIndex - width - 1];
        pN  = input[pixelIndex - width];
        pNE = input[pixelIndex - width + 1];
        pW  = input[pixelIndex - 1];
        pC  = input[pixelIndex];
        pE  = input[pixelIndex + 1];

        r = pNW.r * filter[0] + pN.r * filter[1] + pNE.r * filter[2] +
            pW.r * filter[3] + pC.r * filter[4] + pE.r * filter[5];
        g = pNW.g * filter[0] + pN.g * filter[1] + pNE.g * filter[2] +
            pW.g * filter[3] + pC.g * filter[4] + pE.g * filter[5];
        b = pNW.b * filter[0] + pN.b * filter[1] + pNE.b * filter[2] +
            pW.b * filter[3] + pC.b * filter[4] + pE.b * filter[5];

        output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
        output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
        output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));

        pixelIndex++;
    }

    //좌측
    pixelIndex = width;
    for (y = 1; y < height-1; ++y){
        pN  = input[pixelIndex - width];
        pNE = input[pixelIndex - width + 1];
        pC  = input[pixelIndex];
        pE  = input[pixelIndex + 1];
        pS  = input[pixelIndex + width];
        pSE = input[pixelIndex + width + 1];
        
        r = pN.r * filter[1] + pNE.r * filter[2] +
            pC.r * filter[4] + pE.r * filter[5] +
            pS.r * filter[7] + pSE.r * filter[8];
        g = pN.g * filter[1] + pNE.g * filter[2] +
            pC.g * filter[4] + pE.g * filter[5] +
            pS.g * filter[7] + pSE.g * filter[8];
        b = pN.b * filter[1] + pNE.b * filter[2] +
            pC.b * filter[4] + pE.b * filter[5] +
            pS.b * filter[7] + pSE.b * filter[8];
            
        output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
        output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
        output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));

        pixelIndex+=width;
    }

    //우측
    pixelIndex = width + width - 1;
    for (x = 1; x < width-1; ++x){
        pNW = input[pixelIndex - width - 1];
        pN  = input[pixelIndex - width];
        pW  = input[pixelIndex - 1];
        pC  = input[pixelIndex];
        pSW = input[pixelIndex + width - 1];
        pS  = input[pixelIndex + width];

        r = pNW.r * filter[0] + pN.r * filter[1] +
            pW.r * filter[3] + pC.r * filter[4] +
            pSW.r * filter[6] + pS.r * filter[7];
        g = pNW.g * filter[0] + pN.g * filter[1] +
            pW.g * filter[3] + pC.g * filter[4] +
            pSW.g * filter[6] + pS.g * filter[7];
        b = pNW.b * filter[0] + pN.b * filter[1] +
            pW.b * filter[3] + pC.b * filter[4] +
            pSW.b * filter[6] + pS.b * filter[7];

        output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
        output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
        output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));

        pixelIndex+=width;
    }

    //TL
    pixelIndex=0;
    r = input[pixelIndex].r * filter[4] + input[pixelIndex+1].r * filter[5] +
        input[pixelIndex+width].r * filter[7] + input[pixelIndex+width+1].r * filter[8];
    g = input[pixelIndex].g * filter[4] + input[pixelIndex+1].g * filter[5] +
        input[pixelIndex+width].g * filter[7] + input[pixelIndex+width+1].g * filter[8];
    b = input[pixelIndex].b * filter[4] + input[pixelIndex+1].b * filter[5] +
        input[pixelIndex+width].b * filter[7] + input[pixelIndex+width+1].b * filter[8];

    output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
    output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
    output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));
    //TR
    pixelIndex=width-1;
    r = input[pixelIndex-1].r * filter[3] + input[pixelIndex].r * filter[4] +
        input[pixelIndex+width-1].r * filter[6] + input[pixelIndex+width].r * filter[7];
    g = input[pixelIndex-1].g * filter[3] + input[pixelIndex].g * filter[4] +
        input[pixelIndex+width-1].g * filter[6] + input[pixelIndex+width].g * filter[7];
    b = input[pixelIndex-1].b * filter[3] + input[pixelIndex].b * filter[4] +
        input[pixelIndex+width-1].b * filter[6] + input[pixelIndex+width].b * filter[7];

    output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
    output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
    output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));
    //BL
    pixelIndex= (height-1) * width;
    r = input[pixelIndex-width].r * filter[1] + input[pixelIndex-width+1].r * filter[2] +
        input[pixelIndex].r * filter[4] + input[pixelIndex+1].r * filter[5];
    g = input[pixelIndex-width].g * filter[1] + input[pixelIndex-width+1].g * filter[2] +
        input[pixelIndex].g * filter[4] + input[pixelIndex+1].g * filter[5];
    b = input[pixelIndex-width].b * filter[1] + input[pixelIndex-width+1].b * filter[2] +
        input[pixelIndex].b * filter[4] + input[pixelIndex+1].b * filter[5];

    output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
    output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
    output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));
    //BR
    pixelIndex= height * width - 1;
    r = input[pixelIndex-width-1].r * filter[0] + input[pixelIndex-width].r * filter[1] +
        input[pixelIndex-1].r * filter[3] + input[pixelIndex].r * filter[4];
    g = input[pixelIndex-width-1].g * filter[0] + input[pixelIndex-width].g * filter[1] +
        input[pixelIndex-1].g * filter[3] + input[pixelIndex].g * filter[4];
    b = input[pixelIndex-width-1].b * filter[0] + input[pixelIndex-width].b * filter[1] +
        input[pixelIndex-1].b * filter[3] + input[pixelIndex].b * filter[4];

    output[pixelIndex].r = (unsigned char) fmin(255, fmax(0, r));
    output[pixelIndex].g = (unsigned char) fmin(255, fmax(0, g));
    output[pixelIndex].b = (unsigned char) fmin(255, fmax(0, b));
}
