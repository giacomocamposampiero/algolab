## Hand
It was helpful to me interpet this problem as a clustering problem (possible as every tent has to be assigned to one and only one family) and use the given sample code given [here](https://algolab.inf.ethz.ch/doc/tutorials/sample_code/tut08_emst.cpp).
The problem required to answer two different questions:

1. For given f0, what is the largest s such that there exists an (f0, s)-reasonable assignment? 
2. For given s0, what is the largest f such that there exists an (f, s0)-reasonable assignment?

To answer the first question, we have to find the minimum distance between clusters when there are exactly f0 clusters. For the second question, we have to find the number of clusters when the minimum distance between different clusters equals to s0. With this approach, we can tackle the first three test sets. 

For the last test set, a further step has to be done: in this case, a new constraint on the minimum number of tents for each family is added. Therefore, we can no longer rely on the simple number of clusters (i.e. connected components) in the map, but we also have to work with the actual number of **valid** clusters (which contains a number of nodes >= k). To keep track of this information, we could compute it after linking every new component, but this would have a quadratic (more or less)
complexity in the number of tents, hence not efficient enough to pass any of the tests (except only the first one, probably). However, a faster computation can be done by keeping track of the number of components that have a specific size (i.e. have a counter for the components of size 1, 2, 3 and 4) and updating them after each linking operation. Finally, observe that a naive computation of the number of cluster (just counting the number of cluster of size >= k) will fail, since we're
not considering that every tend has to be assigned to at least one family. In fact, it is allowed to assigned multiple [separate] clusters to the same family, and this obbiously influence the number of family that can be accomodated, which is actually greater or equal to the number of cluster of size >= k (due to the possibility of combining lower-size clusters). 

### Results
```
   Test set 1 (30 pts / 2 s) : Correct answer      (0.013s)
   Test set 2 (30 pts / 2 s) : Correct answer      (0.373s)
   Test set 3 (20 pts / 2 s) : Correct answer      (0.321s)
   Test set 4 (20 pts / 2 s) : Correct answer      (0.242s)
```
