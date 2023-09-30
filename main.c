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
unsigned char eroded_image[BMP_WIDTH][BMP_HEIGHT];
int PEI = 0;



int main(int argc, char **argv) {
    clock_t start, end;
    double cpu_time_used;



    int cells = 0;
    const int MAX_ITERATIONS = 10;
    // Checking that 2 or 3 arguments are passed
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s <input file path> <output file path> [-PEI]\n", argv[0]);
        exit(1);
    }

    // Check if PEI mode is enabled (Print Eroded Images)
    if (argc == 4 && strcmp(argv[3], "-PEI") == 0) {
        printf("PEI mode enabled\n");
        PEI = 1;
    }

    // Load image from file
    read_bitmap(argv[1], input_image);

    convert_to_binary(input_image, eroded_image);

    start = clock();
    int i = 0;
    int did_erode = 1;

    while (did_erode != 0) {
        binary_erode(eroded_image,&did_erode);
        cell_check(eroded_image, &cells);
        i++;

        // Uncomment to enable debugging of erosion images
        if (PEI == 1) {
            char str[32];
            strcpy(str, "../eroded_images/eroded_image ");
            char numStr[23];
            snprintf(numStr, sizeof(numStr), "%d", i);
            strcat(str, numStr);
            strcat(str, ".bmp");
            gray_to_rgb(eroded_image, output_image);
            write_bitmap(output_image, str);
        }
    }
    end = clock();

    printf("The numbers of cells found is: %d\n", cells);



    for(int i = 0; i < coord_index; i++) {
        printf("Cell %d: x = %d, y = %d\n", i+1, coordinates[i].x, coordinates[i].y);
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

