#include "k-means.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int read_From_CSV(int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS]) {
  const char *filename = "generated_points.csv";

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
  srand(time(0));

  // Dataset of points
  int x[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS];

  double runtimes[16];

  // Read data from CSV
  if (read_From_CSV(x) != 0) {
    fprintf(stderr, "Failed to read data from CSV.\n");
    return 1;
  }

  // Test for different numbers of threads (1 to 16)
  printf("Threads\tTime (seconds)\n");
  for (int num_threads = 1; num_threads <= 16; num_threads++) {
    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Positions of each centroid
    int cent[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS];

    // Start the clock
    double start_time = omp_get_wtime();

    // Run K-means
    run_KMeans_parallel(x, cent);

    // Stop the clock
    double end_time = omp_get_wtime();

    // Calculate the time taken

    double time_taken = (end_time - start_time);

    runtimes[num_threads] = time_taken;
  }

  for (int num_threads = 1; num_threads <= 16; num_threads++) {

    printf("%d\t%f\n", num_threads, runtimes[num_threads]);
  }

  return 0;
}
