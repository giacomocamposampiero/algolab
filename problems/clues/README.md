## Clues
In this problem, the second and the third test sets are rather easy. Without having to check the status of the network (interferenced or not) the problem just boils down to find whether the two points are in the same connected component with edges of length <= `r` or if they are at distance again <= `r` (this is probably the most insidious particular about those test sets).

The real challenge in this problem was, at least for me, to find whether the network was good or not. One possible strategy to tackle this problem is implementing a BFS with node coloring, to find out if we already visited a node and, if we had, if the assigned color is compatible with the color of the new discovered neighbor. Needless to say, the difficulty in this case was rather implementative than conceptual. 

### Results
```
   Test set 1        (15 pts / 2 s) : Correct answer      (0.088s)
   Test set 2        (25 pts / 2 s) : Correct answer      (0.739s)
   Test set 3        (25 pts / 2 s) : Correct answer      (1.134s)
   Test set 4        (15 pts / 2 s) : Correct answer      (1.421s)
   Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.088s)
   Hidden test set 2 (05 pts / 2 s) : Correct answer      (0.739s)
   Hidden test set 3 (05 pts / 2 s) : Correct answer      (1.134s)
   Hidden test set 4 (05 pts / 2 s) : Correct answer      (1.421s)
```
