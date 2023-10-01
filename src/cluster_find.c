#include <stdio.h>
#include "cbmp.h"
#include "global_vars.h"
#include <stdbool.h>
#include <malloc.h>
#include <math.h>

#define MAX_QUEUE_SIZE 10000

typedef struct {
    int front, rear, size;
    unsigned capacity;
    Coordinate array[MAX_QUEUE_SIZE];
} Queue;

bool isEmpty(Queue* queue) {
    return (queue->size == 0);
}
bool isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}
bool enqueue(Queue* queue, Coordinate item) {
    if (isFull(queue)) return false;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    return true;
}
Coordinate dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        Coordinate invalidItem = {-1, -1}; // invalid coordinate
        return invalidItem;
    }
    Coordinate item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to create a queue with the given capacity
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    return queue;
}

void color_clusters_green(unsigned char cluster_image[BMP_WIDTH][BMP_HEIGHT][3]) {
    for (int i = 0; i < clusterCount; i++) {
        for (int j = 0; j < clusters[i].count; j++) {
            int x = clusters[i].points[j].x;
            int y = clusters[i].points[j].y;

            cluster_image[x][y][0] = 0;    // Red channel
            cluster_image[x][y][1] = 255;  // Green channel
            cluster_image[x][y][2] = 0;    // Blue channel
        }
    }
}

void find_cell_clusters(unsigned char black_white_image[BMP_WIDTH][BMP_HEIGHT])
{
    // Step 1: Initialize
    Queue* q = createQueue(MAX_QUEUE_SIZE);
    Coordinate Area[10000];
    int count = 0;
    unsigned char is_visited[BMP_WIDTH][BMP_HEIGHT] = {{0}};

    // Step 3: Main Loop
    for (int x = 0; x < BMP_WIDTH; x++)
    {
        for (int y = 0; y < BMP_HEIGHT; y++)
        {
            if (black_white_image[x][y] == 255 && is_visited[x][y] == 0)
            {
                // Step 2: BFS Function
                Coordinate coord = {x,y};
                enqueue(q,coord);
                while (!isEmpty(q))
                {
                    Coordinate point = dequeue(q);
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        for (int dy = -1; dy <= 1; dy++)
                        {
                            int currentX = point.x + dx;
                            int currentY = point.y + dy;
                            if (currentX < BMP_WIDTH && currentX >= 0 && currentY < BMP_HEIGHT && currentY >= 0)
                            {
                                if (black_white_image[currentX][currentY] == 255 && is_visited[currentX][currentY] == 0)
                                {
                                    Coordinate white_pixel = {currentX, currentY};
                                    Area[count++] = white_pixel;
                                    enqueue(q, white_pixel);
                                    is_visited[currentX][currentY] = 1;
                                }
                            }
                        }
                    }
                }
                // Step 4: Return Clusters
                if (count >= 499)
                {
                    for (int pixel = 0; pixel < count; pixel++)
                    {
                        clusters[clusterCount].points[pixel] = Area[pixel];
                    }
                    clusters[clusterCount++].count = count;
                    printf("Cluster %d has %d pixels\n", clusterCount, count);
                }
                count = 0;
            }
        }
    }
}

void find_centroid() {
    for (int i = 0; i < clusterCount; i++) {
        int sumX = 0;
        int sumY = 0;
        int count = clusters[i].count;
        for (int j = 0; j < count; j++) {
            sumX += clusters[i].points[j].x;
            sumY += clusters[i].points[j].y;
        }
        centroids[i].x = sumX / count;
        centroids[i].y = sumY / count;
    }
}

void color_centroid_blue(unsigned char centroid_image[BMP_WIDTH][BMP_HEIGHT][3]){
    //place a 6x6 blue square around the centroid

    for(int i = 0; i < clusterCount; i++){
        int x = centroids[i].x;
        int y = centroids[i].y;

        for(int dx = -3; dx <= 3; dx++){
            for(int dy = -3; dy <= 3; dy++){
                int newX = x + dx;
                int newY = y + dy;

                if(newX >= 0 && newX < BMP_WIDTH && newY >= 0 && newY < BMP_HEIGHT){
                    centroid_image[newX][newY][0] = 0;    // Red channel
                    centroid_image[newX][newY][1] = 0;  // Green channel
                    centroid_image[newX][newY][2] = 255;    // Blue channel
                }
            }
        }
    }
}

int getClusterCircumference(Cluster cluster, unsigned char black_and_white_image[BMP_WIDTH][BMP_HEIGHT], Circumference *circ) {
    int circumference = 0;

    for (int j = 0; j < cluster.count; j++) {
        int x = cluster.points[j].x;
        int y = cluster.points[j].y;

        // Check the 8 neighboring pixels
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                // Skip the center pixel
                if (dx == 0 && dy == 0) continue;

                int newX = x + dx;
                int newY = y + dy;

                // Check boundaries
                if (newX >= 0 && newX < BMP_WIDTH && newY >= 0 && newY < BMP_HEIGHT) {
                    if (black_and_white_image[newX][newY] == 0) { // 0 represents black
                        circ->points[circumference].x = x;
                        circ->points[circumference].y = y;
                        circumference++;
                        break; // Move to the next pixel in the cluster
                    }
                }
            }
        }
    }
    circ->count = circumference; // Store the total count of circs pixels
    return circumference;
}

void find_circumference_of_clumps(unsigned char black_and_white_image[BMP_WIDTH][BMP_HEIGHT]) {
     // Array to store circumferences for all clusters
    for (int i = 0; i < clusterCount; i++) {
        int circumference = getClusterCircumference(clusters[i], black_and_white_image, &circs[i]);
        printf("Cluster %d has circumference of %d pixels\n", i + 1, circumference);
    }
}

void color_circumference_red(unsigned char circumference_red[BMP_WIDTH][BMP_HEIGHT][BMP_CHANNELS]){
    //color the circs red
    for (int i = 0; i < clusterCount; i++) {
        for (int j = 0; j < circs[i].count; j++) {
            int x = circs[i].points[j].x;
            int y = circs[i].points[j].y;

            circumference_red[x][y][0] = 255;    // Red channel
            circumference_red[x][y][1] = 0;  // Green channel
            circumference_red[x][y][2] = 0;    // Blue channel
        }
    }
}










