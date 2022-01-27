## Hagrid
Since the path from the entrance to each chamber of the underground network is unique, we're clearly dealing with a tree. The problem is to find the best visiting order of the tree, which corresponds (at least for the first 90 points) to visit the cheaper subtrees first. In fact, leaving the most expensive subtree at the end of the visit allows us to save the gold that would have been otherwise consumed during the travel upwards.

Therefore, we need associate to each chamber a cost, that equals to the sum of the path lengths in its subtree. Then, we can visit the tree to collect the gold using a custom DFS, where the children of each node are ordered on their score and visited from the lowest score to the greatest. 

To tackle the last test set, we need to compare subtrees no longer only on their subtree time, but on the actual time/number of nodes ratio. 

### Results
```
   Test set 1 (30 pts / 1 s) : Correct answer      (0.012s)
   Test set 2 (30 pts / 1 s) : Correct answer      (0.371s)
   Test set 3 (30 pts / 1 s) : Correct answer      (0.353s)
   Test set 4 (10 pts / 1 s) : Correct answer      (0.434s)
```
