## Beach Bars
In this problem, we have a number of elements placed in a 1-dimensional coordinate system (i.e. a line) and we are required to find the position(s) `x` in the line which maximize the number of elements in the range `[x-100, x+100]`.  
Furthermore, since many positions could maximize this parameter, we are required to pick only those ones which minimize the maximum distance between the bar position `x` and the furthest element(s). 

From the given maximum size of the input, we can see that our solution can be at most *O(nlogn)*. Note that if the input coordinates were ordered, we could apply a sliding window approach and get the solution in a linear time, as we would need to evaluate only connected intervals in the 1-d grid (conceptually it's not too different from the [PoTW2](../deck-cards/)). But sorting the input vector is *O(nlogn)*, and therefore the solution is good enough to solve all the given test sets.

### Results
```
   Test set 1 (20 pts / 1 s) : Correct answer      (0.001s)
   Test set 2 (20 pts / 1 s) : Correct answer      (0.002s)
   Test set 3 (60 pts / 1 s) : Correct answer      (0.389s)
```
