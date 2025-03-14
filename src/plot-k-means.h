
#ifndef PLOT_KMEANS_H
#define PLOT_KMEANS_H

#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_POINTS 20
#define NUMBER_OF_DIMENSIONS 2
#define NUMBER_OF_CENTROIDS 3

// Function to write points and centroids to a file
void write_to_file(int points[NUMBER_OF_POINTS][NUMBER_OF_DIMENSIONS],
                   int centroids[NUMBER_OF_CENTROIDS][NUMBER_OF_DIMENSIONS],
                   const char *filename);

// Function to plot points and centroids using GNUplot
void plot_with_gnuplot(const char *filename);

#endif
