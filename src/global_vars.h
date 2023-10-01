// global_vars.h
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

typedef struct {
   short int x;
    short int y;
} Coordinate;

extern Coordinate coordinates[1000]; // Assuming a maximum of 1000 cells
extern int coord_index;

#endif // GLOBAL_VARS_H
