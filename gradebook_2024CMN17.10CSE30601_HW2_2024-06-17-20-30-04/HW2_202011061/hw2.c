#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"



static inline void convolution(Pixel* input, int x, int y, int width, int height, float* filter, Pixel* output, int num) {
    float r = 0;
    float g = 0;
    float b = 0;

char x_start = (x == 0) ? 1 : 0;
char x_end = (x == (width - 1)) ?  1 : 0;
char y_start = (y == 0) ? 1 : 0;
char y_end = (y == (height - 1)) ? 1 : 0;

int idx1 = num - width;
int idx0 = idx1 - 1;
int idx2 = idx1 + 1;

int idx3 = num-1;
int idx4 = num;
int idx5 = idx4 + 1;

int idx6 = idx3 + width;
int idx7 = idx6 + 1;
int idx8 = idx7 + 1;

r += input[idx4].r * filter[4];
g += input[idx4].g * filter[4];
b += input[idx4].b * filter[4];

    if (!x_start && !y_start && !x_end && !y_end) {
        r += input[idx0].r * filter[0]; r += input[idx1].r * filter[1]; r += input[idx2].r * filter[2];
        g += input[idx0].g * filter[0]; g += input[idx1].g * filter[1]; g += input[idx2].g * filter[2];
        b += input[idx0].b * filter[0]; b += input[idx1].b * filter[1]; b += input[idx2].b * filter[2];
        r += input[idx3].r * filter[3]; r += input[idx5].r * filter[5];
        g += input[idx3].g * filter[3]; g += input[idx5].g * filter[5];
        b += input[idx3].b * filter[3]; b += input[idx5].b * filter[5];
        r += input[idx6].r * filter[6]; r += input[idx7].r * filter[7]; r += input[idx8].r * filter[8];
        g += input[idx6].g * filter[6]; g += input[idx7].g * filter[7]; g += input[idx8].g * filter[8];
        b += input[idx6].b * filter[6]; b += input[idx7].b * filter[7]; b += input[idx8].b * filter[8];
    }  
    else if (x_start) {
	 r += input[idx5].r * filter[5];
        g += input[idx5].g * filter[5];
        b += input[idx5].b * filter[5];

	    if(y_start){
        // Top-left corner
               r += input[idx7].r * filter[7]; r += input[idx8].r * filter[8];
        g += input[idx7].g * filter[7]; g += input[idx8].g * filter[8];
        b += input[idx7].b * filter[7]; b += input[idx8].b * filter[8];
	    }
	else if (y_end) {
        // Bottom-left corner
        r += input[idx1].r * filter[1]; r += input[idx2].r * filter[2];
        g += input[idx1].g * filter[1]; g += input[idx2].g * filter[2];
        b += input[idx1].b * filter[1]; b += input[idx2].b * filter[2];
    	}
	    else{ r += input[idx1].r * filter[1]; r += input[idx2].r * filter[2];
        g += input[idx1].g * filter[1]; g += input[idx2].g * filter[2];
        b += input[idx1].b * filter[1]; b += input[idx2].b * filter[2];
    	r += input[idx7].r * filter[7]; r += input[idx8].r * filter[8];
        g += input[idx7].g * filter[7]; g += input[idx8].g * filter[8];
        b += input[idx7].b * filter[7]; b += input[idx8].b * filter[8];
	}
    }	
    else if (x_end) {
	r += input[idx3].r * filter[3];
        g += input[idx3].g * filter[3];
        b += input[idx3].b * filter[3];

	    if(y_start){
        // Top-right corner
        r += input[idx6].r * filter[6]; r += input[idx7].r * filter[7];
        g += input[idx6].g * filter[6]; g += input[idx7].g * filter[7];
        b += input[idx6].b * filter[6]; b += input[idx7].b * filter[7];
	}    
	else if (y_end) {
        // Bottom-right corner
        r += input[idx0].r * filter[0]; r += input[idx1].r * filter[1];
        g += input[idx0].g * filter[0]; g += input[idx1].g * filter[1];
        b += input[idx0].b * filter[0]; b += input[idx1].b * filter[1];
    	}
	    else{r += input[idx0].r * filter[0]; r += input[idx1].r * filter[1];
        g += input[idx0].g * filter[0]; g += input[idx1].g * filter[1];
        b += input[idx0].b * filter[0]; b += input[idx1].b * filter[1];
	r += input[idx6].r * filter[6]; r += input[idx7].r * filter[7];
        g += input[idx6].g * filter[6]; g += input[idx7].g * filter[7];
        b += input[idx6].b * filter[6]; b += input[idx7].b * filter[7];
	}    
}	
   
    else if (y_start) {
        // Top edge
        r += input[idx3].r * filter[3]; r += input[idx5].r * filter[5];
        g += input[idx3].g * filter[3]; g += input[idx5].g * filter[5];
        b += input[idx3].b * filter[3]; b += input[idx5].b * filter[5];
        r += input[idx6].r * filter[6]; r += input[idx7].r * filter[7]; r += input[idx8].r * filter[8];
        g += input[idx6].g * filter[6]; g += input[idx7].g * filter[7]; g += input[idx8].g * filter[8];
        b += input[idx6].b * filter[6]; b += input[idx7].b * filter[7]; b += input[idx8].b * filter[8];
    } else if (y_end) {
        // Bottom edge
        r += input[idx0].r * filter[0]; r += input[idx1].r * filter[1]; r += input[idx2].r * filter[2];
        g += input[idx0].g * filter[0]; g += input[idx1].g * filter[1]; g += input[idx2].g * filter[2];
        b += input[idx0].b * filter[0]; b += input[idx1].b * filter[1]; b += input[idx2].b * filter[2];
        r += input[idx3].r * filter[3]; r += input[idx5].r * filter[5];
        g += input[idx3].g * filter[3]; g += input[idx5].g * filter[5];
        b += input[idx3].b * filter[3]; b += input[idx5].b * filter[5];
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    output[num].r = (unsigned char)r;
    output[num].g = (unsigned char)g;
    output[num].b = (unsigned char)b;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
   
    int tall = 0-width; 
    for (int y = 0; y < height; ++y) {
	tall += width;
        for (int x = 0; x < width; ++x) {
            convolution(input, x, y, width, height, filter, output, tall+x);
        }
    }
    
}
