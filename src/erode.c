#include <stdlib.h>
#include "cbmp.h"
#include "erode.h"


#define BLACK 0
#define WHITE 1

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGHT], int *did_erode) {

    // erosion (with the expection of bitwise datasaving) is written by Marcus


    // written by Martin with the help of chatGPT
    unsigned char *temp = (unsigned char *) malloc(((BMP_WIDTH * BMP_HEIGHT/8) * sizeof(unsigned char)));

    *did_erode = 0;
    // written by Oliver
    int structuring_element[5][5] = {
            {0, 1, 1, 1, 0},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {0, 1, 1, 1, 0}
    };

    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {

            unsigned char pixel = binary[x][y];

            if (pixel == BLACK) {
                temp[(x * BMP_HEIGHT + y) / 8] &= ~(1 << (7 - (x * BMP_HEIGHT + y) % 8));
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

                        if (structuring_element[i + 2][j + 2] == WHITE && neighbor == BLACK) {
                            should_erode = 0;
                        }
                    }
                }
                // pack bitwise into temp
                if (should_erode) {
                    temp[(x * BMP_HEIGHT + y) / 8] |= (1 << (7 - (x * BMP_HEIGHT + y) % 8));
                } else {
                    temp[(x * BMP_HEIGHT + y) / 8] &= ~(1 << (7 - (x * BMP_HEIGHT + y) % 8));
                }
            }
        }
    }

    // written by Martin, with the help of chatGPT
    // Copy the temp image back into binary
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            int bit_position = (x * BMP_HEIGHT + y) % 8;
            unsigned char byte = temp[(x * BMP_HEIGHT + y) / 8];

            // Check the specific bit within the byte
            int bit_value = (byte >> (7 - bit_position)) & 1;

            if (bit_value == 1) {
                binary[x][y] = 255;
            } else {
                binary[x][y] = BLACK;
            }

            if (binary[x][y] != ((temp[(x * BMP_HEIGHT + y) / 8] >> (7 - (x * BMP_HEIGHT + y) % 8)) & 1)) {
                *did_erode = 1;
            }
        }
    }
    free(temp);
}
