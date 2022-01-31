## Even pairs
In this proble, we are required to find the number of even pairs (i.e. which sums up to an even number) in a given sequence. 

This problem could be tackled using a naive n^3 solution, by summing for all pairs i ≤ j all the values `xi + ··· + xj`. However, this solution would have complexity *O(n^3)*, which is fast enough to pass only the first test set.

A possible improvement to this solution is to pre-compute the partial sum in the vector of integers. This allows us to speed up our algorithm to *O(n^2)*, as we no longer need to compute the sum for every pair i and j. 

Still, we can improve improve our solution even more, by observing that the sum over an interval can be even iif the difference between the partial sums in position (i-1) and j are both odd or both even. Therefore, it's possible to find out the number of even sub-intervals in a linear time, by counting the number of even and odd partial sums and then deriving the result as

![](https://latex.codecogs.com/svg.image?even&space;&plus;&space;\binom{even}{2}&space;&plus;&space;\binom{odd}{2})

### Points
There are three groups of test sets, worth 100 points in total.
1. For the first group of test sets, worth 40 points, you may assume that 1 <= n <= 200.
2. For the second group of test sets, worth 40 points, you may assume that 1 <= n <= 5000. 3. For the third group of test sets, worth 20 points, there are no additional assumptions.

### Results 
```
   Test set 1 (40 pts / 0.400 s) : Correct answer      (0.0s)
   Test set 2 (40 pts / 0.400 s) : Correct answer      (0.004s)
   Test set 3 (20 pts / 0.400 s) : Correct answer      (0.027s)
```
