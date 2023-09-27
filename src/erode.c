#include <stdlib.h>
#include "cbmp.h"
#include "erode.h"

#define BLACK 0
#define WHITE 255

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGHT],
                  int *any_pixel_eroded) {
    int* eroded_line = (int*)malloc(BMP_WIDTH*BMP_HEIGHT * sizeof(int));
    int structuring_element[5][5] = {
            {0, 1, 1, 1, 0},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {0, 1, 1, 1, 0}
    };
    *any_pixel_eroded = 0;
    int k = 0;
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char pixel = binary[x][y];

            if (pixel == BLACK) {
                eroded_line[k++] = BLACK;
            } else {
                int should_erode = 1;

                for (int i = -2; i <= 2 && should_erode; ++i) {
                    for (int j = -2; j <= 2 && should_erode; ++j) {
                        int newX = x + i;
                        int newY = y + j;

                        // Assume pixels outside the boundary are BLACK (0)
                        unsigned char neighbor = BLACK;
                        if (newX >= 0 && newY >= 0 && newX < BMP_WIDTH && newY < BMP_HEIGHT) {
                            neighbor = binary[newX][newY];
                        }

                        if (structuring_element[i + 1][j + 1] == 1 && neighbor == BLACK) {
                            should_erode = 0;
                        }
                    }
                }

                eroded_line[k++] = should_erode ? WHITE : BLACK;

                if (should_erode == 0) {
                    *any_pixel_eroded = 1;
                }
            }

        }
    }
    

    k = 0;
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            binary[x][y] = eroded_line[k];
            k++;
        }
    }
    free(eroded_line);

}

