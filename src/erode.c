#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char eroded[BMP_WIDTH][BMP_HEIGTH]) {


    int structuring_element[3][3] = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0}
    };


    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {

            unsigned char pixel = binary[x][y];

            if (pixel == 0) {
                eroded[x][y] = 0;
            } else {
                int is_eroded = 1;
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {

                        int newX = x + i;
                        int newY = y + j;

                        // Handle boundary conditions
                        if (newX < 0 || newY < 0 || newX >= BMP_WIDTH || newY >= BMP_HEIGTH) {
                            continue;
                        }

                        int structuring_element_pixel = structuring_element[i + 1][j + 1];
                        int image_pixel = binary[newX][newY];

                        if (structuring_element_pixel == 1 && image_pixel == 0) {
                            is_eroded = 0;
                            break;
                        }
                    }
                    if (is_eroded == 0) {
                        break;
                    }
                }
                eroded[x][y] = is_eroded ? 255 : 0;
            }
        }
    }

}