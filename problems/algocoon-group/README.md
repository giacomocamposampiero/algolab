## Algocoon Group
This problem is very easy to code, but understanding how to get the solution might be not so trivial. The first two test set are rather easy to achieve, and we will indeed start solving the problem from them. 

First of all, it's clear that we must interpret each statue as a graph, where figures correspond to nodes and limbs to edges. Since we want to separate the statue in half and every limb has an associated cost, this problem can be rephrased as a *minimum cut* problem. In the tutorial problem we saw that the cost of the minimum cut, to be minimum, must correspond to the value of the maximum flow. Applying the definition directly to our problem, we are able to achieve the first 10 points.
The second test set is also quite intuitive, as we still know the starting point for the flow and we just need to find out the end point: just iterate over all the other vertices we're done.

The last three test sets, however, are quite more challenging. We don't know any of the two endpoints of the flow (i.e. we don't know if a particular figure belongs to us or to our friend). Testing all the possible pairs (quadratic) might work only for very small input, like in test set 3. However, we can observe that we don't need to test all the possible pairs: in fact, we either get figure 0 or not, since we're only two people contending each figure. Therefore, it's possible to test all
the possibilities in two iterations: one if we get figure 0 and one if our friend gets figure 0.

A possible improvement to this solution, reported in the official solutions, is to test only the pairs (0,1), (1,2), (2,3), ... , (n-2,n-1), (n-1,0), as in this way we're still testing for each figure the case is taken from us or from our friend. 


### Results
```
   Test set 1 (10 pts / 3 s) : Correct answer      (0.651s)
   Test set 2 (10 pts / 3 s) : Correct answer      (0.6s)
   Test set 3 (20 pts / 3 s) : Correct answer      (0.04s)
   Test set 4 (30 pts / 3 s) : Correct answer      (0.627s)
   Test set 5 (30 pts / 3 s) : Correct answer      (0.459s)
```
