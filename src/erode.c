#include "cbmp.h"
#include "erode.h"

#define BLACK 0
#define WHITE 255

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGHT], unsigned char eroded[BMP_WIDTH][BMP_HEIGHT],
                  int *any_pixel_eroded) {
    int structuring_element[3][3] = {
            {0,1,1},
            {1, 1,1},
            {1,1, 1},
    };

    *any_pixel_eroded = 0;

    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGHT; ++y) {
            unsigned char pixel = binary[x][y];

            if (pixel == BLACK) {
                eroded[x][y] = BLACK;
            } else {
                int should_erode = 1;

                for (int i = -1; i <= 1 && should_erode; ++i) {
                    for (int j = -1; j <= 1 && should_erode; ++j) {
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

                eroded[x][y] = should_erode ? WHITE : BLACK;

                if (should_erode == 0) {
                    *any_pixel_eroded = 1;
                }
            }
        }
    }
}
