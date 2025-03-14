

#ifndef KMEANS_H
#define KMEANS_H

#include <omp.h>
#include <stdio.h>

#define NUMBER_OF_POINTS 200
#define NUMBER_OF_DIMENSIONS 2
#define NUMBER_OF_CENTROIDS 3
#define MAX_ITERATIONS 100

// compute squared distance between each point and eahc centroid for each
// centroid using euclidean distance
void compute_Distances(int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS],
                       int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS],
                       int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS]);

void run_KMeans(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
               int finalCent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS]);

void randomize_Points(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
                      int min_value, int max_value);

#endif
