#ifndef ERODE_H
#define ERODE_H

#include "cbmp.h"

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGTH], unsigned char eroded[BMP_WIDTH][BMP_HEIGTH], int *is_eroded);
#endif // ERODE_H
