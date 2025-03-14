

/*
  Plots the points and centroids after k-means
  works for only 2 dimensions
*/

#include "plot-k-means.h"

void write_to_file(int points[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
                   int centroids[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS],
                   const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  fprintf(file, "# Points\n");
  for (int i = 0; i < NUMBER_OF_POINTS; i++) {
    fprintf(file, "%d %d\n", points[i][0], points[i][1]);
  }
  fprintf(file, "\n\n");

  fprintf(file, "# Centroids\n");
  for (int i = 0; i < NUMBER_OF_CENTROIDS; i++) {
    fprintf(file, "%d %d\n", centroids[i][0], centroids[i][1]);
  }

  fclose(file);
}

void plot_with_gnuplot(const char *filename) {
  FILE *gnuplot = popen("gnuplot -persistent", "w");
  if (gnuplot == NULL) {
    perror("Error opening GNUplot");
    exit(EXIT_FAILURE);
  }

  // GNUplot commands
  fprintf(gnuplot, "set title 'K-Means Clustering'\n");
  fprintf(gnuplot, "set xlabel 'X-axis'\n");
  fprintf(gnuplot, "set ylabel 'Y-axis'\n");
  fprintf(gnuplot, "set grid\n");

  fprintf(gnuplot, "set key outside\n");
  fprintf(gnuplot,
          "plot '%s' index 0 with points pointtype 7 title 'Points', \\\n",
          filename);
  fprintf(gnuplot, "'%s' index 1 with points pointtype 5 title 'Centroids'\n",
          filename);

  pclose(gnuplot);
}
