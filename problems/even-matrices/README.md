## Even matrices

This problem can be seen, with some tricks, as a 2-dimensional extension of Even pairs.
In fact, even in this case we have to use a pre-computation to speed up the algorithm (see [integral image](https://en.wikipedia.org/wiki/Summed-area_table) on Wikipedia). This pre-computation allows us to compute the sum over every sub-matrix in *O(1)* given the defining coordinates of the matrix i1,j1,i2,j2. However, since we would have to iterate over every cell of the matrix and for each of them we would have to study every combination over i and j axes, this approach results in an *O(n^4)* algorithm, which is still not enough to get the last 20 points (size of the input is 200 at max, and we have to find a solution which runs in less than 6*10^6 = n^3).

To complete the last test set, we have to observe that the 2-dimensional problem that we're tackling can be "easily" reduced to a simpler 1-dimensional problem. In fact, for every combination of the rows i1 and i2 we can compute another vector which represents the sum of the corresponding elements in the two arrays (or even the subtraction is fine, we just need to find whether the two elements are both odd/even or not). Now, we know how to find the number of even pairs ([see here](../even-pairs)) in *O(n)*. We therefore obtain a *O(n^3)* solution to the problem.  

### Results
```
   Test set 1 (30 pts / 0.600 s) : Correct answer      (0.0s)
   Test set 2 (50 pts / 0.600 s) : Correct answer      (0.001s)
   Test set 3 (20 pts / 0.600 s) : Correct answer      (0.027s)
```
