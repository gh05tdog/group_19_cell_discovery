//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include <intrin.h>
#include "cbmp.h"
#include "src/erode.h"
#include "src/cell_check.h"
#include "src/global_vars.h"
#include "src/add_squares.h"

Coordinate coordinates[1000]; // Assuming a maximum of 1000 cells
int coord_index = 0;


void convert_to_binary(unsigned char rgb_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
                           unsigned char binary_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
            unsigned char red = rgb_image[x][y][0];
            unsigned char green = rgb_image[x][y][1];
            unsigned char blue = rgb_image[x][y][2];
            unsigned char gray = (red + green + blue) / 3;

            binary_image[x][y] = gray;
        }
    }

    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
            unsigned char gray = binary_image[x][y];
            if (gray > 85) {
                binary_image[x][y] = 255;
            } else {
                binary_image[x][y] = 0;
            }
        }
    }
}

void gray_to_rgb(unsigned char gray_image[BMP_WIDTH][BMP_HEIGTH],
                 unsigned char rgb_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], Coordinate coordinates[1000]){
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
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
        for (int j = x - 6; j <= x + 6; ++j) {
            rgb_image[j][y - 6][0] = 255;
            rgb_image[j][y - 6][1] = 0;
            rgb_image[j][y - 6][2] = 0;
            rgb_image[j][y + 6][0] = 255;
            rgb_image[j][y + 6][1] = 0;
            rgb_image[j][y + 6][2] = 0;
        }
        for (int j = y - 6; j <= y + 6; ++j) {
            rgb_image[x - 6][j][0] = 255;
            rgb_image[x - 6][j][1] = 0;
            rgb_image[x - 6][j][2] = 0;
            rgb_image[x + 6][j][0] = 255;
            rgb_image[x + 6][j][1] = 0;
            rgb_image[x + 6][j][2] = 0;
        }
    }
}

//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char current_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char binary_image[BMP_WIDTH][BMP_HEIGTH];
unsigned char eroded_image[BMP_WIDTH][BMP_HEIGTH];


//Main function
int main(int argc, char **argv) {
    int cells = 0;
    int is_eroded;
    //argc counts how may arguments are passed
    //argv[0] is a string with the name of the program
    //argv[1] is the first command line argument (input image)
    //argv[2] is the second command line argument (output image)

    //Checking that 2 arguments are passed
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
        exit(1);
    }
    // Load image from file
    read_bitmap(argv[1], input_image);

    // Convert to binary (assuming this function populates current_image)
    convert_to_binary(input_image, binary_image);


    binary_erode(binary_image, eroded_image, &is_eroded);
    int i = 0;
    // Perform the erosion 10 times
    while(1) {
        ++i;
        char str[32];

        strcpy(str,"../eroded_images/eroded_image ");

        char numStr[23];

        snprintf(numStr,sizeof(numStr),"%d",i);
        strcat(str,numStr);

        strcat(str,".bmp");


        binary_erode(eroded_image, current_image, &is_eroded);
        cell_check(eroded_image,current_image, &cells);

        gray_to_rgb(eroded_image, output_image, coordinates);
        write_bitmap(output_image, str);

        // Copy the current_image image back into eroded_image for the next round
        memcpy(eroded_image, current_image, sizeof(current_image));

        if(is_eroded == 0) {
            break;
        }
    }


    printf("The numbers of cells found is: %d\n",cells);
// After you've found all the cells and before you write the final image
    add_squares(input_image, coordinates);

// Write image to file
    write_bitmap(input_image, argv[2]);
    printf("Done!\n");
    return 0;
}

