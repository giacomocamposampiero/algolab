## Burning Coins
In this problem we are required to find the maximum score achievable by a player indipendently from the moves of the adversary. Each player can pick a coin from the head or the tail of the stack (only two possible positions) and the two players can only pick one coin per round.

From the size of the input, we can observe that a *O(n^2)* solution is required to pass the last test set. The complexity of a naive algorithm which computes the outcome for every possible game is clearly exponential in the size of the coin stack. However, we can observe that for each [i,j] interval in the stack there is only an optimum solution and this solution can be computed comining the solutions of smaller sub-intervals. We are in the classical setting of a DP problem!

The two bounding indices i and j are enough to define a DP state. Therefore, our memoization table will be of size *O(n^2)*. The termination condition is (i>j), as i must be lower or equal (whene there is only one coin left for the player). Since the recursive function will be called at most n^2 times (one for each possible interval in the coin stack) the complexity of the algorithm is indeed *O(n^2)*.  

### Results
```
   Test set 1 (30 pts / 2 s) : Correct answer      (0.0s)
   Test set 2 (40 pts / 2 s) : Correct answer      (0.016s)
   Test set 3 (30 pts / 2 s) : Correct answer      (0.5s)
```
