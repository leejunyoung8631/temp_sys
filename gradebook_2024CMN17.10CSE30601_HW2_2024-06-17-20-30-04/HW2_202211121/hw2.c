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
/*
하... 이게 한계야 셤 끝나고 밤샘 코딩 정신 나갈 것 같아'ㄻ;닐 ㅓ;ㅓㅐㄴ리;ㅏㅓㅁㄴㅇ;ㅣㄴㅇ라ㅓㅣ
*/
// 필터 크기
#define FILTER_SIZE 3
#define FILTER_HALF (FILTER_SIZE / 2)

// 이미지 중앙 부분에 필터를 적용하는 함수, 경계 제외
void filter_center(unsigned int width, unsigned int height, Pixel* input, Pixel* output, float* filter) {
    // 이미지의 중앙 부분 픽셀마다 필터 적용
    for (int y = FILTER_HALF; y < height - FILTER_HALF; ++y) {
        for (int x = FILTER_HALF; x < width - FILTER_HALF; ++x) {
            double r = 0.0, g = 0.0, b = 0.0;

            // 각 픽셀 주변에 필터 적용 (루프 언롤링을 통한 최적화)
            Pixel p;
            float f;

            // -1, -1
            p = input[(x - 1) + (y - 1) * width];
            f = filter[0];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // 0, -1
            p = input[(x) + (y - 1) * width];
            f = filter[1];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // +1, -1
            p = input[(x + 1) + (y - 1) * width];
            f = filter[2];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // -1, 0
            p = input[(x - 1) + (y) * width];
            f = filter[3];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // 0, 0
            p = input[(x) + (y) * width];
            f = filter[4];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // +1, 0
            p = input[(x + 1) + (y) * width];
            f = filter[5];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // -1, +1
            p = input[(x - 1) + (y + 1) * width];
            f = filter[6];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // 0, +1
            p = input[(x) + (y + 1) * width];
            f = filter[7];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // +1, +1
            p = input[(x + 1) + (y + 1) * width];
            f = filter[8];
            r += p.r * f;
            g += p.g * f;
            b += p.b * f;

            // 결과 저장
            Pixel* out = &output[x + y * width];
            out->r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            out->g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            out->b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
        }
    }
}

// 경계 부분 필터링 함수
void filter_boundary(unsigned int width, unsigned int height, Pixel* input, Pixel* output, float* filter) {
    // 상단과 하단 경계 필터링
    for (int y = 0; y < height; y += height - 1) { // 첫 번째와 마지막 행을 처리
        for (int x = 0; x < width; ++x) {
            double r = 0.0, g = 0.0, b = 0.0;

            for (int dy = -FILTER_HALF; dy <= FILTER_HALF; ++dy) {
                int iy = y + dy;
                if (iy < 0 || iy >= height) continue; // 경계 조건 확인

                for (int dx = -FILTER_HALF; dx <= FILTER_HALF; ++dx) {
                    int ix = x + dx;
                    if (ix < 0 || ix >= width) continue; // 경계 조건 확인

                    int filter_index = (dx + 1) + (dy + 1) * FILTER_SIZE;
                    Pixel p = input[ix + iy * width];
                    float f = filter[filter_index];
                    r += p.r * f;
                    g += p.g * f;
                    b += p.b * f;
                }
            }

            Pixel* out = &output[x + y * width];
            out->r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            out->g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            out->b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
        }
    }

    // 좌측과 우측 경계 필터링
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 0; x < width; x += width - 1) { // 첫 번째와 마지막 열을 처리
            double r = 0.0, g = 0.0, b = 0.0;

            for (int dy = -FILTER_HALF; dy <= FILTER_HALF; ++dy) {
                int iy = y + dy;
                if (iy < 0 || iy >= height) continue; // 경계 조건 확인

                for (int dx = -FILTER_HALF; dx <= FILTER_HALF; ++dx) {
                    int ix = x + dx;
                    if (ix < 0 || ix >= width) continue; // 경계 조건 확인

                    int filter_index = (dx + 1) + (dy + 1) * FILTER_SIZE;
                    Pixel p = input[ix + iy * width];
                    float f = filter[filter_index];
                    r += p.r * f;
                    g += p.g * f;
                    b += p.b * f;
                }
            }

            Pixel* out = &output[x + y * width];
            out->r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
            out->g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
            out->b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
        }
    }
}

// 최적화된 필터 함수
void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    // 중심부 필터링
    filter_center(width, height, input, output, filter);

    // 경계 부분 필터링
    filter_boundary(width, height, input, output, filter);
}
