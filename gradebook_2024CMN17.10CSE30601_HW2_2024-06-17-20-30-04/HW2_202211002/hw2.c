// Assignment 2 - Efficient C Programming
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmplib.h"
#include "hw2.h"

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!


inline static void convolution(
        Pixel* input, Pixel* output,int x, int y, int width, int height, float* filter) {
    int r_1 = 0;
    int g_1 = 0;
    int b_1 = 0;
    int r_2 = 0;
    int g_2 = 0;
    int b_2 = 0;
    int r_3 = 0;
    int g_3 = 0;
    int b_3 = 0;
    int r2_1 = 0;
    int g2_1 = 0;
    int b2_1 = 0;
    int r2_2 = 0;
    int g2_2 = 0;
    int b2_2 = 0;
    int r2_3 = 0;
    int g2_3 = 0;
    int b2_3 = 0;
    int r3_1 = 0;
    int g3_1 = 0;
    int b3_1 = 0;
    int r3_2 = 0;
    int g3_2 = 0;
    int b3_2 = 0;
    int r3_3 = 0;
    int g3_3 = 0;
    int b3_3 = 0;
    int r4_1 = 0;
    int g4_1 = 0;
    int b4_1 = 0;
    int r4_2 = 0;
    int g4_2 = 0;
    int b4_2 = 0;
    int r4_3 = 0;
    int g4_3 = 0;
    int b4_3 = 0;
    int r5_1 = 0;
    int g5_1 = 0;
    int b5_1 = 0;
    int r5_2 = 0;
    int g5_2 = 0;
    int b5_2 = 0;
    int r5_3 = 0;
    int g5_3 = 0;
    int b5_3 = 0;
    int r6_1 = 0;
    int g6_1 = 0;
    int b6_1 = 0;
    int r6_2 = 0;
    int g6_2 = 0;
    int b6_2 = 0;
    int r6_3 = 0;
    int g6_3 = 0;
    int b6_3 = 0;
    int r7_1 = 0;
    int g7_1 = 0;
    int b7_1 = 0;
    int r7_2 = 0;
    int g7_2 = 0;
    int b7_2 = 0;
    int r7_3 = 0;
    int g7_3 = 0;
    int b7_3 = 0;
    int r8_1 = 0;
    int g8_1 = 0;
    int b8_1 = 0;
    int r8_2 = 0;
    int g8_2 = 0;
    int b8_2 = 0;
    int r8_3 = 0;
    int g8_3 = 0;
    int b8_3 = 0;
    int r9_1 = 0;
    int g9_1 = 0;
    int b9_1 = 0;
    int r9_2 = 0;
    int g9_2 = 0;
    int b9_2 = 0;
    int r9_3 = 0;
    int g9_3 = 0;
    int b9_3 = 0;
    int r10_1 = 0;
    int g10_1 = 0;
    int b10_1 = 0;
    int r10_2 = 0;
    int g10_2 = 0;
    int b10_2 = 0;
    int r10_3 = 0;
    int g10_3 = 0;
    int b10_3 = 0;
    int r11_1 = 0;
    int g11_1 = 0;
    int b11_1 = 0;
    int r11_2 = 0;
    int g11_2 = 0;
    int b11_2 = 0;
    int r11_3 = 0;
    int g11_3 = 0;
    int b11_3 = 0;
    int r12_1 = 0;
    int g12_1 = 0;
    int b12_1 = 0;
    int r12_2 = 0;
    int g12_2 = 0;
    int b12_2 = 0;
    int r12_3 = 0;
    int g12_3 = 0;
    int b12_3 = 0;
    int r13_1 = 0;
    int g13_1 = 0;
    int b13_1 = 0;
    int r13_2 = 0;
    int g13_2 = 0;
    int b13_2 = 0;
    int r13_3 = 0;
    int g13_3 = 0;
    int b13_3 = 0;
    int r14_1 = 0;
    int g14_1 = 0;
    int b14_1 = 0;
    int r14_2 = 0;
    int g14_2 = 0;
    int b14_2 = 0;
    int r14_3 = 0;
    int g14_3 = 0;
    int b14_3 = 0;
    int r15_1 = 0;
    int g15_1 = 0;
    int b15_1 = 0;
    int r15_2 = 0;
    int g15_2 = 0;
    int b15_2 = 0;
    int r15_3 = 0;
    int g15_3 = 0;
    int b15_3 = 0;
    int r16_1 = 0;
    int g16_1 = 0;
    int b16_1 = 0;
    int r16_2 = 0;
    int g16_2 = 0;
    int b16_2 = 0;
    int r16_3 = 0;
    int g16_3 = 0;
    int b16_3 = 0;
    int f0 = filter[0];
    int f1 = filter[1];
    int f2 = filter[2];
    int f3 = filter[3];
    int f4 = filter[4];
    int f5 = filter[5];
    int f6 = filter[6];
    int f7 = filter[7];
    int f8 = filter[8];
    int f10 = f0;
    int f11 = f1;
    int f12 = f2;
    int f13 = f3;
    int f14 = f4;
    int f15 = f5;
    int f16 = f6;
    int f17 = f7;
    int f18 = f8;

    // y - 1, x - 1
    if ((y - 1) >= 0 && (y - 1) < height && (x - 1) >= 0 && (x - 1) < width) {
        Pixel a0 = input[(x - 1) + width * (y - 1)];
        r_1 += a0.r * f10;
        g_1 += a0.g * f0;
        b_1 += a0.b * f10;
    }
        // y, x - 1
    if (y >= 0 && y < height && (x - 1) >= 0 && (x - 1) < width) {
        Pixel a3 = input[(x - 1) + width * y];
        r_2 += a3.r * f13;
        g_2 += a3.g * f3;
        b_2 += a3.b * f13;
        r9_1 += a3.r * f10;
        g9_1 += a3.g * f0;
        b9_1 += a3.b * f10;

    }

    // y + 1, x - 1
    if ((y + 1) >= 0 && (y + 1) < height && (x - 1) >= 0 && (x - 1) < width) {
        Pixel a6 = input[(x - 1) + width * (y + 1)];
        r_3 += a6.r * f6;
        g_3 += a6.g * f16;
        b_3 += a6.b * f6;
        r9_2 += a6.r * f3;
        g9_2 += a6.g * f13;
        b9_2 += a6.b * f3;

    }
        // y + 2, x - 1
    if ((y + 2) >= 0 && (y + 2) < height && (x - 1) >= 0 && (x - 1) < width) {
        Pixel aa = input[(x - 1) + width * (y + 2)];
        r9_3 += aa.r * f16;
        g9_3 += aa.g * f6;
        b9_3 += aa.b * f16;
    }

    // y - 1, x
    if ((y - 1) >= 0 && (y - 1) < height && x >= 0 && x < width) {
        Pixel a1 = input[x + width * (y - 1)];
        r_1 += a1.r * f11;
        g_1 += a1.g * f1;
        b_1 += a1.b * f11;
        r2_1 += a1.r * f0;
        g2_1 += a1.g * f10;
        b2_1 += a1.b * f0;
    }
    // y, x
    if (y >= 0 && y < height && x >= 0 && x < width) {
        Pixel a4 = input[x + width * y];
        r_2 += a4.r * f14;
        g_2 += a4.g * f4;
        b_2 += a4.b * f14;
        r2_2 += a4.r * f13;
        g2_2 += a4.g * f3;
        b2_2 += a4.b * f13;
        r9_1 += a4.r * f1;
        g9_1 += a4.g * f11;
        b9_1 += a4.b * f1;
        r10_1 += a4.r * f0;
        g10_1 += a4.g * f10;
        b10_1 += a4.b * f0;

    }
        // y + 1, x
    if ((y + 1) >= 0 && (y + 1) < height && x >= 0 && x < width) {
        Pixel a7 = input[x + width * (y + 1)];
        r_3 += a7.r * f7;
        g_3 += a7.g * f17;
        b_3 += a7.b * f7;
        r2_3 += a7.r * f6;
        g2_3 += a7.g * f16;
        b2_3 += a7.b * f6;
        r9_3 += a7.r * f4;
        g9_3 += a7.g * f14;
        b9_3 += a7.b * f4;
        r10_3 += a7.r * f3;
        g10_3 += a7.g * f13;
        b10_3 += a7.b * f3;
    }
        // y + 2, x
    if ((y + 2) >= 0 && (y + 2) < height && x >= 0 && x < width) {
        Pixel aa = input[x + width * (y + 2)];
        r9_1 +=  aa.r * f7;
        g9_1 +=  aa.g * f17;
        b9_1 +=  aa.b * f7;
        r10_1 += aa.r * f6;
        g10_1 += aa.g * f16;
        b10_1 += aa.b * f6;
    }



    // y - 1, x + 1
    if ((y - 1) >= 0 && (y - 1) < height && (x + 1) >= 0 && (x + 1) < width) {
        Pixel a2 = input[(x + 1) + width * (y - 1)];
        r_3 += a2.r * f2;
        g_3 += a2.g * f12;
        b_3 += a2.b * f2;
        r2_2 += a2.r * f1;
        g2_2 += a2.g * f11;
        b2_2 += a2.b * f1;
        r3_1 += a2.r * f0;
        g3_1 += a2.g * f10;
        b3_1 += a2.b * f0;
    }



    // y, x + 1
    if (y >= 0 && y < height && (x + 1) >= 0 && (x + 1) < width) {
        Pixel a5 = input[(x + 1) + width * y];
        r_3 += a5.r * f5;
        g_3 += a5.g * f15;
        b_3 += a5.b * f5;
        r2_1 += a5.r * f14;
        g2_1 += a5.g * f4;
        b2_1 += a5.b * f14;
        r3_2 += a5.r * f3;
        g3_2 += a5.g * f13;
        b3_2 += a5.b * f3;
        r9_3 +=  a5.r * f12;
        g9_3 +=  a5.g * f2;
        b9_3 +=  a5.b * f12;
        r10_2 += a5.r * f1;
        g10_2 += a5.g * f11;
        b10_2 += a5.b * f1;
        r11_1 += a5.r * f0;
        g11_1 += a5.g * f10;
        b11_1 += a5.b * f0;

    }


    // y + 1, x + 1
    if ((y + 1) >= 0 && (y + 1) < height && (x + 1) >= 0 && (x + 1) < width) {
        Pixel a8 = input[(x + 1) + width * (y + 1)];
        r_3 += a8.r * f8;
        g_3 += a8.g * f18;
        b_3 += a8.b * f8;
        r2_3 += a8.r * f7;
        g2_3 += a8.g * f17;
        b2_3 += a8.b * f7;
        r3_3 += a8.r * f6;
        g3_3 += a8.g * f16;
        b3_3 += a8.b * f6;
        r9_3 += a8.r * f5;
        g9_3 += a8.g * f15;
        b9_3 += a8.b * f5;
        r10_3 += a8.r * f4;
        g10_3 += a8.g * f14;
        b10_3 += a8.b * f4;
        r11_3 += a8.r * f3;
        g11_3 += a8.g * f13;
        b11_3 += a8.b * f3;

    }
    // y + 2, x + 1
    if ((y + 2) >= 0 && (y + 2) < height && (x + 1) >= 0 && (x + 1) < width) {
        Pixel a8 = input[(x + 1) + width * (y + 2)];
        r9_1 += a8.r * f8;
        g9_1 += a8.g * f18;
        b9_1 += a8.b * f8;
        r10_1 += a8.r * f7;
        g10_1 += a8.g * f17;
        b10_1 += a8.b * f7;
        r11_1 += a8.r * f16;
        g11_1 += a8.g * f6;
        b11_1 += a8.b * f16;

    }

    // second convolution

    // y - 1, x + 2
    if ((y - 1) >= 0 && (y - 1) < height && (x + 2) >= 0 && (x + 2) < width) {
        Pixel a9 = input[(x + 2) + width * (y - 1)];
        r2_1 += a9.r * f2;
        g2_1 += a9.g * f12;
        b2_1 += a9.b * f2;
        r3_1 += a9.r * f11;
        g3_1 += a9.g * f1;
        b3_1 += a9.b * f11;
        r4_1 += a9.r * f0;
        g4_1 += a9.g * f10;
        b4_1 += a9.b * f0;

    }

    // y, x + 2
    if ((y) >= 0 && (y) < height && (x + 2) >= 0 && (x +2) < width) {
        Pixel a10 = input[(x + 2) + width * (y)];
        r2_2 += a10.r * f15;
        g2_2 += a10.g * f5;
        b2_2 += a10.b * f15;
        r3_2 += a10.r * f4;
        g3_2 += a10.g * f14;
        b3_2 += a10.b * f4;
        r4_2 += a10.r * f13;
        g4_2 += a10.g * f3;
        b4_2 += a10.b * f13;
        r10_2 += a10.r * f2;
        g10_2 += a10.g * f12;
        b10_2 += a10.b * f2;
        r11_2 += a10.r * f1;
        g11_2 += a10.g * f11;
        b11_2 += a10.b * f1;
        r12_2 += a10.r * f0;
        g12_2 += a10.g * f10;
        b12_2 += a10.b * f0;

    }
    // y + 1, x + 2
    if ((y + 1) >= 0 && (y + 1) < height && (x + 2) >= 0 && (x + 2) < width) {
        Pixel a11 = input[(x + 2) + width * (y + 1)];
        r2_3 += a11.r * f8;
        g2_3 += a11.g * f18;
        b2_3 += a11.b * f8;
        r3_3 += a11.r * f7;
        g3_3 += a11.g * f17;
        b3_3 += a11.b * f7;
        r4_3 += a11.r * f6;
        g4_3 += a11.g * f16;
        b4_3 += a11.b * f6;
        r10_3 += a11.r * f5;
        g10_3 += a11.g * f15;
        b10_3 += a11.b * f5;
        r11_3 += a11.r * f4;
        g11_3 += a11.g * f14;
        b11_3 += a11.b * f4;
        r12_3 += a11.r * f3;
        g12_3 += a11.g * f13;
        b12_3 += a11.b * f3;
    }
    // y + 2, x + 2
    if ((y + 2) >= 0 && (y + 2) < height && (x + 2) >= 0 && (x + 2) < width) {
        Pixel a11 = input[(x + 2) + width * (y + 2)];
        r10_1 += a11.r * f18;
        g10_1 += a11.g * f8;
        b10_1 += a11.b * f18;
        r11_1 += a11.r * f7;
        g11_1 += a11.g * f17;
        b11_1 += a11.b * f7;
        r12_1 += a11.r * f6;
        g12_1 += a11.g * f16;
        b12_1 += a11.b * f6;
    }

    // y - 1, x + 3
    if ((y - 1) >= 0 && (y - 1) < height && (x + 3) >= 0 && (x + 3) < width) {
        Pixel a12 = input[(x + 3) + width * (y - 1)];
        r3_1 += a12.r * f12;
        g3_1 += a12.g * f2;
        b3_1 += a12.b * f12;
        r4_1 += a12.r * f1;
        g4_1 += a12.g * f11;
        b4_1 += a12.b * f1;
        r5_1 += a12.r * f0;
        g5_1 += a12.g * f10;
        b5_1 += a12.b * f0;

    }

    // y, x + 3
    if ((y) >= 0 && (y) < height && (x + 3) >= 0 && (x +3) < width) {
        Pixel a13 = input[(x + 3) + width * (y)];
        r3_2 += a13.r * f15;
        g3_2 += a13.g * f5;
        b3_2 += a13.b * f15;
        r4_2 += a13.r * f4;
        g4_2 += a13.g * f14;
        b4_2 += a13.b * f4;
        r5_2 += a13.r * f13;
        g5_2 += a13.g * f3;
        b5_2 += a13.b * f13;
        r11_2 += a13.r * f2;
        g11_2 += a13.g * f12;
        b11_2 += a13.b * f2;
        r12_2 += a13.r * f1;
        g12_2 += a13.g * f11;
        b12_2 += a13.b * f1;
        r13_2 += a13.r * f0;
        g13_2 += a13.g * f10;
        b13_2 += a13.b * f0;

    }
    // y + 1, x + 3
    if ((y + 1) >= 0 && (y + 1) < height && (x + 3) >= 0 && (x + 3) < width) {
        Pixel a14 = input[(x + 3) + width * (y + 1)];
        r3_3 += a14.r * f8;
        g3_3 += a14.g * f18;
        b3_3 += a14.b * f8;
        r4_3 += a14.r * f7;
        g4_3 += a14.g * f17;
        b4_3 += a14.b * f7;
        r5_3 += a14.r * f6;
        g5_3 += a14.g * f16;
        b5_3 += a14.b * f6;
        r11_3 += a14.r * f5;
        g11_3 += a14.g * f15;
        b11_3 += a14.b * f5;
        r12_3 += a14.r * f4;
        g12_3 += a14.g * f14;
        b12_3 += a14.b * f4;
        r13_3 += a14.r * f3;
        g13_3 += a14.g * f13;
        b13_3 += a14.b * f3;

    }
      // y + 2, x + 3
    if ((y + 2) >= 0 && (y + 2) < height && (x + 3) >= 0 && (x + 3) < width) {
        Pixel a14 = input[(x + 3) + width * (y + 2)];
        r11_1 += a14.r * f8;
        g11_1 += a14.g * f18;
        b11_1 += a14.b * f8;
        r12_1 += a14.r * f7;
        g12_1 += a14.g * f17;
        b12_1 += a14.b * f7;
        r13_1 += a14.r * f6;
        g13_1 += a14.g * f16;
        b13_1 += a14.b * f6;
    }

 // y - 1, x + 4
    if ((y - 1) >= 0 && (y - 1) < height && (x + 4) >= 0 && (x + 4) < width) {
        Pixel a15 = input[(x + 4) + width * (y - 1)];
        r4_1 += a15.r * f2;
        g4_1 += a15.g * f12;
        b4_1 += a15.b * f2;
        r5_1 += a15.r * f1;
        g5_1 += a15.g * f11;
        b5_1 += a15.b * f1;
        r6_1 += a15.r * f0;
        g6_1 += a15.g * f10;
        b6_1 += a15.b * f0;
    }

    // y, x + 4
    if ((y) >= 0 && (y) < height && (x + 4) >= 0 && (x +4) < width) {
        Pixel a16 = input[(x + 4) + width * (y)];
        r4_2 += a16.r * f5;
        g4_2 += a16.g * f15;
        b4_2 += a16.b * f5;
        r5_2 += a16.r * f4;
        g5_2 += a16.g * f14;
        b5_2 += a16.b * f4;
        r6_2 += a16.r * f3;
        g6_2 += a16.g * f13;
        b6_2 += a16.b * f3;
        r12_1 += a16.r * f2;
        g12_1 += a16.g * f12;
        b12_1 += a16.b * f2;
        r13_1 += a16.r * f1;
        g13_1 += a16.g * f11;
        b13_1 += a16.b * f1;
        r14_1 += a16.r * f0;
        g14_1 += a16.g * f10;
        b14_1 += a16.b * f0;

    }
    // y + 1, x + 4
    if ((y + 1) >= 0 && (y + 1) < height && (x + 4) >= 0 && (x + 4) < width) {
        Pixel a17 = input[(x + 4) + width * (y + 1)];
        r4_3 += a17.r * f8;
        g4_3 += a17.g * f18;
        b4_3 += a17.b * f8;
        r5_3 += a17.r * f7;
        g5_3 += a17.g * f17;
        b5_3 += a17.b * f7;
        r6_3 += a17.r * f6;
        g6_3 += a17.g * f16;
        b6_3 += a17.b * f6;
        r12_3 += a17.r * f15;
        g12_3 += a17.g * f5;
        b12_3 += a17.b * f15;
        r13_3 += a17.r * f4;
        g13_3 += a17.g * f14;
        b13_3 += a17.b * f4;
        r14_3 += a17.r * f3;
        g14_3 += a17.g * f13;
        b14_3 += a17.b * f3;

    }
        // y + 2, x + 4
    if ((y + 2) >= 0 && (y + 2) < height && (x + 4) >= 0 && (x + 4) < width) {
        Pixel a17 = input[(x + 4) + width * (y + 2)];
        r12_1 += a17.r * f8;
        g12_1 += a17.g * f18;
        b12_1 += a17.b * f8;
        r13_1 += a17.r * f7;
        g13_1 += a17.g * f17;
        b13_1 += a17.b * f7;
        r14_1 += a17.r * f6;
        g14_1 += a17.g * f16;
        b14_1 += a17.b * f6;
    }

 // y - 1, x + 5
    if ((y - 1) >= 0 && (y - 1) < height && (x + 5) >= 0 && (x + 5) < width) {
        Pixel a18 = input[(x + 5) + width * (y - 1)];
        r5_1 += a18.r * f2;
        g5_1 += a18.g * f12;
        b5_1 += a18.b * f2;
        r6_1 += a18.r * f1;
        g6_1 += a18.g * f11;
        b6_1 += a18.b * f1;
        r7_1 += a18.r * f0;
        g7_1 += a18.g * f10;
        b7_1 += a18.b * f0;
    }

    // y, x + 5
    if ((y) >= 0 && (y) < height && (x + 5) >= 0 && (x +5) < width) {
        Pixel a19 = input[(x + 5) + width * (y)];
        r5_2 += a19.r * f15;
        g5_2 += a19.g * f5;
        b5_2 += a19.b * f15;
        r6_2 += a19.r * f4;
        g6_2 += a19.g * f14;
        b6_2 += a19.b * f4;
        r7_2 += a19.r * f3;
        g7_2 += a19.g * f13;
        b7_2 += a19.b * f3;
        r13_2 += a19.r * f2;
        g13_2 += a19.g * f12;
        b13_2 += a19.b * f2;
        r14_2 += a19.r * f1;
        g14_2 += a19.g * f11;
        b14_2 += a19.b * f1;
        r15_2 += a19.r * f0;
        g15_2 += a19.g * f10;
        b15_2 += a19.b * f0;

    }
    // y + 1, x + 5
    if ((y + 1) >= 0 && (y + 1) < height && (x + 5) >= 0 && (x + 5) < width) {
        Pixel a20 = input[(x + 5) + width * (y + 1)];
        r5_3 += a20.r * f18;
        g5_3 += a20.g * f8;
        b5_3 += a20.b * f18;
        r6_3 += a20.r * f7;
        g6_3 += a20.g * f17;
        b6_3 += a20.b * f7;
        r7_3 += a20.r * f6;
        g7_3 += a20.g * f16;
        b7_3 += a20.b * f6;
        r13_3 += a20.r * f5;
        g13_3 += a20.g * f15;
        b13_3 += a20.b * f5;
        r14_3 += a20.r * f4;
        g14_3 += a20.g * f14;
        b14_3 += a20.b * f4;
        r15_3 += a20.r * f3;
        g15_3 += a20.g * f13;
        b15_3 += a20.b * f3;

    }
        // y + 2, x + 5
    if ((y + 2) >= 0 && (y + 2) < height && (x + 5) >= 0 && (x + 5) < width) {
        Pixel a20 = input[(x + 5) + width * (y + 2)];
        r13_1 += a20.r * f8;
        g13_1 += a20.g * f18;
        b13_1 += a20.b * f8;
        r14_1 += a20.r * f7;
        g14_1 += a20.g * f17;
        b14_1 += a20.b * f7;
        r15_1 += a20.r * f6;
        g15_1 += a20.g * f16;
        b15_1 += a20.b * f6;
    }

 // y - 1, x + 6
    if ((y - 1) >= 0 && (y - 1) < height && (x + 6) >= 0 && (x + 6) < width) {
        Pixel a21 = input[(x + 6) + width * (y - 1)];
        r6_1 += a21.r * f2;
        g6_1 += a21.g * f12;
        b6_1 += a21.b * f2;
        r7_1 += a21.r * f1;
        g7_1 += a21.g * f11;
        b7_1 += a21.b * f1;
        r8_1 += a21.r * f0;
        g8_1 += a21.g * f10;
        b8_1 += a21.b * f0;
    }

    // y, x + 6
    if ((y) >= 0 && (y) < height && (x + 6) >= 0 && (x +6) < width) {
        Pixel a22 = input[(x + 6) + width * (y)];
        r6_2 += a22.r * f5;
        g6_2 += a22.g * f15;
        b6_2 += a22.b * f5;
        r7_2 += a22.r * f4;
        g7_2 += a22.g * f14;
        b7_2 += a22.b * f4;
        r8_2 += a22.r * f3;
        g8_2 += a22.g * f13;
        b8_2 += a22.b * f3;
        r14_2 += a22.r * f2;
        g14_2 += a22.g * f12;
        b14_2 += a22.b * f2;
        r15_2 += a22.r * f1;
        g15_2 += a22.g * f11;
        b15_2 += a22.b * f1;
        r16_2 += a22.r * f0;
        g16_2 += a22.g * f10;
        b16_2 += a22.b * f0;

    }
    // y + 1, x + 6
    if ((y + 1) >= 0 && (y + 1) < height && (x + 6) >= 0 && (x + 6) < width) {
        Pixel a23 = input[(x + 6) + width * (y + 1)];
        r6_3 += a23.r * f8;
        g6_3 += a23.g * f18;
        b6_3 += a23.b * f8;
        r7_3 += a23.r * f7;
        g7_3 += a23.g * f17;
        b7_3 += a23.b * f7;
        r8_3 += a23.r * f6;
        g8_3 += a23.g * f16;
        b8_3 += a23.b * f6;
        r14_3 += a23.r * f5;
        g14_3 += a23.g * f15;
        b14_3 += a23.b * f5;
        r15_3 += a23.r * f4;
        g15_3 += a23.g * f14;
        b15_3 += a23.b * f4;
        r16_3 += a23.r * f3;
        g16_3 += a23.g * f13;
        b16_3 += a23.b * f3;

    }
      // y + 2, x + 6
    if ((y + 2) >= 0 && (y + 2) < height && (x + 6) >= 0 && (x + 6) < width) {
        Pixel a23 = input[(x + 6) + width * (y + 2)];
        r14_3 += a23.r * f8;
        g14_3 += a23.g * f18;
        b14_3 += a23.b * f8;
        r15_3 += a23.r * f7;
        g15_3 += a23.g * f17;
        b15_3 += a23.b * f7;
        r16_3 += a23.r * f6;
        g16_3 += a23.g * f16;
        b16_3 += a23.b * f6;
    }
 // y - 1, x + 7
    if ((y - 1) >= 0 && (y - 1) < height && (x + 7) >= 0 && (x + 7) < width) {
        Pixel a24 = input[(x + 7) + width * (y - 1)];
        r7_1 += a24.r * f2;
        g7_1 += a24.g * f12;
        b7_1 += a24.b * f2;
        r8_1 += a24.r * f1;
        g8_1 += a24.g * f11;
        b8_1 += a24.b * f1;
    }

    // y, x + 7
    if ((y) >= 0 && (y) < height && (x + 7) >= 0 && (x +7) < width) {
        Pixel a25 = input[(x + 7) + width * (y)];
        r7_2 += a25.r * f5;
        g7_2 += a25.g * f15;
        b7_2 += a25.b * f5;
        r8_2 += a25.r * f4;
        g8_2 += a25.g * f14;
        b8_2 += a25.b * f4;
        r15_2 += a25.r * f2;
        g15_2 += a25.g * f12;
        b15_2 += a25.b * f2;
        r16_2 += a25.r * f1;
        g16_2 += a25.g * f11;
        b16_2 += a25.b * f1;

    }
    // y + 1, x + 7
    if ((y + 1) >= 0 && (y + 1) < height && (x + 7) >= 0 && (x + 7) < width) {
        Pixel a26 = input[(x + 7) + width * (y + 1)];
        r7_3 += a26.r * f18;
        g7_3 += a26.g * f8;
        b7_3 += a26.b * f18;
        r8_3 += a26.r * f7;
        g8_3 += a26.g * f17;
        b8_3 += a26.b * f7;
        r15_3 += a26.r * f5;
        g15_3 += a26.g * f15;
        b15_3 += a26.b * f5;
        r16_3 += a26.r * f4;
        g16_3 += a26.g * f14;
        b16_3 += a26.b * f4;

    }
        // y + 2, x + 7
    if ((y + 2) >= 0 && (y + 2) < height && (x + 7) >= 0 && (x + 7) < width) {
        Pixel a26 = input[(x + 7) + width * (y + 2)];
        r15_1 += a26.r * f8;
        g15_1 += a26.g * f18;
        b15_1 += a26.b * f8;
        r16_1 += a26.r * f7;
        g16_1 += a26.g * f17;
        b16_1 += a26.b * f7;

    }
 // y - 1, x + 8
    if ((y - 1) >= 0 && (y - 1) < height && (x + 8) >= 0 && (x + 8) < width) {
        Pixel a27 = input[(x + 8) + width * (y - 1)];
        r8_1 += a27.r * f2;
        g8_1 += a27.g * f12;
        b8_1 += a27.b * f2;
    }

    // y, x + 8
    if ((y) >= 0 && (y) < height && (x + 8) >= 0 && (x +8) < width) {
        Pixel a28 = input[(x + 8) + width * (y)];
        r8_2 += a28.r * f5;
        g8_2 += a28.g * f15;
        b8_2 += a28.b * f5;
        r16_2 += a28.r * f2;
        g16_2 += a28.g * f12;
        b16_2 += a28.b * f2;


    }
    // y + 1, x + 8
    if ((y + 1) >= 0 && (y + 1) < height && (x + 8) >= 0 && (x + 8) < width) {
        Pixel a29 = input[(x + 8) + width * (y + 1)];
        r8_3 += a29.r * f8;
        g8_3 += a29.g * f18;
        b8_3 += a29.b * f8;
        r16_3 += a29.r * f5;
        g16_3 += a29.g * f15;
        b16_3 += a29.b * f5;
    }
        // y + 2, x + 8

    if ((y + 2) >= 0 && (y + 2) < height && (x + 8) >= 0 && (x + 8) < width) {
        Pixel a29 = input[(x + 8) + width * (y + 2)];
        r16_1 += a29.r * f18;
        g16_1 += a29.g * f8;
        b16_1 += a29.b * f18;
        }


    r_1+=r_2+r_3;
    g_1+=g_2+g_3;
    b_1+=b_2+b_3;
    r2_1+=r2_2+r2_3;
    g2_1+=g2_2+g2_3;
    b2_1+=b2_2+b2_3;
    r3_1+=r3_2+r3_3;
    g3_1+=g3_2+g3_3;
    b3_1+=b3_2+b3_3;
    r4_1+=r4_2+r4_3;
    g4_1+=g4_2+g4_3;
    b4_1+=b4_2+b4_3;
    r5_1+=r5_2+r5_3;
    g5_1+=g5_2+g5_3;
    b5_1+=b5_2+b5_3;
    r6_1+=r6_2+r6_3;
    g6_1+=g6_2+g6_3;
    b6_1+=b6_2+b6_3;
    r7_1+=r7_2+r7_3;
    g7_1+=g7_2+g7_3;
    b7_1+=b7_2+b7_3;
    r8_1+=r8_2+r8_3;
    g8_1+=g8_2+g8_3;
    b8_1+=b8_2+b8_3;
    r9_1+=r9_2+r9_3;
    g9_1+=g9_2+g9_3;
    b9_1+=b9_2+b9_3;
    r10_1+=r10_2+r10_3;
    g10_1+=g10_2+g10_3;
    b10_1+=b10_2+b10_3;

    r11_1+=r11_2+r11_3;
    g11_1+=g11_2+g11_3;
    b11_1+=b11_2+b11_3;
    r12_1+=r12_2+r12_3;
    g12_1+=g12_2+g12_3;
    b12_1+=b12_2+b12_3;
    r13_1+=r13_2+r13_3;
    g13_1+=g13_2+g13_3;
    b13_1+=b13_2+b13_3;
    r14_1+=r14_2+r14_3;
    g14_1+=g14_2+g14_3;
    b14_1+=b14_2+b14_3;
    r15_1+=r15_2+r15_3;
    g15_1+=g15_2+g15_3;
    b15_1+=b15_2+b15_3;
    r16_1+=r16_2+r16_3;
    g16_1+=g16_2+g16_3;
    b16_1+=b16_2+b16_3;

    if (r_1 < 0) r_1 = 0;
    else if (r_1 > 255) r_1 = 255;
    if (g_1 < 0) g_1 = 0;
    else if (g_1 > 255) g_1 = 255;
    if (b_1 < 0) b_1 = 0;
    else if (b_1 > 255) b_1 = 255;

    if (r2_1 < 0) r2_1 = 0;
    else if (r2_1 > 255) r2_1 = 255;
    if (g2_1 < 0) g2_1 = 0;
    else if (g2_1 > 255) g2_1 = 255;
    if (b2_1 < 0) b2_1 = 0;
    if (b2_1 > 255) b2_1 = 255;
    
    if (r3_1 < 0) r3_1 = 0;
    else if (r3_1 > 255) r3_1 = 255;
    if (g3_1 < 0) g3_1 = 0;
    else if (g3_1 > 255) g3_1 = 255;
    if (b3_1 < 0) b3_1 = 0;
    else if (b3_1 > 255) b3_1 = 255;

    if (r4_1 < 0) r4_1 = 0;
    else if (r4_1 > 255) r4_1 = 255;
    if (g4_1 < 0) g4_1 = 0;
    else if (g4_1 > 255) g4_1 = 255;
    if (b4_1 < 0) b4_1 = 0;
    else if (b4_1 > 255) b4_1 = 255;

    if (r5_1 < 0) r5_1 = 0;
    else if (r5_1 > 255) r5_1 = 255;
    if (g5_1 < 0) g5_1 = 0;
    else if (g5_1 > 255) g5_1 = 255;
    if (b5_1 < 0) b5_1 = 0;
    else if (b5_1 > 255) b5_1 = 255;

    if (r6_1 < 0) r6_1 = 0;
    else if (r6_1 > 255) r6_1 = 255;
    if (g6_1 < 0) g6_1 = 0;
    else if (g6_1 > 255) g6_1 = 255;
    if (b6_1 < 0) b6_1 = 0;
    if (b6_1 > 255) b6_1 = 255;
    
    if (r7_1 < 0) r7_1 = 0;
    else if (r7_1 > 255) r7_1 = 255;
    if (g7_1 < 0) g7_1 = 0;
    else if (g7_1 > 255) g7_1 = 255;
    if (b7_1 < 0) b7_1 = 0;
    else if (b7_1 > 255) b7_1 = 255;

    if (r8_1 < 0) r8_1 = 0;
    else if (r8_1 > 255) r8_1 = 255;
    if (g8_1 < 0) g8_1 = 0;
    else if (g8_1 > 255) g8_1 = 255;
    if (b8_1 < 0) b8_1 = 0;
    else if (b8_1 > 255) b8_1 = 255;
    if (r9_1 < 0) r9_1 = 0;
    else if (r9_1 > 255) r9_1 = 255;
    if (g9_1 < 0) g9_1 = 0;
    else if (g9_1 > 255) g9_1 = 255;
    if (b9_1 < 0) b9_1 = 0;
    else if (b9_1 > 255) b9_1 = 255;

    if (r10_1 < 0) r10_1 = 0;
    else if (r10_1 > 255) r10_1 = 255;
    if (g10_1 < 0) g10_1 = 0;
    else if (g10_1 > 255) g10_1 = 255;
    if (b10_1 < 0) b10_1 = 0;
    if (b10_1 > 255) b10_1 = 255;
    
    if (r11_1 < 0) r11_1 = 0;
    else if (r11_1 > 255) r11_1 = 255;
    if (g11_1 < 0) g11_1 = 0;
    else if (g11_1 > 255) g11_1 = 255;
    if (b11_1 < 0) b11_1 = 0;
    else if (b11_1 > 255) b11_1 = 255;

    if (r12_1 < 0) r12_1 = 0;
    else if (r12_1 > 255) r12_1 = 255;
    if (g12_1 < 0) g12_1 = 0;
    else if (g12_1 > 255) g12_1 = 255;
    if (b12_1 < 0) b12_1 = 0;
    else if (b12_1 > 255) b12_1 = 255;

    if (r13_1 < 0) r13_1 = 0;
    else if (r13_1 > 255) r13_1 = 255;
    if (g13_1 < 0) g13_1 = 0;
    else if (g13_1 > 255) g13_1 = 255;
    if (b13_1 < 0) b13_1 = 0;
    else if (b13_1 > 255) b13_1 = 255;

    if (r14_1 < 0) r14_1 = 0;
    else if (r14_1 > 255) r14_1 = 255;
    if (g14_1 < 0) g14_1 = 0;
    else if (g14_1 > 255) g14_1 = 255;
    if (b14_1 < 0) b14_1 = 0;
    if (b14_1 > 255) b14_1 = 255;
    
    if (r15_1 < 0) r15_1 = 0;
    else if (r15_1 > 255) r15_1 = 255;
    if (g15_1 < 0) g15_1 = 0;
    else if (g15_1 > 255) g15_1 = 255;
    if (b15_1 < 0) b15_1 = 0;
    else if (b15_1 > 255) b15_1 = 255;

    if (r16_1 < 0) r16_1 = 0;
    else if (r16_1 > 255) r16_1 = 255;
    if (g16_1 < 0) g16_1 = 0;
    else if (g16_1 > 255) g16_1 = 255;
    if (b16_1 < 0) b16_1 = 0;
    else if (b16_1 > 255) b16_1 = 255;


    output[y*width+x  ].r = r_1;
    output[y*width+x ].g = g_1;
    output[y*width+x  ].b = b_1;
    output[y*width+x+1].r = r2_1;
    output[y*width+x+1].g = g2_1;
    output[y*width+x+1].b = b2_1;
    output[y*width+x+2].r = r3_1;
    output[y*width+x+2].g = g3_1;
    output[y*width+x+2].b = b3_1;
    output[y*width+x+3].r = r4_1;
    output[y*width+x+3].g = g4_1;
    output[y*width+x+3].b = b4_1;
    output[y*width+x+4].r = r5_1;
    output[y*width+x+4].g = g5_1;
    output[y*width+x+4].b = b5_1;
    output[y*width+x+5].r = r6_1;
    output[y*width+x+5].g = g6_1;
    output[y*width+x+5].b = b6_1;
    output[y*width+x+6].r = r7_1;
    output[y*width+x+6].g = g7_1;
    output[y*width+x+6].b = b7_1;
    output[y*width+x+7].r = r8_1;
    output[y*width+x+7].g = g8_1;
    output[y*width+x+7].b = b8_1;
    output[(y+1)*width+x].r = r9_1;
    output[(y+1)*width+x].g = g9_1;
    output[(y+1)*width+x].b = b9_1;
    output[(y+1)*width+x+1 ].r = r10_1;
    output[(y+1)*width+x+1 ].g = g10_1;
    output[(y+1)*width+x+1 ].b = b10_1;
    output[(y+1)*width+x+2].r = r11_1;
    output[(y+1)*width+x+2].g = g11_1;
    output[(y+1)*width+x+2].b = b11_1;
    output[(y+1)*width+x+3].r = r12_1;
    output[(y+1)*width+x+3].g = g12_1;
    output[(y+1)*width+x+3].b = b12_1;
    output[(y+1)*width+x+4].r = r13_1;
    output[(y+1)*width+x+4].g = g13_1;
    output[(y+1)*width+x+4].b = b13_1;
    output[(y+1)*width+x+5].r = r14_1;
    output[(y+1)*width+x+5].g = g14_1;
    output[(y+1)*width+x+5].b = b14_1;
    output[(y+1)*width+x+6].r = r15_1;
    output[(y+1)*width+x+6].g = g15_1;
    output[(y+1)*width+x+6].b = b15_1;
    output[(y+1)*width+x+7].r = r16_1;
    output[(y+1)*width+x+7].g = g16_1;
    output[(y+1)*width+x+7].b = b16_1;
}   

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    for (int y = 0; y < height; y+=2) {
        for (int x = 0; x < width; x+=8) {
            convolution(input,output, x, y, width, height, filter);
        }
    }
}
//4.1 speedup