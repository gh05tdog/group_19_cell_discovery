#include "cell_check.h"
#include "global_vars.h"
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
        sum += (float) i * (float) histogram[i];
    }

// Compute Otsu's threshold
    for (int i = 0; i < 256; ++i) {
        q1 += histogram[i];
        if (q1 == 0) continue;
        q2 = total - q1;
        if (q2 == 0) break;
        sumB += (float) (i * histogram[i]);
        float m1 = sumB / (float) q1;
        float m2 = (sum - sumB) / (float) q2;
        float varBetween = (float) q1 * (float) q2 * (m1 - m2) * (m1 - m2);
        if (varBetween > varMax) {
            varMax = varBetween;
            threshold = i-15;
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

void gray_to_rgb(unsigned char gray_image[950][950], unsigned char rgb_image[950][950][3] ) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char gray = gray_image[x][y];
            rgb_image[x][y][0] = gray;
            rgb_image[x][y][1] = gray;
            rgb_image[x][y][2] = gray;
        }
    }
    //Add a red square around the cells
    for (int i = 0; i < coord_index; ++i) {
        int x = coordinates[i].x;
        int y = coordinates[i].y;

        // Add a thicker and bigger red cross around the cell
        for (int j = -12; j <= 12; ++j) {
            // Check if the pixel is within the image boundaries
            if (x + j >= 0 && x + j < BMP_WIDTH && y >= 0 && y < BMP_HEIGHT) {
                rgb_image[x + j][y][0] = 255;
                rgb_image[x + j][y][1] = 0;
                rgb_image[x + j][y][2] = 0;
            }
            if (x >= 0 && x < BMP_WIDTH && y + j >= 0 && y + j < BMP_HEIGHT) {
                rgb_image[x][y + j][0] = 255;
                rgb_image[x][y + j][1] = 0;
                rgb_image[x][y + j][2] = 0;
            }
        }
    }
}