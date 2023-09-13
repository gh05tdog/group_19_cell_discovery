
#include "cell_check.h"
#include "global_vars.h"
void add_squares(unsigned char rgb_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], Coordinate coordinates[1000]) {
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


