#include "cell_check.h"
#include <stdio.h>
#include "global_vars.h"


void cell_check(unsigned char eroded_image[BMP_WIDTH][BMP_HEIGHT], int *cells) {
    int x = 0;
    int count = 0;

    while (x < BMP_WIDTH) {
        int y = 0;

        while (y < BMP_HEIGHT) {
            if (eroded_image[x][y] == 255) {
                int i = 6;
                int is_clear = 1;


//___________________________________________________________________________________________
                while (i >= -6) {
                    unsigned char boundary1;
                    unsigned char boundary2;
                    unsigned char boundary3;
                    unsigned char boundary4;

                    if (x + i <= 0) {
                        boundary1 = eroded_image[0][y + 7];
                        boundary2 = eroded_image[0][y - 7];
                    } else if (x + i >= BMP_WIDTH - 1) {
                        boundary1 = eroded_image[BMP_WIDTH - 1][y + 7];
                        boundary2 = eroded_image[BMP_WIDTH - 1][y - 7];
                    } else {
                        boundary1 = eroded_image[x + i][y + 7];
                        boundary2 = eroded_image[x + i][y - 7];
                    }

                    if (y + i <= 0) {
                        boundary3 = eroded_image[x - 7][0];
                        boundary4 = eroded_image[x + 7][0];
                    } else if (y + i >= BMP_HEIGHT - 1) {
                        boundary3 = eroded_image[x - 7][BMP_HEIGHT - 1];
                        boundary4 = eroded_image[x + 7][BMP_HEIGHT - 1];
                    } else {
                        boundary3 = eroded_image[x - 7][y + i];
                        boundary4 = eroded_image[x + 7][y + i];
                    }

                    if (boundary3 == 255 || boundary4 == 255) {
                        is_clear = 0;
                        y = y + 6 + i;
                        break;
                    } else if (boundary1 == 255 || boundary2 == 255) {
                        is_clear = 0;
                        break;
                    }


                    i--;
                }

//____________________________________________________________________________________________

                if (is_clear == 1) {
                    coordinates[coord_index].x = x;
                    coordinates[coord_index].y = y;
                    coord_index++;

                    for (int p = x - 6; p <= x + 6; ++p) {
                        for (int q = y - 6; q <= y + 6; q++) {
                            eroded_image[p][q] = 0;
                        }
                    }
                    count++;
                    break;
                }
            }
            y++;
        }
        x++;
    }

    int total = *cells += count;
    printf("The count of cells is: %d", total);
    printf("\n");
}