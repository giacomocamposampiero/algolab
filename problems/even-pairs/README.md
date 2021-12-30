## Even pairs
This problem could be tackled using a naive n^3 solution, by summing for all pairs i ≤ j all the values xi +···+xj. However, this solution is *O(n^3)* and is fast enough to pass only the first test set.

A possible improvement to this solution is to pre-compute the partial sum in the vector of integers. This allows us to speed up our algorithm to *O(n^2)*, as we no longer need to compute the sum for every pair i and j. 

Still, we can improve improve our solution even more, by observing that the sum over an interval can be even iif the difference between the partial sums in position (i-1) and j are both odd or both even. Therefore, it's possible to find out the number of even sub-intervals in a linear time, by counting the number of even and odd partial sums and then deriving the result as

![](https://latex.codecogs.com/svg.image?even&space;&plus;&space;\frac{1}{2}\binom{even}{2}&space;&plus;&space;\frac{1}{2}\binom{odd}{2})

Note that we take half of *nC2* as the pairs are ordered (i≤j).

### Results 
```
   Test set 1 (40 pts / 0.400 s) : Correct answer      (0.0s)
   Test set 2 (40 pts / 0.400 s) : Correct answer      (0.004s)
   Test set 3 (20 pts / 0.400 s) : Correct answer      (0.027s)
```
