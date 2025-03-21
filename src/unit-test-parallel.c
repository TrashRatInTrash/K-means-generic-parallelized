
/*
  Test of K-means-sequential algorithm and gnuplotting
*/

#include "k-means.h"
#include "plot-k-means.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

  srand(time(0));

  // distances between each point and each centroid, [x][y] x is index of the
  // point, y is the index of the centroid
  int dist[NUMBER_OF_POINTS][NUMBER_OF_CENTROIDS];

  // positions of each centroid
  int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS];

  // Dataset of points
  int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS];

  // read points from csv here

  clock_t clock_Time = clock();

  run_KMeans_parallel(x, cent);

  clock_Time = clock() - clock_Time;

  double time_taken = ((double)clock_Time) / CLOCKS_PER_SEC;
  printf("%f seconds\n", time_taken);

  // Write points and centroids to a file
  write_to_file(x, cent, "kmeans_data.txt");

  /*
    Plot using GNUplot, Comment this line to disable gnuplot,
    also remove included header if not installed
  */
  plot_with_gnuplot("kmeans_data.txt");

  // Print final centroids
  printf("solution:\n");
  for (int i = 0; i < NUMBER_OF_CENTROIDS; i++) {
    printf("Centroid %d: (", i);
    for (int d = 0; d < NUMBER_OF_DIMENSIONS; d++) {
      printf("%d", cent[i][d]);
      if (d < NUMBER_OF_DIMENSIONS - 1)
        printf(", ");
    }
    printf(")\n");
  }

  return 0;
}
