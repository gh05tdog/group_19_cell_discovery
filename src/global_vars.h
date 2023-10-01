// global_vars.h
#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H
#define MAX_CLUSTERS 5000
#define MAX_POINTS_PER_CLUSTER 5000
#define MAX_POINTS 1000

typedef struct {
   short int x;
    short int y;
} Coordinate;


typedef struct {
    Coordinate points[5000]; // Assuming a maximum number of pixels for the circumference
    int count; // Number of pixels in the circumference
} Circumference;

typedef struct {
    Coordinate points[5000]; // Assuming a max of 10000 points per cluster
    int count;
    double slopeDifferences[5000];
} Cluster;

typedef struct {
    Coordinate points[5000]; // Assuming a max of 10000 points per cluster
    int x;
    int y;
} Centroid;

extern Coordinate coordinates[5000]; // Assuming a maximum of 1000 cells
extern int coord_index;


extern int clusterCount;

extern Cluster clusters[MAX_CLUSTERS];

extern Circumference circs[MAX_CLUSTERS];
extern Centroid centroids[MAX_CLUSTERS];


#endif // GLOBAL_VARS_H
