## The Iron Islands
In this problem we are given a star-shape graph (where the join of the different branches - waterways in the problem descript - is always the same node) and we are required to find the maximum subset of connected vertices which sums up to exactly `k`. It is important to observe that, even if there can be up to `n` branches in the graph, the solution will always span at most 2 branches, due to the constraint that no islands can be visited more than once. Given this pieces of information, we're
good to start solving the problem.

For the first half of the points, the number of brances is low enough to brute-force all the possible pairs of branches. Once we have all the possible joined paths, we can use a sliding window approach to linearly find the biggest subsequence of vertices in all the possible paths. However, finding all the branches combination has a complexity of *O(w^2)*, that as already mentioned before is not good enough to pass the last two test sets.

For these one, we have to come up with some new idea. Visiting every branch starting from the root, we can observe that only one value is appropriate to complement the current partial sum of soldiers. Saving the best number of islands which can visited with a given number of soldier, we might be able to determine for every partial sum value if there is a corresponding complement in the other island and to compute the total number of islands that would be covered by the sum of the
visited islands in the two branches. Since the lookups and the insertions are *O(1)* in average, using an `std::unordered_map` to store complementary values, the overall algorithm would have a total complexity which is **in average** linear in the number of islands. 

### Results
```
   Test set 1 (25 pts / 2 s) : Correct answer      (0.44s)
   Test set 2 (25 pts / 2 s) : Correct answer      (0.501s)
   Test set 3 (25 pts / 2 s) : Correct answer      (0.537s)
   Test set 4 (25 pts / 2 s) : Correct answer      (0.579s)
```
