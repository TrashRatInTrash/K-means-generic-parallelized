
/*
  A generic sequential K-means implementations
  Works on 1 or more dimensions
*/

#include "k-means.h"
#include "plot-k-means.h"
#include <limits.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define K 3
#define NUM_POINTS 20

/*
  compute squared distance between each point and eahc centroid for each
  centroid using euclidean distance
*/
void compute_Distances(int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS],
                       int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS],
                       int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS]) {
  //
  for (int i_point = 0; i_point < NUMBER_OF_POINTS; i_point++) {
    for (int i_centroid = 0; i_centroid < NUMBER_OF_POINTS; i_centroid++) {
      int dist = 0;
      for (int i_dimension = 0; i_dimension < NUMBER_OF_POINTS; i_dimension++) {
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
    for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {
      finalCent[i][d] = x[random_Index][d];
    }
  }

  for (int i = 0; i < NUMBER_OF_CENTROIDS; i++) {
    printf("init centroid:");
    for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {

      printf("%d ", finalCent[i][d]);
    }
    printf("\n");
  }
}

void list_Cluster_Points(int points[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
                         int labels[NUMBER_OF_POINTS], int number_of_clusters) {
  for (int cluster = 0; cluster < number_of_clusters; cluster++) {
    printf("Cluster %d: ", cluster + 1);

    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
      if (labels[i] == cluster) {
        printf("(");
        for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {
          printf("%d", points[i][d]);
          if (d < NUMBER_OF_DIMENSIONS - 1) {
            printf(", ");
          }
        }
        printf(") ");
      }
    }
    printf("\n");
  }
}

/*
  count the number of points for each cluster,
  then reset centroid for each cluster as the mean
*/
void update_Centroids(
    int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS], int labels[NUMBER_OF_POINTS],
    int finalCent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS]) {

  int count[NUMBER_OF_CENTROIDS] = {0};
  int sum[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS] = {0};

  for (int i_point = 0; i_point < NUMBER_OF_POINTS; i_point++) {
    int cluster = labels[i_point];
    for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {
      sum[cluster][d] += x[i_point][d];
    }
    count[cluster]++;
  }

  for (int i_centroid = 0; i_centroid < NUMBER_OF_CENTROIDS; i_centroid++) {
    for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {
      if (count[i_centroid] > 0) {
        finalCent[i_centroid][d] = sum[i_centroid][d] / count[i_centroid];
      }
    }
  }
}

/*
  check for convergence by comparing new labels with previous labels
  By this definition
  convergence = Same labels in 2 stops in a row
*/
int has_Converged(int labels[NUMBER_OF_POINTS],
                  int prev_labels[NUMBER_OF_POINTS]) {
  for (int i = 0; i < NUMBER_OF_POINTS; i++) {
    if (labels[i] != prev_labels[i]) {
      return 0; // Not converged
    }
  }
  return 1; // Converged
}

void run_KMeans(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
                int finalCent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS]) {
  //
  int labels[NUMBER_OF_POINTS];
  int prev_labels[NUMBER_OF_POINTS];

  init_Centroids_Random_Points(x, finalCent);

  // run algorithm for MAX_ITERATIONS, TODO add convergence checks
  for (int i_iter = 0; i_iter < MAX_ITERATIONS; i_iter++) {
    printf("Epoch: %d \n", i_iter + 1);

    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
      prev_labels[i] = labels[i];
    }

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

    update_Centroids(x, labels, finalCent);
    list_Cluster_Points(x, labels, NUMBER_OF_CENTROIDS);

    // Check for convergence
    if (has_Converged(labels, prev_labels)) {
      break;
    }
  }

  return;
}

void randomize_Points(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
                      int min_value, int max_value) {
  for (int i = 0; i < NUMBER_OF_POINTS; i++) {
    for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {
      x[i][d] = min_value + rand() % (max_value - min_value + 1);
    }
  }
}
