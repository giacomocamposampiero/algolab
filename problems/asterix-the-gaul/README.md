## Asterix the Gaul
In this problem, we are required to minimize the number of potions that allows Asterix to reach Panoramix in time, if possible. Unfortunately, there are no ways to write down a polynomial solution for this problem, and we will have to go for an exponential time solution that, given the size of the input, will still achieve a good score. For the last test set, the use of 'split and list' technique is required, but it wasn't implenented in this solution.

A first approach to the problem could be to look for a polynomial solution using DP. Unfortunately, the only way to store informations about subproblems would be having a state defined by the time left to reach Panoramix, and this is clearly not feasible given the size of the time (2^50). Therefore, we are forced to use brute force, and try all the possible combinations of moves that could reach panoramix. 

The first trick we could implement would be sorting the moves on the time they require and then vising the array in that order in the recursion. This allows us to stop the visit of all the possible moves after that, as they are only going to be higher in time (and therefore not suitable for the given constraint). With a simple algorithm that does this, we would get the first 40 points.

In order to achieve the third set, we have to observe that the number of available potions is now really large (10^5) and we can no longer iterate over it linearly. This is doable however, as the list of possible amounts of potion is ordered (trivially) and we can use binary search on it. This allows logaritmic searchs in the range, and therefore our solution is good enough to pass also this test set.

For the last test set, the implementation of split and list is required, as the exponent of the exponential part of the algorithm grows from 2^20 (borderline, but feasible) to 2^30 (definitely not achievable in the given time). By implementing split and list, the complexity would decrease to *O(n\*2^(n/2))*, again something reasonable. 

**UPDATE**: split and list version achieving full score.

### Results
```
   Test set 1 (20 pts / 4 s) : Correct answer      (0.003s)
   Test set 2 (20 pts / 4 s) : Correct answer      (0.01s)
   Test set 3 (20 pts / 4 s) : Correct answer      (0.439s)
   Test set 4 (40 pts / 4 s) : Correct answer      (1.577s)
```
