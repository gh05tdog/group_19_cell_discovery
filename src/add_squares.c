#include "cell_check.h"
#include "global_vars.h"
// aad squares is written by Oliver
void add_squares(unsigned char rgb_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS], Coordinate coordinates[1000]) {
    for (int i = 0; i < coord_index; ++i) {
        int x = coordinates[i].x;
        int y = coordinates[i].y;

        for (int j = -12; j <= 12; ++j) {
            for (int thickness = -1; thickness <= 1; ++thickness) {
                if (x + j >= 0 && x + j < BMP_WIDTH && y + thickness >= 0 && y + thickness < BMP_HEIGHT) {
                    rgb_image[x + j][y + thickness][0] = 255;
                    rgb_image[x + j][y + thickness][1] = 0;
                    rgb_image[x + j][y + thickness][2] = 0;
                }
                // Vertical part of the cross
                if (x + thickness >= 0 && x + thickness < BMP_WIDTH && y + j >= 0 && y + j < BMP_HEIGHT) {
                    rgb_image[x + thickness][y + j][0] = 255;
                    rgb_image[x + thickness][y + j][1] = 0;
                    rgb_image[x + thickness][y + j][2] = 0;
                }
            }
        }
    }
}
