## Evolution
This problem does not belong to a specific category of problems, and requires the use of different techniques to get full score. The first test set is not too difficult to pass. It's enought to save for each species the pointer to its anchestor, and then follow the pointers until when the species' age is no longer less or equal to the given bound. This approach in the worst case scenario has complexity *O(nm)*, which is good for the first test set but not for the second.

Since the input has size in the order of 10^4, a *O(nlogm)* or *O(mlogn)* solution is required. A possible thought might be DP (trying somehow to define states as the older anchestor you can visit with age <= threshold from a certain node, but we quicly realize that age would be a memoization dimension, and this is not possible given the size of the dimension. Another possible solution might be saving every path from the leaves to the root, but also this approach is doomed to fail: constructing
the possible paths would be quadratic in time. 

However, we are almost there. In fact, we can observe that visiting every path in the tree (and looking for the oldest anchestor in that path) it's possible using DFS! Grouping all the queries by name, it's then possible to solve them when the corresponding node is reached using binary search on the partial path (*O(logn)* for the search). Some improvements to the presented solution are indeed possible (probably struct slow down the overall execution time and a mapping between
species names and numbers, but it still manages to pass the second test.

### Results
```
   Test set 1 (30 pts / 1 s) : Correct answer      (0.047s)
   Test set 2 (70 pts / 3 s) : Correct answer      (2.783s)
```
