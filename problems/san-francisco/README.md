## San Francisco
In this problem, we are asked to find the minimum number of moves that are required to yield a given score. The formulation of the problem is really [intentionally] ambiguos, and the temptation of modeling it as a graph problem (with flows or other techniques) might be high. However, we would just end up in a rabbit hole spending our entire 2 hours trying different approaches that will inevitably fail. In fact, the only solution to solve this problem is to try all the possible paths in
the graph. However, this might only work for the first test set, what about the others?

Well, the answer is obviously DP. In this case, we can define as our DP state the maximum score achievable from a starting point `start` using exactly `m` moves. This will allow us to shrink the complexity of our algorithm from exponential to *O(n\*m)*, where `n` is the number of nodes in the graph.  
Exploring the right values of `m` might be again too complex (even if right now an iterative approach still passes all the tests without problems), but we can reduce even this complexity using binary search instead.

Finally, to implement the "free action" feature, we just have to check in the recursive method whether the position has outgoing canals or not. In the latter case, the position is actually *Weayaya* and we can start again from the first node (if we have remaining moves) just recalling the recursive method on node 0.

### Results
```
   Test set 1        (25 pts / 3 s) : Correct answer      (0.0s)
   Test set 2        (25 pts / 3 s) : Correct answer      (0.019s)
   Test set 3        (30 pts / 3 s) : Correct answer      (1.374s)
   Hidden test set 1 (05 pts / 3 s) : Correct answer      (0.0s)
   Hidden test set 2 (05 pts / 3 s) : Correct answer      (0.018s)
   Hidden test set 3 (10 pts / 3 s) : Correct answer      (1.383s)
```
