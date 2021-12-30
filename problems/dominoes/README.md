## Dominoes
In this problem, you are dealing with a special kind of domino set, in which the tiles are of different heights. Your task is to determine, given an arrangement of these tiles in a line, how many of the domino tiles will fall after toppling the left-most domino.

More precisely, we have the following set-up: the dominoes are placed at successive points on the integer line, the first at position 1, the second at 2, and so on. If a tile of height h at position i is toppled, this causes the tiles at all positions j > i such that j − i < h to fall as well.

### Results
```
   Test set 1 (50 pts / 1 s) : Correct answer      (0.0s)
   Test set 2 (50 pts / 1 s) : Correct answer      (0.562s)
```
