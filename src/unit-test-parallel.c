
/*
  Test of K-means-sequential algorithm and gnuplotting
*/

#include "k-means.h"
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int read_From_CSV(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS]) {

  const char *filename = "generated_points.csv";
  // const char *filename = "points.csv";

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("error opening file");
    return -1;
  }

  int i = 0;
  while (fscanf(file, "%d,%d", &x[i][0], &x[i][1]) == 2) {
    i++;
    if (i >= NUMBER_OF_POINTS) {
      break; // Avoid exceeding the array bounds
    }
  }

  fclose(file);

  return 0;
}

int main(int argc, char *argv[]) {

  omp_set_num_threads(4);

  srand(time(0));

  // distances between each point and each centroid, [x][y] x is index of the
  // point, y is the index of the centroid
  int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS];

  // positions of each centroid
  int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS];

  // Dataset of points
  int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS];

  read_From_CSV(x);

  double start_time = omp_get_wtime();

  run_KMeans_parallel(x, cent);

  double end_time = omp_get_wtime();

  double time_taken = (end_time - start_time);
  printf("%f seconds\n", time_taken);

  return 0;
}
