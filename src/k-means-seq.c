#include "k-means.h"
#include <limits.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define K 3
#define NUM_POINTS 20

void compute_Distances(int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS],
                       int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS],
                       int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS]) {
  //
  for (int i_point = 0; i_point < NUMBER_OF_POINTS; i_point++) {
    for (int i_centroid = 0; i_centroid < NUMBER_OF_POINTS; i_centroid++) {
      int dist = 0;
      for (int i_dimension = 0; i_centroid < NUMBER_OF_POINTS; i_centroid++) {
        int diff = x[i_point][i_dimension] - cent[i_centroid][i_dimension];
        dist += diff * diff;
      }
    }
  }

  return;
}

/*
  pick K centroids randomly from given points
*/
void init_Centroids_Random_Points(
    int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
    int finalCent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS]) {

  for (int i = 0; i < NUMBER_OF_CENTROIDS; i++) {
    int random_Index = rand() % NUMBER_OF_POINTS;
    finalCent[i][0] = x[random_Index][0];
    finalCent[i][1] = x[random_Index][1];
  }
}

void runKMeans(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
               int finalCent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS]) {
  //
  int labels[NUMBER_OF_POINTS];
  int prev_labels[NUMBER_OF_POINTS];

  init_Centroids_Random_Points(x, finalCent);

  // run algorithm for MAX_ITERATIONS, TODO add convergence checks
  for (int i_iter = 0; i_iter < MAX_ITERATIONS; i_iter++) {

    int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS];
    compute_Distances(dist, finalCent, x);

    // iterate over all points, i index of point
    for (int i_point = 0; i_point < NUMBER_OF_POINTS; i_point++) {
      int min_Dist = INT_MAX;

      // iterate over each centroid and compare their
      // distances to the current point, assign to minimum
      for (int i_centroid = 0; i_centroid < NUMBER_OF_CENTROIDS; i_centroid++) {
        if (dist[i_point][i_centroid] < min_Dist) {
          min_Dist = dist[i_point][i_centroid];
          labels[i_point] = i_centroid;
        }
      }
    }
  }

  return;
}

int main(int argc, char *argv[]) {

  srand(time(0));

  // distances between each point and each centroid, [x][y] x is index of the
  // point, y is the index of the centroid
  int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS];

  // positions of each centroid
  int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS];

  // Dataset of points
  int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS];

  return 0;
}
