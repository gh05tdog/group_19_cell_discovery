#ifndef ERODE_H
#define ERODE_H

#include "cbmp.h"

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGHT], unsigned char eroded[BMP_WIDTH][BMP_HEIGHT], int *is_eroded);

#endif // ERODE_H
