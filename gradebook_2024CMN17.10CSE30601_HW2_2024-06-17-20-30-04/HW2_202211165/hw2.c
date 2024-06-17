#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "hw2.h"

// ����ȭ�� ���� �Լ� (�� �켱 ���)
void filter_optimized(void* args[]) {
    unsigned int width = *(unsigned int*)args[0];
    unsigned int height = *(unsigned int*)args[1];
    Pixel* input = (Pixel*)args[2];
    Pixel* output = (Pixel*)args[3];
    float* filter = (float*)args[4];

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float r = 0;
            float g = 0;
            float b = 0;

            // ������� ���� ����
            for (int dy = -1; dy <= 1; ++dy) {
                int y_pos = y + dy;
                if (y_pos < 0 || y_pos >= height)
                    continue;

                for (int dx = -1; dx <= 1; ++dx) {
                    int x_pos = x + dx;
                    if (x_pos < 0 || x_pos >= width)
                        continue;

                    Pixel pixel = input[x_pos + y_pos * width];
                    float filter_value = filter[(dx + 1) + (dy + 1) * 3];

                    r += pixel.r * filter_value;
                    g += pixel.g * filter_value;
                    b += pixel.b * filter_value;
                }
            }

            // ���� [0, 255] ������ ���� �� ���������� ĳ����
            int ir = (int)(r < 0 ? 0 : (r > 255 ? 255 : r));
            int ig = (int)(g < 0 ? 0 : (g > 255 ? 255 : g));
            int ib = (int)(b < 0 ? 0 : (b > 255 ? 255 : b));

            // ��� �ȼ��� output �迭�� ����
            output[x + y * width].r = (unsigned char)ir;
            output[x + y * width].g = (unsigned char)ig;
            output[x + y * width].b = (unsigned char)ib;
        }
    }
}
