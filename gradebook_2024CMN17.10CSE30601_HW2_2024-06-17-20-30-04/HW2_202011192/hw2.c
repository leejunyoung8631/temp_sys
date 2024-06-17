#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

Pixel* create_padded_input(Pixel* input, int width, int height) {

    int padded_width = width + 2;
    int padded_height = height + 2;

    //padding을 해주는게 훨씬 나아. 절대 빼지 말자
    Pixel* padded_input = (Pixel*)calloc(padded_width * padded_height, sizeof(Pixel));

    for (int y = 0; y < height; ++y) {

        int src_row_offset = y * width;
        int dst_row_offset = (y + 1) * padded_width + 1;


        memcpy(&padded_input[dst_row_offset], &input[src_row_offset], width * sizeof(Pixel));
    }

    return padded_input;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];


    int fi[9];

    //optimization 4
    for (int i = 0; i < 9; ++i) {
        
        fi[i] = (int)(filter[i] * 256);  
    }


    int padded_width = width + 2;
    Pixel* padded_input = create_padded_input(input, width, height);


    for (int y = 0; y < height; ++y) {
        int output_row_offset = y * width;
        int padded_row_offset = (y + 1) * padded_width + 1;

        for (int x = 0; x < width; x += 4) {

            //아 여기 조건문 없애고 싶은데,,
            for (int k = 0; k < 4 && x + k < width; ++k) {
                int center_idx = padded_row_offset + x + k;


                int idx_topleft     = center_idx - padded_width - 1;
                int idx_topcenter   = center_idx - padded_width;
                int idx_topright    = center_idx - padded_width + 1;
                int idx_middleleft  = center_idx - 1;
                int idx_middleright = center_idx + 1;

                int idx_bottomleft  = center_idx + padded_width - 1;
                int idx_bottomcenter= center_idx + padded_width;
                int idx_bottomright = center_idx + padded_width + 1;



                int r = 0, g = 0, b = 0;


                //여기 순차적으로 연산해주자. 
                r += padded_input[idx_topleft].r     * fi[0];
                g += padded_input[idx_topleft].g     * fi[0];
                b += padded_input[idx_topleft].b     * fi[0];

                r += padded_input[idx_topcenter].r   * fi[1];
                g += padded_input[idx_topcenter].g   * fi[1];
                b += padded_input[idx_topcenter].b   * fi[1];

                r += padded_input[idx_topright].r    * fi[2];
                g += padded_input[idx_topright].g    * fi[2];
                b += padded_input[idx_topright].b    * fi[2];

                r += padded_input[idx_middleleft].r  * fi[3];
                g += padded_input[idx_middleleft].g  * fi[3];
                b += padded_input[idx_middleleft].b  * fi[3];

                r += padded_input[center_idx].r      * fi[4];
                g += padded_input[center_idx].g      * fi[4];
                b += padded_input[center_idx].b      * fi[4];

                r += padded_input[idx_middleright].r * fi[5];
                g += padded_input[idx_middleright].g * fi[5];
                b += padded_input[idx_middleright].b * fi[5];

                r += padded_input[idx_bottomleft].r  * fi[6];
                g += padded_input[idx_bottomleft].g  * fi[6];
                b += padded_input[idx_bottomleft].b  * fi[6];

                r += padded_input[idx_bottomcenter].r* fi[7];
                g += padded_input[idx_bottomcenter].g* fi[7];
                b += padded_input[idx_bottomcenter].b* fi[7];

                r += padded_input[idx_bottomright].r * fi[8];
                g += padded_input[idx_bottomright].g * fi[8];
                b += padded_input[idx_bottomright].b * fi[8];



                r = (r >> 8) < 0 ? 0 : (r >> 8) > 255 ? 255 : (r >> 8);
                g = (g >> 8) < 0 ? 0 : (g >> 8) > 255 ? 255 : (g >> 8);
                b = (b >> 8) < 0 ? 0 : (b >> 8) > 255 ? 255 : (b >> 8);


                Pixel p;
                p.r = (unsigned char)r;
                p.g = (unsigned char)g;
                p.b = (unsigned char)b;

                output[output_row_offset + x + k] = p;
            }
        }
    }



    free(padded_input);
}
