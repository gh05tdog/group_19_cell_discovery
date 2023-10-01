#ifndef ERODE_H
#define ERODE_H

#include "cbmp.h"
#include <stdio.h>
#include "global_vars.h"

void binary_erode(unsigned char binary[BMP_WIDTH][BMP_HEIGHT], int *did_erode);

#endif // ERODE_H
