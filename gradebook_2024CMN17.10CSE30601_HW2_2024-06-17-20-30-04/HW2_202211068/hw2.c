#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

void filter_optimized(void* args[]) {
    register unsigned int width = *(unsigned int*)args[0];
    register unsigned int height = *(unsigned int*)args[1];
    register Pixel* input = (Pixel*)args[2];
    register Pixel* output = (Pixel*)args[3];
    register float* filter = (float*)args[4];

    register int ywidth = 0;
    register float r = 0, g = 0, b = 0;
    register int index, xdx, ydy, ydywidth;
    register Pixel p, in;

    for (register int y = 0; y < height; ++y) {
        for (register int x = 0; x < width; x += 4) { // Loop unrolling
            index = x + ywidth;

            //output[index] = convolution(input, x, y, width, height, filter);
            r = 0, g = 0, b = 0;
            // dy = -1
            ydy = y - 1;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x - 1;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[0];
                    g += in.g * filter[0];
                    b += in.b * filter[0];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[1];
                    g += in.g * filter[1];
                    b += in.b * filter[1];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[2];
                    g += in.g * filter[2];
                    b += in.b * filter[2];
                }
            }

            // dy = 0
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x - 1;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[3];
                    g += in.g * filter[3];
                    b += in.b * filter[3];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[4];
                    g += in.g * filter[4];
                    b += in.b * filter[4];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[5];
                    g += in.g * filter[5];
                    b += in.b * filter[5];
                }
            }

            // dy = 1
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x - 1;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[6];
                    g += in.g * filter[6];
                    b += in.b * filter[6];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[7];
                    g += in.g * filter[7];
                    b += in.b * filter[7];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[8];
                    g += in.g * filter[8];
                    b += in.b * filter[8];
                }
            }

            // Clamping the results
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);

            p.r = (unsigned char)r;
            p.g = (unsigned char)g;
            p.b = (unsigned char)b;
            output[index] = p;
            
            
            //output[index + 1] = convolution(input, x + 1, y, width, height, filter);
            r = 0, g = 0, b = 0;
            xdx = 0;
            // dy = -1
            ydy = y - 1;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[0];
                    g += in.g * filter[0];
                    b += in.b * filter[0];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[1];
                    g += in.g * filter[1];
                    b += in.b * filter[1];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[2];
                    g += in.g * filter[2];
                    b += in.b * filter[2];
                }
            }

            // dy = 0
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[3];
                    g += in.g * filter[3];
                    b += in.b * filter[3];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[4];
                    g += in.g * filter[4];
                    b += in.b * filter[4];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[5];
                    g += in.g * filter[5];
                    b += in.b * filter[5];
                }
            }

            // dy = 1
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[6];
                    g += in.g * filter[6];
                    b += in.b * filter[6];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[7];
                    g += in.g * filter[7];
                    b += in.b * filter[7];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[8];
                    g += in.g * filter[8];
                    b += in.b * filter[8];
                }
            }

            // Clamping the results
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);

            p.r = (unsigned char)r;
            p.g = (unsigned char)g;
            p.b = (unsigned char)b;
            output[index+1] = p;

            
            //output[index + 2] = convolution(input, x + 2, y, width, height, filter);
            r = 0, g = 0, b = 0;
            xdx = 0;
            // dy = -1
            ydy = y - 1;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x+1;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[0];
                    g += in.g * filter[0];
                    b += in.b * filter[0];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[1];
                    g += in.g * filter[1];
                    b += in.b * filter[1];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[2];
                    g += in.g * filter[2];
                    b += in.b * filter[2];
                }
            }

            // dy = 0
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x+1;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[3];
                    g += in.g * filter[3];
                    b += in.b * filter[3];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[4];
                    g += in.g * filter[4];
                    b += in.b * filter[4];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[5];
                    g += in.g * filter[5];
                    b += in.b * filter[5];
                }
            }

            // dy = 1
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x+1;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[6];
                    g += in.g * filter[6];
                    b += in.b * filter[6];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[7];
                    g += in.g * filter[7];
                    b += in.b * filter[7];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[8];
                    g += in.g * filter[8];
                    b += in.b * filter[8];
                }
            }

            // Clamping the results
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);

            p.r = (unsigned char)r;
            p.g = (unsigned char)g;
            p.b = (unsigned char)b;
            output[index+2] = p;

            
            //output[index + 3] = convolution(input, x + 3, y, width, height, filter);
            r = 0, g = 0, b = 0;
            xdx = 0;
            // dy = -1
            ydy = y - 1;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x + 2;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[0];
                    g += in.g * filter[0];
                    b += in.b * filter[0];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[1];
                    g += in.g * filter[1];
                    b += in.b * filter[1];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[2];
                    g += in.g * filter[2];
                    b += in.b * filter[2];
                }
            }

            // dy = 0
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x + 2;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[3];
                    g += in.g * filter[3];
                    b += in.b * filter[3];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[4];
                    g += in.g * filter[4];
                    b += in.b * filter[4];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[5];
                    g += in.g * filter[5];
                    b += in.b * filter[5];
                }
            }

            // dy = 1
            ydy++;
            ydywidth = ydy * width;
            if (ydy >= 0 && ydy < height) {
                // dx = -1
                xdx = x+2;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[6];
                    g += in.g * filter[6];
                    b += in.b * filter[6];
                }
                // dx = 0
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[7];
                    g += in.g * filter[7];
                    b += in.b * filter[7];
                }
                // dx = 1
                xdx++;
                if (xdx >= 0 && xdx < width) {
                    in = input[xdx + ydywidth];
                    r += in.r * filter[8];
                    g += in.g * filter[8];
                    b += in.b * filter[8];
                }
            }

            // Clamping the results
            r = r < 0 ? 0 : (r > 255 ? 255 : r);
            g = g < 0 ? 0 : (g > 255 ? 255 : g);
            b = b < 0 ? 0 : (b > 255 ? 255 : b);

            p.r = (unsigned char)r;
            p.g = (unsigned char)g;
            p.b = (unsigned char)b;
            output[index+3] = p;
            
        }
        ywidth += width;
    }
}
