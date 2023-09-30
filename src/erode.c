#include <stdlib.h>
#include "cbmp.h"
#include "erode.h"


#define BLACK 0
#define WHITE 255

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGHT], int* did_erode) {
    unsigned char temp[BMP_WIDTH][BMP_HEIGHT];
    *did_erode = 0;
    int structuring_element[5][5] = {
            {0, 1, 1, 1, 0},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {0, 1, 1, 1, 0}
    };

    // Initialize temp with the same values as binary
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            temp[x][y] = binary[x][y];
        }
    }

    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char pixel = binary[x][y];

            if (pixel == BLACK) {
                temp[x][y] = BLACK;
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

                        if (structuring_element[i + 2][j + 2] == 1 && neighbor == BLACK) {
                            should_erode = 0;
                        }
                    }
                }

                temp[x][y] = should_erode ? WHITE : BLACK;
            }
        }
    }

    // Copy the temp image back into binary
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            if (binary [x][y] != temp[x][y]) {
                *did_erode = 1;

            }
            binary[x][y] = temp[x][y];
        }
    }
}
