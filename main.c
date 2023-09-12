//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include <intrin.h>
#include "cbmp.h"
#include "src/erode.h"

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
            if (gray > 90) {
                binary_image[x][y] = 255;
            } else {
                binary_image[x][y] = 0;
            }
        }
    }
}

void gray_to_rgb(unsigned char gray_image[BMP_WIDTH][BMP_HEIGTH],
                 unsigned char rgb_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
            unsigned char gray = gray_image[x][y];
            rgb_image[x][y][0] = gray;
            rgb_image[x][y][1] = gray;
            rgb_image[x][y][2] = gray;
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


    binary_erode(binary_image, eroded_image);

    // Perform the erosion 10 times
    for(int i = 1; i < 10; ++i) {
        binary_erode(eroded_image, current_image);

        // Copy the current_image image back into eroded_image for the next round
        memcpy(eroded_image, current_image, sizeof(current_image));
    }

    // Save the final eroded image
    gray_to_rgb(eroded_image, output_image);
    write_bitmap(output_image, "../eroded_image.bmp");

    printf("Done!\n");
    return 0;
}

