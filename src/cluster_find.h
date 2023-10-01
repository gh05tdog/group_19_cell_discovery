//
// Created by Marcus on 01/10/2023.
//

#ifndef GROUP_19_CELL_DISCOVERY_CLUSTER_FIND_H
#define GROUP_19_CELL_DISCOVERY_CLUSTER_FIND_H

#include "cbmp.h"


void color_clusters_green(unsigned char cluster_image[BMP_WIDTH][BMP_HEIGHT][3]);
void find_cell_clusters(unsigned char black_white_image[BMP_WIDTH][BMP_HEIGHT]);
void find_centroid();
void color_centroid_blue(unsigned char output_image[BMP_WIDTH][BMP_HEIGHT][3]);
void find_circumference_of_clumps(unsigned char circumference_image[BMP_WIDTH][BMP_HEIGHT]);
void color_circumference_red(unsigned char circumference_red[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS]);

#endif //GROUP_19_CELL_DISCOVERY_CLUSTER_FIND_H
