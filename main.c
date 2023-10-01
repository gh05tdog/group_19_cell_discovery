#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "cbmp.h"
#include "src/erode.h"
#include "src/cell_check.h"
#include "src/global_vars.h"
#include "src/add_squares.h"
#include "src/convert_to_binary.h"
#include "src/cluster_find.h"

Coordinate coordinates[5000];
int coord_index = 0;

//Declaring the array to store the image (unsigned char = unsigned 8 bit)
unsigned char input_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
unsigned char eroded_image[BMP_WIDTH][BMP_HEIGHT];
unsigned char cluster_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS];
int clusterCount = 0;
Cluster clusters[MAX_CLUSTERS];
Centroid centroids[MAX_CLUSTERS];
Circumference circs[MAX_CLUSTERS];


int main(int argc, char **argv) {
    clock_t start, end;
    double cpu_time_used;

    int cells = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
        exit(1);
    }

    // Load image from file
    read_bitmap(argv[1], input_image);
    convert_to_binary(input_image, eroded_image);

    //Loops through each cell and finds all the white pixels that are connected via BFS and a queue, then if more than 400 pixels are found, it is caller a cluster
    find_cell_clusters(eroded_image);

    //Reads the first argument as bitmap then colors all the pixels found in the clusters green
    read_bitmap(argv[1], cluster_image);
    color_clusters_green(cluster_image);

    //finds the centers for all the clusters and colors them blue
    find_centroid();
    color_centroid_blue(cluster_image);

    //finds the circumference of all the clusters and colors them red
    find_circumference_of_clumps(eroded_image);
    color_circumference_red(cluster_image);
    write_bitmap(cluster_image, "../circumference_image.bmp");

    start = clock();
    int did_erode = 1;

    while (did_erode != 0) {
        binary_erode(eroded_image, &did_erode);
        cell_check(eroded_image, &cells);
    }
    end = clock();

    for (int i = 0; i < coord_index; i++) {
        printf("Cell %d: x = %d, y = %d\n", i + 1, coordinates[i].x, coordinates[i].y);
    }

    printf("The numbers of cells found is: %d\n", cells);


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

