

# K-means sequential means algorithm

- [[#Algorithm used]]
- [[#Code]]
- [[#Sample run]]
### Algorithm used

1. Initialize **points** Randomly between 0 and 50
2. Initialize K **Centroids** by choosing K random **points**
3. Assign each **point** to its closest **Centroid**
4. Update **Centroid** location for each **cluster**, set as the mean of each **cluster**
5. Repeat until **convergence** or reached **MAX_ITERATIONS**

**Convergence** in our case is 2 iterations where the **Centroid** locations don't change

### Code
#### Script index:
- [[#k-means-seq.c]]
- [[#plot-k-means.c]]
- [[#unit-test-sequential.c]]

##### k-means-seq.c

The main K-means algorithm

**update_Centroids:**
Update **centroids**, set each **new centroid** as the mean of its **cluster**

![[Pasted image 20250314180539.png]]

**compute_Distances**
Compute the distance between each point and each centroid using **euclidean distance**

![[Pasted image 20250314180942.png]]


##### plot-k-means.c

Using **gnuplot** C library to first write the **point** and **centroid** data to a text file and then plots it. Currently **not Generic**, only works for 2 dimensions

##### unit-test-sequential.c

Main function that runs the k-means algorithm on randomly generated points, then outputs and plots the result. 

### Sample run

![[Pasted image 20250314181302.png]]
\- K-means ran with 200 points, plotted with `gnuplot`

Due to the even distribution of randomly generated points the centroids tend to cluster in the center.
Running with only 20 points, We can see the centroids spread out further.

![[Pasted image 20250314181452.png]]
\- K-means ran with 20 points

**Console output:**
![[Pasted image 20250314181608.png]]

```
$ gcc src/unit-test-sequential.c src/k-means-seq.c src/plot-k-means.c -o kmeans_program.o && ./kmeans_program.o
init centroid:31 3
init centroid:31 3
init centroid:16 0
Epoch: 1
Cluster 1: (32, 1) (29, 13) (39, 32) (49, 29) (31, 20) (30, 23) (50, 20) (16, 20) (33, 24) (47, 32) (32, 9) (16, 46) (16, 0)
Cluster 2: (33, 22) (16, 4) (48, 6) (31, 3)
Cluster 3: (10, 23) (6, 15) (24, 35)
Epoch: 2
Cluster 1: (32, 1) (29, 13) (39, 32) (49, 29) (31, 20) (30, 23) (50, 20) (16, 20) (33, 24) (47, 32) (32, 9) (16, 46) (16, 0)
Cluster 2: (33, 22) (16, 4) (48, 6) (31, 3)
Cluster 3: (10, 23) (6, 15) (24, 35)
solution:
Centroid 0: (32, 20)
Centroid 1: (32, 8)
Centroid 2: (13, 24)
```
