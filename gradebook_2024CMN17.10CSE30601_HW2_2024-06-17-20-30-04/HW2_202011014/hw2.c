#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

#define CLAMP(value) ((value) < 0 ? 0 : ((value) > 255 ? 255 : (value)))
#define PREFETCH(ptr) __builtin_prefetch(ptr, 0 , 3) 

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    
    int y, x, dy, dx;
    int by_width = 0;
    int dy_width = 0;
    
    float pre_filter[9];
    for(int i = 0; i < 9; i++){
        *(pre_filter + i) = *(filter + i);
    }
    
    
    
    // Handle boundary pixels
    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){
            if(x < 1 || x > width - 2 || y < 1 || y > height - 2){
                float r = 0, g = 0, b = 0;
                float *filter_ptr = pre_filter;
                Pixel *input_ptr = (input + by_width + x);
                dy_width = -width;
                for(dy = -1; dy <= 1; dy++){
                    int ny = y + dy;
                    for(dx = -1; dx <= 1; dx++){
                        int nx = x + dx;
                        if(nx >= 0 && nx < width && ny >= 0 && ny < height){
                            r += (input_ptr + dx + dy_width)->r * *(filter_ptr);
                            g += (input_ptr + dx + dy_width)->g * *(filter_ptr);
                            b += (input_ptr + dx + dy_width)->b * *(filter_ptr);
                        }
                        filter_ptr++;
                    }
                    dy_width += width;
                }                
                (output + x + by_width)->r = (unsigned char)CLAMP(r);
                (output + x + by_width)->g = (unsigned char)CLAMP(g);
                (output + x + by_width)->b = (unsigned char)CLAMP(b);
            }
        }
        by_width += width;
    }
    
    int y_width = width;
    
    // Handle inner pixels
    for(y = 1; y < height - 1; y++){
        for(x = 1; x < width - 1; x += 2){
            float r1 = 0, g1 = 0, b1 = 0;
            float r2 = 0, g2 = 0, b2 = 0;
            float *filter_ptr = pre_filter;
            Pixel *input_ptr = (input + y_width + x);
            dy_width = -width;
            
            PREFETCH(input_ptr + 1 + dy_width + 16);

            
            for(dy = -1; dy <= 1; dy++){
                for(dx = -1; dx <= 1; dx++){
                    r1 += (input_ptr + dx + dy_width)->r * *(filter_ptr);
                    g1 += (input_ptr + dx + dy_width)->g * *(filter_ptr);
                    b1 += (input_ptr + dx + dy_width)->b * *(filter_ptr);
                    
                    r2 += (input_ptr + 1 + dx + dy_width)->r * *(filter_ptr);
                    g2 += (input_ptr + 1 + dx + dy_width)->g * *(filter_ptr);
                    b2 += (input_ptr + 1+ dx + dy_width)->b * *(filter_ptr);

                    filter_ptr++;
                }
                dy_width += width;
            }
            Pixel p1, p2;
            p1.r = (unsigned char)CLAMP(r1);
            p1.g = (unsigned char)CLAMP(g1);
            p1.b = (unsigned char)CLAMP(b1);
            
            p2.r = (unsigned char)CLAMP(r2);
            p2.g = (unsigned char)CLAMP(g2);
            p2.b = (unsigned char)CLAMP(b2);
            
            *(output + x + y_width) = p1;
            *(output + x + y_width + 1) = p2;
            
        }
        y_width += width;
    }
}
