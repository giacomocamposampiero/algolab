## Fighting Pits of Meereen
This problem was particularly hard and required both memory and time optimization (as I approached it, but there are other solutions available online which use bit operations and other stuff and are even ten time faster).

In this solution, I used a DP approach to tackle the problem. The problem was to find the best maximum scoring binary tree (where each assignment of a fighter to one of the two gates, north or south). A naive solution would have been exponential in the number of players, clearly not good enough to pass all the tests. DP memoization allows us to avoid the computation of already-visited states (and all the corresponding sub-trees) and this gives us a great improvement in the performances.

The DP state is defined by the current fighter (it's position in the vector), the imbalance between the fighters entered in the two gates so far and the two queues (north and south). However, to make it work, we need to make some observations. 

First of all, we need to note that the imbalance between the fighters entering the two gates cannot be greater than 11. In fact, the problem states that **no round** can have a negative score, and if the imbalance is greater than 11 the penalizing factor will be > 2^12 = 4096, which is way higher than then the maximum excitement bonus we can achieve (3000).This allows us to compute and memoize only the states whose imbalance is in the interval [-11, +11]. Moreover, we can observe that we don't need to store the 3 past fighters for each gate, but only 2 are needed in each round (the third is
the new fighter). This reduces the dimension of the *north* and *south* axis from a maximum of *k^m* to a maximum of *k^(m-1)*, which in our case equals in the worst scenario to 4^2=16. All this observations allows us to cut down the maximum number of steps to roughly 2\*10^7, which is okay for the time limits given.

**Take-home messages**
- DP table should not exceed ~10^8, otherwise the code won't run in CodeExpert
- Careful with the specifics of the problem, in this case the few observations above were necessary to achieve the points for test set 4
- Sample input is very helpful to understand what is going on, don't overlook it!

### Results
```
   Test set 1        (20 pts / 2 s) : Correct answer      (0.051s)
   Test set 2        (20 pts / 2 s) : Correct answer      (0.129s)
   Test set 3        (20 pts / 2 s) : Correct answer      (0.125s)
   Test set 4        (20 pts / 2 s) : Correct answer      (0.537s)
   Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.05s)
   Hidden test set 2 (05 pts / 2 s) : Correct answer      (0.119s)
   Hidden test set 3 (05 pts / 2 s) : Correct answer      (0.126s)
   Hidden test set 4 (05 pts / 2 s) : Correct answer      (0.537s)
```
