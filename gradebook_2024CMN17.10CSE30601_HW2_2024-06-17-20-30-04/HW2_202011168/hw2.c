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

// 매크로
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// 0~255 초과 제한하는 함수를 Inline 함수로 구현
static inline unsigned char clamp(float value) {
    return (unsigned char)MIN(255, MAX(0, value));
}

// 컨볼루션 없애고 합치기
void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0]; 
    unsigned int height = *(unsigned int*)args[1]; 
    Pixel* input = (Pixel*)args[2]; 
    Pixel* output = (Pixel*)args[3]; 
    float* filter = (float*)args[4]; 

    // 조건문 계산 미리 하기
    unsigned int width_minus_1 = width - 1; 
    unsigned int height_minus_1 = height - 1; 

    // 경계 부분 제외한 부분(9개의 필터 모두 합해지는 부분)
    for (int y = 1; y < height_minus_1; ++y) {
        for (int x = 1; x < width_minus_1; x += 2) {
            
            // 조건문 계산 미리 하기
            int index1 = x + y * width; // associative 1
            int index2 = index1 + 1; // associaitive 2

            // 각 픽셀에 대한 별도의 누적 변수
            float r1 = 0, g1 = 0, b1 = 0;
            float r2 = 0, g2 = 0, b2 = 0;

            // 데이터 지역성을 개선하기 위해 이웃 픽셀의 인덱스를 미리 계산
            int t1 = index1 - width, t2 = index2 - width; // 위쪽 픽셀
            int k1 = index1 + width, k2 = index2 + width; // 아래쪽 픽셀

            // 위쪽 행
            r1 += input[t1 - 1].r * filter[0] + input[t1].r * filter[1] + input[t1 + 1].r * filter[2];
            g1 += input[t1 - 1].g * filter[0] + input[t1].g * filter[1] + input[t1 + 1].g * filter[2];
            b1 += input[t1 - 1].b * filter[0] + input[t1].b * filter[1] + input[t1 + 1].b * filter[2];

            r2 += input[t2 - 1].r * filter[0] + input[t2].r * filter[1] + input[t2 + 1].r * filter[2];
            g2 += input[t2 - 1].g * filter[0] + input[t2].g * filter[1] + input[t2 + 1].g * filter[2];
            b2 += input[t2 - 1].b * filter[0] + input[t2].b * filter[1] + input[t2 + 1].b * filter[2];

            // 중간 행
            r1 += input[index1 - 1].r * filter[3] + input[index1].r * filter[4] + input[index1 + 1].r * filter[5];
            g1 += input[index1 - 1].g * filter[3] + input[index1].g * filter[4] + input[index1 + 1].g * filter[5];
            b1 += input[index1 - 1].b * filter[3] + input[index1].b * filter[4] + input[index1 + 1].b * filter[5];

            r2 += input[index2 - 1].r * filter[3] + input[index2].r * filter[4] + input[index2 + 1].r * filter[5];
            g2 += input[index2 - 1].g * filter[3] + input[index2].g * filter[4] + input[index2 + 1].g * filter[5];
            b2 += input[index2 - 1].b * filter[3] + input[index2].b * filter[4] + input[index2 + 1].b * filter[5];

            // 아래쪽 행
            r1 += input[k1 - 1].r * filter[6] + input[k1].r * filter[7] + input[k1 + 1].r * filter[8];
            g1 += input[k1 - 1].g * filter[6] + input[k1].g * filter[7] + input[k1 + 1].g * filter[8];
            b1 += input[k1 - 1].b * filter[6] + input[k1].b * filter[7] + input[k1 + 1].b * filter[8];

            r2 += input[k2 - 1].r * filter[6] + input[k2].r * filter[7] + input[k2 + 1].r * filter[8];
            g2 += input[k2 - 1].g * filter[6] + input[k2].g * filter[7] + input[k2 + 1].g * filter[8];
            b2 += input[k2 - 1].b * filter[6] + input[k2].b * filter[7] + input[k2 + 1].b * filter[8];

            
            output[index1].r = clamp(r1);
            output[index1].g = clamp(g1);
            output[index1].b = clamp(b1);

            output[index2].r = clamp(r2);
            output[index2].g = clamp(g2);
            output[index2].b = clamp(b2);
        }
    }

    // 경계부분 처리 (위 아래 행)
    for (int x = 0; x < width; ++x) {
        int index_top = x;
        int index_bottom = x + height_minus_1 * width;

        float top_r = 0, top_g = 0, top_b = 0;
        float bottom_r = 0, bottom_g = 0, bottom_b = 0;

        // 위쪽 행 4와 7은 필수, 나머지는 조건문 따라, 0,1,2는 무조건 삭제
        //(0,0) 아닐때
        if (x > 0) {
            top_r += input[index_top - 1].r * filter[3];
            top_g += input[index_top - 1].g * filter[3];
            top_b += input[index_top - 1].b * filter[3];
        }

        top_r += input[index_top].r * filter[4];
        top_g += input[index_top].g * filter[4];
        top_b += input[index_top].b * filter[4];
        
        //오른쪽 모서리 아닐때
        if (x < width_minus_1) {
            top_r += input[index_top + 1].r * filter[5];
            top_g += input[index_top + 1].g * filter[5];
            top_b += input[index_top + 1].b * filter[5];
        }

        top_r += input[index_top + width].r * filter[7];
        top_g += input[index_top + width].g * filter[7];
        top_b += input[index_top + width].b * filter[7];

        //(0,0) 아닐때
        if (x > 0) {
            top_r += input[index_top + width - 1].r * filter[6];
            top_g += input[index_top + width - 1].g * filter[6];
            top_b += input[index_top + width - 1].b * filter[6];
        }
        //오른쪽 모서리 아닐때
        if (x < width_minus_1) {
            top_r += input[index_top + width + 1].r * filter[8];
            top_g += input[index_top + width + 1].g * filter[8];
            top_b += input[index_top + width + 1].b * filter[8];
        }

        output[index_top].r = clamp(top_r);
        output[index_top].g = clamp(top_g);
        output[index_top].b = clamp(top_b);

        // 아래쪽 행, 1과 4는 필수, 6,7,8은 무조건 삭제
        //왼쪽 하단 모서리 아닐때
        if (x > 0) {
            bottom_r += input[index_bottom - width - 1].r * filter[0];
            bottom_g += input[index_bottom - width - 1].g * filter[0];
            bottom_b += input[index_bottom - width - 1].b * filter[0];
        }
        // 오른쪽 하단 모서리 아닐때
        if (x < width_minus_1) {
            bottom_r += input[index_bottom - width + 1].r * filter[2];
            bottom_g += input[index_bottom - width + 1].g * filter[2];
            bottom_b += input[index_bottom - width + 1].b * filter[2];
        }
        // 필수
        bottom_r += input[index_bottom - width].r * filter[1];
        bottom_g += input[index_bottom - width].g * filter[1];
        bottom_b += input[index_bottom - width].b * filter[1];

        // 왼쪽 하단 모서리 아닐때
        if (x > 0) {
            bottom_r += input[index_bottom - 1].r * filter[3];
            bottom_g += input[index_bottom - 1].g * filter[3];
            bottom_b += input[index_bottom - 1].b * filter[3];
        }

        //필수
        bottom_r += input[index_bottom].r * filter[4];
        bottom_g += input[index_bottom].g * filter[4];
        bottom_b += input[index_bottom].b * filter[4];

        // 오른쪽 하단 모서리 아닐때
        if (x < width_minus_1) {
            bottom_r += input[index_bottom + 1].r * filter[5];
            bottom_g += input[index_bottom + 1].g * filter[5];
            bottom_b += input[index_bottom + 1].b * filter[5];
        }

        output[index_bottom].r = clamp(bottom_r);
        output[index_bottom].g = clamp(bottom_g);
        output[index_bottom].b = clamp(bottom_b);
    }

    // 경계부분 처리 (좌우열), 모서리 4군데는 위에서 처리했으니까 여기서는 처리 X
    for (int y = 1; y < height_minus_1; ++y) {
        
        // 왼쪽 열, 0,3,6 삭제, 나머지는 필수
        int index_left = y * width;

        float left_r = 0, left_g = 0, left_b = 0;

        left_r += input[index_left - width].r * filter[1];
        left_g += input[index_left - width].g * filter[1];
        left_b += input[index_left - width].b * filter[1];

        left_r += input[index_left - width + 1].r * filter[2];
        left_g += input[index_left - width + 1].g * filter[2];
        left_b += input[index_left - width + 1].b * filter[2];

        left_r += input[index_left].r * filter[4];
        left_g += input[index_left].g * filter[4];
        left_b += input[index_left].b * filter[4];

        left_r += input[index_left + 1].r * filter[5];
        left_g += input[index_left + 1].g * filter[5];
        left_b += input[index_left + 1].b * filter[5];

        left_r += input[index_left + width].r * filter[7];
        left_g += input[index_left + width].g * filter[7];
        left_b += input[index_left + width].b * filter[7];

        left_r += input[index_left + width + 1].r * filter[8];
        left_g += input[index_left + width + 1].g * filter[8];
        left_b += input[index_left + width + 1].b * filter[8];

        output[index_left].r = clamp(left_r);
        output[index_left].g = clamp(left_g);
        output[index_left].b = clamp(left_b);


        // 우측 열, 2,5,7 삭제
        int index_right = (y + 1) * width - 1;

        float right_r = 0, right_g = 0, right_b = 0;

        right_r += input[index_right - width].r * filter[1];
        right_g += input[index_right - width].g * filter[1];
        right_b += input[index_right - width].b * filter[1];

        right_r += input[index_right - width - 1].r * filter[0];
        right_g += input[index_right - width - 1].g * filter[0];
        right_b += input[index_right - width - 1].b * filter[0];

        right_r += input[index_right].r * filter[4];
        right_g += input[index_right].g * filter[4];
        right_b += input[index_right].b * filter[4];

        right_r += input[index_right - 1].r * filter[3];
        right_g += input[index_right - 1].g * filter[3];
        right_b += input[index_right - 1].b * filter[3];

        right_r += input[index_right + width].r * filter[7];
        right_g += input[index_right + width].g * filter[7];
        right_b += input[index_right + width].b * filter[7];

        right_r += input[index_right + width - 1].r * filter[6];
        right_g += input[index_right + width - 1].g * filter[6];
        right_b += input[index_right + width - 1].b * filter[6];

        output[index_right].r = clamp(right_r);
        output[index_right].g = clamp(right_g);
        output[index_right].b = clamp(right_b);
    }
}