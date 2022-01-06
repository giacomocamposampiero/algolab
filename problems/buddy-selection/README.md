## Buddy Selection
In this problem we are required to find if a given assignment of pairs in a set is optimal or not. The optimality in this case is defined by the minimum number of characteristics shared by every pair in the assignment (the more more common characteristics the two elements have, the best the pairing is).

To find the solution, we just need to compute - for every possible pair of elements in the set - the number of common characteristics; if this number is strictly greater than *f* (the given number of shared characteristics in the assignment to be tested) we can add an edge in a graph between the two nodes. Finally, we just need to compute the maximum matching with Edmond's algorithm and check if it's cardinality is equal to *n/2* (all the elements are paired). If it is, the current
assignment is not optimal, otherwise it is.

For the last test set, we just needed to refine the more computationally intensive part of the algorithm, which is the computation of the number of common characteristics between elements. A naive implementation of this would be *O(n^2\*c^2)*, if we check for every pair of elements and every pair of characteristic if they're equal.
A little improvement can be achieved ordering the vector of characteristic for every element of the set, and then for every pair iterating over the characteristic of the first and using binary search to find whether the element is contained in the other. This approach would lead to a complexity of *O(n^2\*c\*logc)*, which is unfortunately still too big for our problem, as it corresponds to ~400^2\*100\*2=3.2\*10^8, which is more or less 1.2s higher than the time limit. 

The problem is that we're not taking advantage of the ordering in the first array. In fact, if we can use a "merge" approach to compare the two vectors in linear time, with an overall algorithm complexity *O(n^2\*c)*, which allows us to achieve the points for remaining test set.  

### Results
```
   Test set 1  (30 pts / 2 s) : Correct answer      (0.04s)
   Test set 2  (40 pts / 2 s) : Correct answer      (0.084s)
   Test set 3  (20 pts / 2 s) : Correct answer      (0.71s)
   bordercases (10 pts / 2 s) : Correct answer      (0.044s)
```
