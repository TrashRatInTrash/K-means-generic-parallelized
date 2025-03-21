```
  A generic implementation of K-means
  parallelized using openmp
```

# K-means part 2: parallelized with open MP


---

### Algorithm used

1. Initialize **points** Randomly between 0 and 50
2. Initialize K **Centroids** by choosing K random **points**
3. Assign each **point** to its closest **Centroid** using euclidean distance
4. Update **Centroid** location for each **cluster**, set as the mean of each **cluster**
5. Repeat until **convergence** or reached **MAX_ITERATIONS**

**Convergence** in our case is 2 iterations where the **Centroid** locations don't change

### Parallel algorithm

The most time consuming part are the for loops in `compute_Distances` and `update_Centroids`. 

![Pasted image 20250321211123](https://github.com/user-attachments/assets/f8e43ea7-39a0-40ff-8b43-62f08a03afd4)


# Assessing Runs:

**Notes:**
in order to prevent "bad runs" (or runs with un-optimal initial centroid selection) influencing the time taken. We manually select the first 3 points as initial centroids.

The algorithm solves this in 15 epochs consistently.
The algorithm always finds the same final centroids due to the consistent use of initial **seed** centroids

**Sample final output:**
```
Epoch: 15
Centroid 0: 366 -529
Centroid 1: 318 546
Centroid 2: -615 -51
```


---

***Interlude:***

*Calculating time is done using the omp function `omp_get_wtime()`, as this provides accurate wall clock time in a simple manner. As opposed to `clock_t` which provides clock time, which is misleading.*

*usage:*

```
    double start_time = omp_get_wtime();
    
    run_KMeans_parallel(x, cent);

    double end_time = omp_get_wtime();

    double time_taken = (end_time - start_time);

```

*The final `double time_taken` is in seconds*

---

Using `omp_set_num_threads(int threads)` to control how many threads are utilized we can test the effectiveness of parallelism. We can see expected results:

![Pasted image 20250321205445](https://github.com/user-attachments/assets/b1e5758f-da21-46cc-bd7d-1a7bafd1b879)

- As number of threads used **increases** runtime **decreases**
- Noticeable diminishing returns at higher thread counts due to the cost of overhead when compared with the small data set

