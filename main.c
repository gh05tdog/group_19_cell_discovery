//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include <intrin.h>
#include <time.h>

#include "cbmp.h"
#include "src/erode.h"
#include "src/cell_check.h"
#include "src/global_vars.h"
#include "src/add_squares.h"
#include "src/convert_to_binary.h"

Coordinate coordinates[1000]; // Assuming a maximum of 1000 cells
int coord_index = 0;

//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
unsigned char output_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
unsigned char current_image[BMP_WIDTH][BMP_HEIGHT];
unsigned char binary_image[BMP_WIDTH][BMP_HEIGHT];
unsigned char eroded_image[BMP_WIDTH][BMP_HEIGHT];


//Main function
int main(int argc, char **argv) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int cells = 0;
    int is_eroded;

    //Checking that 2 arguments are passed
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
        exit(1);
    }
    // Load image from file
    read_bitmap(argv[1], input_image);

    convert_to_binary(input_image, binary_image);

    memcpy(eroded_image, binary_image, sizeof(binary_image));
    int i = 0;

    // Perform the erosion 10 times
    while (1) {

        ++i;
        //char str[32];

        //strcpy(str,"../eroded_images/eroded_image ");

        //char numStr[23];

        //snprintf(numStr,sizeof(numStr),"%d",i);
        //strcat(str,numStr);

        //strcat(str,".bmp");

        binary_erode(eroded_image, current_image, &is_eroded);
        cell_check(eroded_image, current_image, &cells);


        //Uncomment to enable debugging of erosion images
        //gray_to_rgb(eroded_image, output_image);
        //write_bitmap(output_image, str);

        // Copy the current_image image back into eroded_image for the next round
        memcpy(eroded_image, current_image, sizeof(current_image));

        if (is_eroded == 0) {
            break;
        }

    }


    printf("The numbers of cells found is: %d\n", cells);
// After you've found all the cells and before you write the final image
    add_squares(input_image, coordinates);

// Write image to file
    write_bitmap(input_image, argv[2]);
    end = clock();
    cpu_time_used = end - start;
    printf("Total time: %f ms\n", cpu_time_used * 1000.0 /
                                  CLOCKS_PER_SEC);

    printf("Done!\n");
    return 0;
}

