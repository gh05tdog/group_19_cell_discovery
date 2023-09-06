//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

//Function to invert pixels of an image (negative)
void invert(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
  for (int x = 0; x < BMP_WIDTH; x++)
  {
    for (int y = 0; y < BMP_HEIGTH; y++)
    {
      for (int c = 0; c < BMP_CHANNELS; c++)
      {
      output_image[x][y][c] = 255 - input_image[x][y][c];
      }
    }
  }
}

void convert_to_gray_scale(unsigned char rgb_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char gray_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
            unsigned char red = rgb_image[x][y][0];
            unsigned char green = rgb_image[x][y][1];
            unsigned char blue = rgb_image[x][y][2];

            unsigned char gray = (red + green + blue) / 3;

            gray_image[x][y] = gray;
        }
    }
}

void gray_to_rgb(unsigned char gray_image[BMP_WIDTH][BMP_HEIGTH], unsigned char rgb_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
            unsigned char gray = gray_image[x][y];
            rgb_image[x][y][0] = gray;
            rgb_image[x][y][1] = gray;
            rgb_image[x][y][2] = gray;
        }
    }
}


void grey_to_binary(unsigned char gray_image[BMP_WIDTH][BMP_HEIGTH], unsigned char binary_image[BMP_WIDTH][BMP_HEIGTH]) {
    for (int x = 0; x < BMP_WIDTH; ++x) {
        for (int y = 0; y < BMP_HEIGTH; ++y) {
            unsigned char gray = gray_image[x][y];
            if (gray > 90) {
                binary_image[x][y] = 255;
            } else {
                binary_image[x][y] = 0;
            }
        }
    }
}


  //Declaring the array to store the image (unsigned char = unsigned 8 bit)
  unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char gray_image[BMP_WIDTH][BMP_HEIGTH];

//Main function
int main(int argc, char** argv)
{
  //argc counts how may arguments are passed
  //argv[0] is a string with the name of the program
  //argv[1] is the first command line argument (input image)
  //argv[2] is the second command line argument (output image)

  //Checking that 2 arguments are passed
  if (argc != 3)
  {
      fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
      exit(1);
  }

  //Load image from file
  read_bitmap(argv[1], input_image);

    // Convert to grayscale
    convert_to_gray_scale(input_image, gray_image);

    unsigned char binary_image[BMP_WIDTH][BMP_HEIGTH];

    // Convert to binary
    grey_to_binary(gray_image, binary_image);

    // Convert 2D grayscale image back to 3D RGB image
    gray_to_rgb(binary_image, output_image);

    // Save image to file
    write_bitmap(output_image, argv[2]);

  printf("Done!\n");
  return 0;
}
