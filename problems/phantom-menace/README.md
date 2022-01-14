## Phantom Menace
This Problem of the Week feels rather easy. In fact, it's a simple variation of the minimum cut problem. In this variation, battleships need to be placed on astronomical objects, not on the edges connect them. Therefore, the cut need to be perfomed on the graph vertices, not edges. However, "duplicating" each node and inserting an edge with capacity of 1 between the splitted vertices is enough to do the trick.

### Results
```
   Test set 1        (25 pts / 2 s) : Correct answer      (0.311s)
   Test set 2        (25 pts / 2 s) : Correct answer      (0.029s)
   Test set 3        (30 pts / 2 s) : Correct answer      (0.324s)
   Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.31s)
   Hidden test set 2 (05 pts / 2 s) : Correct answer      (0.029s)
   Hidden test set 3 (10 pts / 2 s) : Correct answer      (0.323s)
```
