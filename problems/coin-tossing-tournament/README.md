## Coin Tossing Tournament
In this problem we are required to verify if a given scoreboard is possible to obtain, knowing the rounds that have been played so far and the results of a subset of them. The problems resembles a lot the tutorial problem [Soccer Predictions](https://algolab.inf.ethz.ch/doc/tutorials/tut07_bgl_flows.pdf), and in fact the underlying logic is the same. Indeed, every game "distributes" one point and every player "receives" points from the game. This problem can be modeled as a flow, where each
game is connected with the source with a capacity equals to the points it distributes (in our case 1) and each player is connected to a sink with an edge whose capacity is equal to his/her final score.

For the matches whose result is known we can add only one edge from the match node to the winner node. For the matches whose outcome is unknown, we must add one edge for each player involved in the match. Note that the capacity from the source to the match node set to 1 will guarantee that only one of these two nodes will be considered in the final solution. 

Applying max-flow to this network, it will try to maximize the likelihood between the given scoreboard and the outcomes of match. Checking whether the scoreboard is possible to obtain or not is the same as checking if the flow value equals the sum over all scores in the leaderboard. Moreover, we need to check if this value is equal to the number of matches, as we need to distribute all the points of each match. 

### Results
```
   Test set 1 (40 pts / 1 s) : Correct answer      (0.009s)
   Test set 2 (40 pts / 1 s) : Correct answer      (0.104s)
   Test set 3 (20 pts / 1 s) : Correct answer      (0.265s)
```
