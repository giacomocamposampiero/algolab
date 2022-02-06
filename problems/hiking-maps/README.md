## Hiking Maps
In this problem, we are required to find the smallest subsequence of a list that satisfy a geometric condition. The geometric condition is that every given segment is contained in at least one of the triangles contained in the subsequence. The problem can be splitted in two smaller problems:

- determine, for each triangle, which segments it contains
- determine the smallest subsequence of triangle which contains all the segments

For the first task, the use of CGAL is required. In this case, solving the problem is feasible using the less-expensive kernel, EPIC. In fact, the predicates `left_turn` and `right_turn` allow us to determine if a segment (defined by it's source and target points) is contained in the triangle or not. No construction are neeeded.

The second task is a simple lookup of the smallest subsequence that satisfy a certain condition. So far we have already seen many examples of how to deal with this problem, and the use of a sliding window approach should be automatic. In this case, however, the sliding window approach can't be linear (we must check for every interval if all legs are contained). As a result, an *O(n\*m)* will be the best that we can achieve, but given the input size (n,m < 2000) this should be fine.

### Results
```
   Test set 1 (20 pts / 0.400 s) : Correct answer      (0.003s)
   Test set 2 (20 pts / 0.400 s) : Correct answer      (0.008s)
   Test set 3 (20 pts / 0.400 s) : Correct answer      (0.08s)
   Test set 4 (20 pts / 0.400 s) : Correct answer      (0.224s)
   Test set 5 (20 pts / 0.400 s) : Correct answer      (0.191s)
```
