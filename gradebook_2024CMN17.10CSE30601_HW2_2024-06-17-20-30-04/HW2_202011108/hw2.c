#include "bmplib.h"
#include "hw2.h"
void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    float r = 0;
    float g = 0;
    float b = 0;
    float filter0 = *filter++;
    float filter1 = *filter++;
    float filter2 = *filter++;
    float filter3 = *filter++;
    float filter4 = *filter++;
    float filter5 = *filter++;
    float filter6 = *filter++;
    float filter7 = *filter++;
    float filter8 = *filter;
    unsigned int outputIndex = 0;
    unsigned int xMax = width - 1;
    unsigned int yMax = height - 1;
    int yWidth = 0;
    Pixel* inputPointer = 0;
    Pixel* outputPointer = 0;
    Pixel* inputPointer0 = 0;
    Pixel* inputPointer1 = 0;
    Pixel* inputPointer2 = 0;
    Pixel* inputPointer3 = 0;
    Pixel* inputPointer5 = 0;
    Pixel* inputPointer6 = 0;
    Pixel* inputPointer7 = 0;
    Pixel* inputPointer8 = 0;
////////////////////////////////////////////////
    r += input -> r * filter4;
    g += input -> g * filter4;
    b += input -> b * filter4;
    inputPointer5 = input + 1;
    r += inputPointer5 -> r * filter5;
    g += inputPointer5 -> g * filter5;
    b += inputPointer5 -> b * filter5;
    inputPointer7 = input + width;
    r += inputPointer7 -> r * filter7;
    g += inputPointer7 -> g * filter7;
    b += inputPointer7 -> b * filter7;
    inputPointer8 = inputPointer7 + 1;
    r += inputPointer8 -> r * filter8;
    g += inputPointer8 -> g * filter8;
    b += inputPointer8 -> b * filter8;
    if (r < 0) {
        r = 0;
    }
    else {
        if (r > 255) r = 255;
    }
    if (g < 0) {
        g = 0;
    }
    else {
        if (g > 255) g = 255;
    }
    if (b < 0) {
        b = 0;
    }
    else {
        if (b > 255) b = 255;
    }
    output -> r = (unsigned char)r;
    output -> g = (unsigned char)g;
    output -> b = (unsigned char)b;

    for (int x = 1; x < xMax; ++x) {
        r = 0;
        g = 0;
        b = 0;
        inputPointer = input + x;
        outputPointer = output + x;

        inputPointer3 = inputPointer - 1;
        r += inputPointer3 -> r * filter3;
        g += inputPointer3 -> g * filter3;
        b += inputPointer3 -> b * filter3;
        r += inputPointer -> r * filter4;
        g += inputPointer -> g * filter4;
        b += inputPointer -> b * filter4;
        inputPointer5 = inputPointer + 1;
        r += inputPointer5 -> r * filter5;
        g += inputPointer5 -> g * filter5;
        b += inputPointer5 -> b * filter5;
        inputPointer7 = inputPointer + width;
        inputPointer6 = inputPointer7 - 1;
        r += inputPointer6 -> r * filter6;
        g += inputPointer6 -> g * filter6;
        b += inputPointer6 -> b * filter6;
        r += inputPointer7 -> r * filter7;
        g += inputPointer7 -> g * filter7;
        b += inputPointer7 -> b * filter7;
        inputPointer8 = inputPointer7 + 1;
        r += inputPointer8 -> r * filter8;
        g += inputPointer8 -> g * filter8;
        b += inputPointer8 -> b * filter8;
        if (r < 0) {
            r = 0;
        }
        else {
            if (r > 255) r = 255;
        }
        if (g < 0) {
            g = 0;
        }
        else {
            if (g > 255) g = 255;
        }
        if (b < 0) {
            b = 0;
        }
        else {
            if (b > 255) b = 255;
        }
        outputPointer -> r = (unsigned char)r;
        outputPointer -> g = (unsigned char)g;
        outputPointer -> b = (unsigned char)b;
    }

    r = 0;
    g = 0;
    b = 0;
    outputIndex = width - 1;
    inputPointer = input + outputIndex;
    outputPointer = output + outputIndex;
    inputPointer3 = inputPointer - 1;
    r += inputPointer3 -> r * filter3;
    g += inputPointer3 -> g * filter3;
    b += inputPointer3 -> b * filter3;
    r += inputPointer -> r * filter4;
    g += inputPointer -> g * filter4;
    b += inputPointer -> b * filter4;
    inputPointer7 = inputPointer + width;
    inputPointer6 = inputPointer7 - 1;
    r += inputPointer6 -> r * filter6;
    g += inputPointer6 -> g * filter6;
    b += inputPointer6 -> b * filter6;
    r += inputPointer7 -> r * filter7;
    g += inputPointer7 -> g * filter7;
    b += inputPointer7 -> b * filter7;
    if (r < 0) {
        r = 0;
    }
    else {
        if (r > 255) r = 255;
    }
    if (g < 0) {
        g = 0;
    }
    else {
        if (g > 255) g = 255;
    }
    if (b < 0) {
        b = 0;
    }
    else {
        if (b > 255) b = 255;
    }
    outputPointer -> r = (unsigned char)r;
    outputPointer -> g = (unsigned char)g;
    outputPointer -> b = (unsigned char)b;


    for (int y = 1; y < yMax; ++y) {

        r = 0;
        g = 0;
        b = 0;
        outputIndex = y * width;
        inputPointer = input + outputIndex;
        outputPointer = output + outputIndex;

        inputPointer1 = inputPointer - width;
        r += inputPointer1 -> r * filter1;
        g += inputPointer1 -> g * filter1;
        b += inputPointer1 -> b * filter1;
        inputPointer2 = inputPointer1 + 1;
        r += inputPointer2 -> r * filter2;
        g += inputPointer2 -> g * filter2;
        b += inputPointer2 -> b * filter2;
        r += inputPointer -> r * filter4;
        g += inputPointer -> g * filter4;
        b += inputPointer -> b * filter4;
        inputPointer5 = inputPointer + 1;
        r += inputPointer5 -> r * filter5;
        g += inputPointer5 -> g * filter5;
        b += inputPointer5 -> b * filter5;
        inputPointer7 = inputPointer + width;
        r += inputPointer7 -> r * filter7;
        g += inputPointer7 -> g * filter7;
        b += inputPointer7 -> b * filter7;
        inputPointer8 = inputPointer7 + 1;
        r += inputPointer8 -> r * filter8;
        g += inputPointer8 -> g * filter8;
        b += inputPointer8 -> b * filter8;
        if (r < 0) {
            r = 0;
        }
        else {
            if (r > 255) r = 255;
        }
        if (g < 0) {
            g = 0;
        }
        else {
            if (g > 255) g = 255;
        }
        if (b < 0) {
            b = 0;
        }
        else {
            if (b > 255) b = 255;
        }

        outputPointer -> r = (unsigned char)r;
        outputPointer -> g = (unsigned char)g;
        outputPointer -> b = (unsigned char)b;

        yWidth = y * width;
        for (int x = 1; x < xMax; ++x) {
            r = 0;
            g = 0;
            b = 0;
            outputIndex = x + yWidth;
            inputPointer = input + outputIndex;
            outputPointer = output + outputIndex;

            inputPointer1 = inputPointer - width;
            inputPointer0 = inputPointer1 - 1;
            r += inputPointer0 -> r * filter0;
            g += inputPointer0 -> g * filter0;
            b += inputPointer0 -> b * filter0;
            r += inputPointer1 -> r * filter1;
            g += inputPointer1 -> g * filter1;
            b += inputPointer1 -> b * filter1;
            inputPointer2 = inputPointer1 + 1;
            r += inputPointer2 -> r * filter2;
            g += inputPointer2 -> g * filter2;
            b += inputPointer2 -> b * filter2;
            inputPointer3 = inputPointer - 1;
            r += inputPointer3 -> r * filter3;
            g += inputPointer3 -> g * filter3;
            b += inputPointer3 -> b * filter3;
            r += inputPointer -> r * filter4;
            g += inputPointer -> g * filter4;
            b += inputPointer -> b * filter4;
            inputPointer5 = inputPointer + 1;
            r += inputPointer5 -> r * filter5;
            g += inputPointer5 -> g * filter5;
            b += inputPointer5 -> b * filter5;
            inputPointer7 = inputPointer + width;
            inputPointer6 = inputPointer7 - 1;
            r += inputPointer6 -> r * filter6;
            g += inputPointer6 -> g * filter6;
            b += inputPointer6 -> b * filter6;
            r += inputPointer7 -> r * filter7;
            g += inputPointer7 -> g * filter7;
            b += inputPointer7 -> b * filter7;
            inputPointer8 = inputPointer7 + 1;
            r += inputPointer8 -> r * filter8;
            g += inputPointer8 -> g * filter8;
            b += inputPointer8 -> b * filter8;
            if (r < 0) {
                r = 0;
            }
            else {
                if (r > 255) r = 255;
            }
            if (g < 0) {
                g = 0;
            }
            else {
                if (g > 255) g = 255;
            }
            if (b < 0) {
                b = 0;
            }
            else {
                if (b > 255) b = 255;
            }
            outputPointer -> r = (unsigned char)r;
            outputPointer -> g = (unsigned char)g;
            outputPointer -> b = (unsigned char)b;
        }

        r = 0;
        g = 0;
        b = 0;
        outputIndex = (y + 1)* width - 1;
        inputPointer = input + outputIndex;
        outputPointer = output + outputIndex;

        inputPointer1 = inputPointer - width;
        inputPointer0 = inputPointer1 - 1;
        r += inputPointer0 -> r * filter0;
        g += inputPointer0 -> g * filter0;
        b += inputPointer0 -> b * filter0;
        r += inputPointer1 -> r * filter1;
        g += inputPointer1 -> g * filter1;
        b += inputPointer1 -> b * filter1;

        inputPointer3 = inputPointer - 1;
        r += inputPointer3 -> r * filter3;
        g += inputPointer3 -> g * filter3;
        b += inputPointer3 -> b * filter3;
        r += inputPointer -> r * filter4;
        g += inputPointer -> g * filter4;
        b += inputPointer -> b * filter4;
        inputPointer7 = inputPointer + width;
        inputPointer6 = inputPointer7 - 1;
        r += inputPointer6 -> r * filter6;
        g += inputPointer6 -> g * filter6;
        b += inputPointer6 -> b * filter6;
        r += inputPointer7 -> r * filter7;
        g += inputPointer7 -> g * filter7;
        b += inputPointer7 -> b * filter7;
        if (r < 0) {
            r = 0;
        }
        else {
            if (r > 255) r = 255;
        }
        if (g < 0) {
            g = 0;
        }
        else {
            if (g > 255) g = 255;
        }
        if (b < 0) {
            b = 0;
        }
        else {
            if (b > 255) b = 255;
        }
        outputPointer -> r = (unsigned char)r;
        outputPointer -> g = (unsigned char)g;
        outputPointer -> b = (unsigned char)b;
    }
    /////////////////////////////////////////

    r = 0;
    g = 0;
    b = 0;
    outputIndex = yMax * width;
    inputPointer = input + outputIndex;
    outputPointer = output + outputIndex;

    inputPointer1 = inputPointer - width;
    r += inputPointer1 -> r * filter1;
    g += inputPointer1 -> g * filter1;
    b += inputPointer1 -> b * filter1;
    inputPointer2 = inputPointer1 + 1;
    r += inputPointer2 -> r * filter2;
    g += inputPointer2 -> g * filter2;
    b += inputPointer2 -> b * filter2;
    r += inputPointer -> r * filter4;
    g += inputPointer -> g * filter4;
    b += inputPointer -> b * filter4;
    inputPointer5 = inputPointer + 1;
    r += inputPointer5 -> r * filter5;
    g += inputPointer5 -> g * filter5;
    b += inputPointer5 -> b * filter5;

    if (r < 0) {
        r = 0;
    }
    else {
        if (r > 255) r = 255;
    }
    if (g < 0) {
        g = 0;
    }
    else {
        if (g > 255) g = 255;
    }
    if (b < 0) {
        b = 0;
    }
    else {
        if (b > 255) b = 255;
    }

    outputPointer -> r = (unsigned char)r;
    outputPointer -> g = (unsigned char)g;
    outputPointer -> b = (unsigned char)b;

    yWidth = yMax * width;
    for (int x = 1; x < xMax; ++x) {
        r = 0;
        g = 0;
        b = 0;
        outputIndex = x + yWidth;
        inputPointer = input + outputIndex;
        outputPointer = output + outputIndex;

        inputPointer1 = inputPointer - width;
        inputPointer0 = inputPointer1 - 1;
        r += inputPointer0 -> r * filter0;
        g += inputPointer0 -> g * filter0;
        b += inputPointer0 -> b * filter0;
        r += inputPointer1 -> r * filter1;
        g += inputPointer1 -> g * filter1;
        b += inputPointer1 -> b * filter1;
        inputPointer2 = inputPointer1 + 1;
        r += inputPointer2 -> r * filter2;
        g += inputPointer2 -> g * filter2;
        b += inputPointer2 -> b * filter2;
        inputPointer3 = inputPointer - 1;
        r += inputPointer3 -> r * filter3;
        g += inputPointer3 -> g * filter3;
        b += inputPointer3 -> b * filter3;
        r += inputPointer -> r * filter4;
        g += inputPointer -> g * filter4;
        b += inputPointer -> b * filter4;
        inputPointer5 = inputPointer + 1;
        r += inputPointer5 -> r * filter5;
        g += inputPointer5 -> g * filter5;
        b += inputPointer5 -> b * filter5;
        if (r < 0) {
            r = 0;
        }
        else {
            if (r > 255) r = 255;
        }
        if (g < 0) {
            g = 0;
        }
        else {
            if (g > 255) g = 255;
        }
        if (b < 0) {
            b = 0;
        }
        else {
            if (b > 255) b = 255;
        }
        outputPointer -> r = (unsigned char)r;
        outputPointer -> g = (unsigned char)g;
        outputPointer -> b = (unsigned char)b;
    }

    r = 0;
    g = 0;
    b = 0;
    outputIndex = height * width - 1;
    inputPointer = input + outputIndex;
    outputPointer = output + outputIndex;

    inputPointer1 = inputPointer - width;
    inputPointer0 = inputPointer1 - 1;
    r += inputPointer0 -> r * filter0;
    g += inputPointer0 -> g * filter0;
    b += inputPointer0 -> b * filter0;
    r += inputPointer1 -> r * filter1;
    g += inputPointer1 -> g * filter1;
    b += inputPointer1 -> b * filter1;

    inputPointer3 = inputPointer - 1;
    r += inputPointer3 -> r * filter3;
    g += inputPointer3 -> g * filter3;
    b += inputPointer3 -> b * filter3;
    r += inputPointer -> r * filter4;
    g += inputPointer -> g * filter4;
    b += inputPointer -> b * filter4;
    if (r < 0) {
        r = 0;
    }
    else {
        if (r > 255) r = 255;
    }
    if (g < 0) {
        g = 0;
    }
    else {
        if (g > 255) g = 255;
    }
    if (b < 0) {
        b = 0;
    }
    else {
        if (b > 255) b = 255;
    }
    outputPointer -> r = (unsigned char)r;
    outputPointer -> g = (unsigned char)g;
    outputPointer -> b = (unsigned char)b;
}