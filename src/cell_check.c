//
// Created by marti on 12/09/2023.
//

#include "cell_check.h"
#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

void cell_check (unsigned char eroded_image[BMP_WIDTH][BMP_HEIGTH], unsigned char checked_image[BMP_WIDTH][BMP_HEIGTH]) {
    int count = 0;

    int x = 0;

    while (x < BMP_WIDTH-2) {

        int y = 0;

        while (y < BMP_HEIGTH) {

            unsigned char eroded = eroded_image[x][y];
            if (eroded == 255) {
                int i = 6;
                int is_clear = 1;

//___________________________________________________________________________________________
                while (i >= -6) {
                    unsigned char boundary1 = eroded_image[x - i][y + 7];
                    unsigned char boundary2 = eroded_image[x - i][y - 7];
                    unsigned char boundary3 = eroded_image[x - 7][y + i];
                    unsigned char boundary4 = eroded_image[x + 7][y + i];

                    if (boundary3 == 255 || boundary4 == 255) {
                        is_clear = 0;
                        y = y + 7 + i;
                        break;
                    }
                    if (boundary1 == 255 || boundary2 == 255) {
                        is_clear = 0;
                        y++;
                        break;
                    }
                    i--;
                }
//____________________________________________________________________________________________

                if (is_clear == 1) {
                    for (int p = x - 6; p <= x + 6; ++p) {
                        for (int q = y - 6; q <= y + 6; q++) {
                            if (eroded_image[p][q] == 255) {
                                checked_image[p][q] = 0;
                                eroded_image[p][q] = 0;
                            }
                            if (eroded_image[p][q] == 0) {
                                checked_image[p][q] = 255;
                            }
                        }

                    }
                    printf("x = %d", x);
                    printf(" y = %d", y);
                    printf("\n");
                    count++;
                    break;
                }
            }

//____________________________________________________________________________________
            else {
                y++;
            }
        }
        x++;
    }


    printf("The count of cells is: %d",count);
}