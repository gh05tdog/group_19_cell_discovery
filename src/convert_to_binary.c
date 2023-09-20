#include "cell_check.h"
#include <stdio.h>

void convert_to_binary(unsigned char rgb_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS],
                       unsigned char binary_image[BMP_WIDTH][BMP_HEIGHT]) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char red = rgb_image[x][y][0];
            unsigned char green = rgb_image[x][y][1];
            unsigned char blue = rgb_image[x][y][2];
            unsigned char gray = (red + green + blue) / 3;

            binary_image[x][y] = gray;
        }
    }

    float sum = 0;
    float sumB = 0;
    int q1 = 0;
    int q2;
    float varMax = 0;
    int threshold = 0;

    int histogram[256] = {0};

// Calculate histogram
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char gray = binary_image[x][y];
            histogram[gray]++;
        }
    }

// Total number of pixels
    int total = BMP_WIDTH * BMP_HEIGHT;

// Calculate sum of pixels
    for (int i = 0; i < 256; ++i) {
        sum += (float ) i * (float)histogram[i];
    }

// Compute Otsu's threshold
    for (int i = 0; i < 256; ++i) {
        q1 += histogram[i];
        if (q1 == 0) continue;
        q2 = total - q1;
        if (q2 == 0) break;
        sumB += (float)(i * histogram[i]);
        float m1 = sumB / (float)q1;
        float m2 = (sum - sumB) / (float)q2;
        float varBetween = (float)q1 * (float)q2 * (m1 - m2) * (m1 - m2);
        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = i;
        }
    }
    printf("the threshold is: %i \n", threshold);

// Apply Otsu's threshold

    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char gray = binary_image[x][y];
            if (gray >= threshold) {
                binary_image[x][y] = 255;
            } else {
                binary_image[x][y] = 0;
            }
        }
    }
}