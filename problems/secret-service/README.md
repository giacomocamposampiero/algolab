## On Her Majesty's Secret Service
For this problem, there's not a simple an straight-forward solution. Instead, we must combine different techniques to achieve full points. The best way to approach the problem is solving it sub-task by sub-task, as the solution are quite incremental. The first test set is rather easy, can be tacled with different approaches (e.g. Dijkstra, flow with costs) and only requires to find the shortest path between the agent and one of the shelters.

From the second test set, things start getting more complicated. In fact, having multiple agents requires to find an optimal assignment to all of them at the same time, and a greedy approach (where we assign every agent to the closest shelter) simply won't work. However, we can observe that there are only two valid values of path's length. This should suggest us that a binary search is needed (we can find the same strategy also in other problems, e.g. [India](../india/)). But on what we
should do binary search? The answer it's on the maximum path's length between an agent and a shelter! If we consider only path which have at most length `l`, we can then use maximum matching to find out if there's a valid assignment between agents and shelters. Therefore, with binary search we will be able to find the minimum value of the maximum length s.t. every agent can reach a shelter.

For the last 20 points a further feature is added to the problem: now shelters have a capacity and can potentially host many agents. This means that we should now take in account the possibility that agents might queue to access a particularly "convenient" shelter. To solve this problem, it's sufficient to "duplicate" (as in our case the capacity limited to at most 2) every shelter and considering it with a doubled entry time cost. 

### Results
```
   Test set 1 (25 pts / 5 s) : Correct answer      (0.024s)
   Test set 2 (25 pts / 5 s) : Correct answer      (0.027s)
   Test set 3 (15 pts / 5 s) : Correct answer      (0.048s)
   Test set 4 (15 pts / 5 s) : Correct answer      (0.153s)
   Test set 5 (20 pts / 5 s) : Correct answer      (0.224s)
```
