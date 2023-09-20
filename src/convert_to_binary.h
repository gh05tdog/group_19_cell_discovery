//
// Created by olive on 20-09-2023.
//

#ifndef GROUP_19_CELL_DISCOVERY_CONVERT_TO_BINARY_H
#define GROUP_19_CELL_DISCOVERY_CONVERT_TO_BINARY_H
#include "cbmp.h"

void convert_to_binary(unsigned char rgb_image[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS],
                       unsigned char binary_image[BMP_WIDTH][BMP_HEIGHT]);

#endif //GROUP_19_CELL_DISCOVERY_CONVERT_TO_BINARY_H