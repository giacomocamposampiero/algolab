## Defensive Line
In this problem we are required to find the maximum sum of lengths of non-overlapping sub-intervals of a sequence. The values of each sub-sequence must sum up to exactly *k*.
From the given maximum size of the input, we can note that the solution must be at most *O(n \* m)*.  

The first thing to do in this case is to find the sub-intervals (defined by the bounding indices **a_i** and **b_i**) in the sequence which satisfy the constraint 
![equation](https://latex.codecogs.com/svg.image?\sum_{j=a_i}^{b_i}v_j)

This can be done in linear time using a sliding window approach. For simplicity, the intervals are store in a new vector, which in position `i` contains the length of the interval (if there is an interval starting at `i`) or -1 in case there are no intervals starting in that position.

Now that we have every candidate interval, we have to choose the best non-overlapping *m* within them such that the sum of their lengths is maximized. The only way (that I found) to deal with this problem is to actually use DP.
The DP state is defined as "the maximum sum of lenghts of *m* intervals from the index *i*". Note that we will need a 2-dimensional DP table, where the first dimension is for the starting point of the interval, whereas the second dimension if for the number *m* of intervals that we're allowed to pick.  

### Results
```
   Test set 1 (20 pts / 0.500 s) : Correct answer      (0.0s)
   Test set 2 (20 pts / 0.500 s) : Correct answer      (0.012s)
   Test set 3 (20 pts / 0.500 s) : Correct answer      (0.138s)
   Test set 4 (20 pts / 2.000 s) : Correct answer      (0.018s)
   Test set 5 (20 pts / 0.500 s) : Correct answer      (0.165s)
```
