## The Great Game

In this problem, we are presented The Great Game, a 2-player game where the two players compete against each others. From the input size, we can see that an O(n) solution is required to pass all the test sets. The only way to achieve a linear complexity is, in this case, using DP. 

Observe that finding the winner of the game is the same as finding the nearest meeple to the target position, where the distance is computed with a min-max approach (for every turn, the meeple will be moved both by the player [**min**inimize the distance from the target] and by the opponent [**max**imize the distance from the target]. We can observe that the min-max distances of each position are unique and indipendent from the color of the meeple that will step by. We can therefore compute them only once for all the meeples.

In this case, the state of our DP equals to "the shortest path to the target from the current position, given the player type [min/max]". Each state depends on the followings, and our DP table will have size O(2n), because for each cell we need to store both the min-player and max-player distances to the target.

The winning player will be the one with the lower distance to the target cell. In case of a tie, Sherlock will win if the distance is odd, Moriarty if the distance is even (due to the fact that they're not playing in the exact same order, and the meeple will move in the order RBBR).

### Results
```
   Test set 1 (25 pts / 3.500 s) : Correct answer      (0.0s)
   Test set 2 (25 pts / 3.500 s) : Correct answer      (0.002s)
   Test set 3 (25 pts / 3.500 s) : Correct answer      (0.05s)
   Test set 4 (25 pts / 3.500 s) : Correct answer      (2.986s)
```
