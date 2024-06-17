#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "bmplib.h"
#include "hw2.h"

// 스레드당 처리할 행의 수
#define THREAD_COUNT 8

// 스레드에 전달할 인수 구조체 정의
typedef struct {
    int start_row;
    int end_row;
    unsigned int width;
    unsigned int height;
    Pixel* input;
    Pixel* output;
    float* filter;
} ThreadArgs;

static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            if ((y + dy) < 0 || (y + dy) >= height)
                continue;

            if ((x + dx) < 0 || (x + dx) >= width)
                continue;

            r += input[(x+dx)+(y+dy)*width].r * filter[(dx+1)+(dy+1)*3];
            g += input[(x+dx)+(y+dy)*width].g * filter[(dx+1)+(dy+1)*3];
            b += input[(x+dx)+(y+dy)*width].b * filter[(dx+1)+(dy+1)*3];
        }
    }

    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    
    Pixel p;
    memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;

    return p;
}

void* threadFunc(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;

    for (int y = threadArgs->start_row; y < threadArgs->end_row; ++y) {
        for (int x = 0; x < threadArgs->width; ++x) {
            Pixel p = convolution(threadArgs->input, x, y, threadArgs->width, threadArgs->height, threadArgs->filter);
            threadArgs->output[x + y * threadArgs->width] = p;
        }
    }

    return NULL;
}

void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = args[2];
    Pixel* output = args[3];
    float* filter = args[4];

    pthread_t threads[THREAD_COUNT];
    ThreadArgs threadArgs[THREAD_COUNT];

    int rowsPerThread = height / THREAD_COUNT;
    int remainingRows = height % THREAD_COUNT;

    // 스레드 생성
    for (int i = 0; i < THREAD_COUNT; ++i) {
        threadArgs[i].start_row = i * rowsPerThread;
        threadArgs[i].end_row = (i + 1) * rowsPerThread;
        if (i == THREAD_COUNT - 1) {
            threadArgs[i].end_row += remainingRows; // 마지막 스레드가 나머지 행 처리
        }
        threadArgs[i].width = width;
        threadArgs[i].height = height;
        threadArgs[i].input = input;
        threadArgs[i].output = output;
        threadArgs[i].filter = filter;

        if (pthread_create(&threads[i], NULL, threadFunc, (void*)&threadArgs[i]) != 0) {
            printf("Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // 스레드 종료 대기
    for (int i = 0; i < THREAD_COUNT; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

}
