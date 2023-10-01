#include <stdlib.h>
#include <stdio.h>
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
unsigned char eroded_image[BMP_WIDTH][BMP_HEIGHT];



int main(int argc, char **argv) {
    clock_t start, end;
    double cpu_time_used;

    int cells = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file path> <output file path> \n", argv[0]);
        exit(1);
    }

    // Load image from file
    read_bitmap(argv[1], input_image);

    convert_to_binary(input_image, eroded_image);

    //Start the clock
    start = clock();

    int did_erode = 1;

    while (did_erode != 0) {
        binary_erode(eroded_image, &did_erode);
        cell_check(eroded_image, &cells);
    }

    end = clock();

    printf("The numbers of cells found is: %d\n", cells);


    for (int number = 0; number < coord_index; number++) {
        printf("Cell %d: x = %d, y = %d\n", number + 1, coordinates[number].x, coordinates[number].y);
    }
    read_bitmap(argv[1], input_image);
    // Add squares to the original image
    add_squares(input_image, coordinates);
    write_bitmap(input_image, argv[2]);

    // Calculate time elapsed
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Print time elapsed
    printf("Total time: %f ms\n", cpu_time_used * 1000.0);

    printf("Done!\n");

    return 0;
}

