## Return of the Jedi
In this problem it should be easy to understand that the Princess Leia method corresponds to simply build the minimum spanning tree between the planets network. We're asked to find the "second best MST", which must be different from the true MST of the network.

The approach presented here is quite simple. We first compute the MST using boost Union Find structure. This has a cost of *O(m\*logm)* (due to the ordering of edges), that given the input size should be fine. Then, observe that the we're only dealing with at most `n-1` edges at this point. Indeed, it's possible to just re-construct the MST `n-1` times (total quadratic complexity, since the edges are already ordered), each time not selecting one of the true MST edges. Finally, after computing
the cost of each one of these alternative MST, we just need to pick the less expensive, which is exactly what we were looking for.

### Results
```
   Test set 1 (40 pts / 2 s) : Correct answer      (0.009s)
   Test set 2 (40 pts / 2 s) : Correct answer      (0.658s)
   Test set 3 (20 pts / 2 s) : Correct answer      (1.115s)
```
