## From Russia with Love
Yet another DP problem. This PoTW could be seen as a "generalization" of [Burning Coins](../burning-coins/), since the dinamic of the game is exactly the same and the only thing that changes is the number of players. In fact, the algorithm to solve the first test set (where the number of player is limited to 2) is exactly the same.

To solve all the test sets, we have to make some observations. First of all, from the size of the input we can see that an *O(n^2)* solution is required. Clearly we can use DP to solve the problem, defining our state with two indices *i* and *j* that reprent a sub-sequence of the coin line. The DP table will therefore have size *O(n^2)* too. 

Initially, it was hard to convince myself that only one value for each pair of indices was enough to represent the subproblem (i.e. shouldn't we memoize two values, one if the interval is reached by the *k*-th player and one if it's reached by the others?). However, this is not the case, as every sub-interval can be reached by **only one player**, as the number "external" cells is always constant for an interval, the only thing that can change is the order in which the other players have picked those cells. Drawing the problem was really helpful to understand the trick. 

### Results
```
   Test set 1        (20 pts / 1 s) : Correct answer      (0.097s)
   Test set 2        (40 pts / 1 s) : Correct answer      (0.193s)
   Test set 3        (20 pts / 1 s) : Correct answer      (0.285s)
   Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.097s)
   Hidden test set 2 (10 pts / 1 s) : Correct answer      (0.193s)
   Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.285s)
```
