## Punch
In this problem we are required to find the minimum cost of a valid punch which, in case of tie (different punches which have the same cost) maximizes the number of different beverages used to compose the punch. The approach adopted to solve this problem was DP. 
The DP state can be defined, in this setting, as a couple of values (cost of the punch and number of beverages contained in it) that optimizes our object given a the index of the current beverage, the volume of punch already "created" and if this beverage was taken for the first time in this iteration or not. 
The DP table has a space complexity of *O(k\*n)*, which is well within the limits we have for the computation and the used memory.

### Results
```
   Test set 1 (50 pts / 2 s) : Correct answer      (0.012s)
   Test set 2 (50 pts / 2 s) : Correct answer      (1.05s)
```
