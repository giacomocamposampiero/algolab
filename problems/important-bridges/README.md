## Important Bridges
In this problem, we are required to find the subset of edges in a graph that, if removed, would cause the number of components to increase. 

A naive solution *O(m(m+n))* (that would still pass the first test set) could be to remove from the graph one edge at a time, and then check whether the graph is still connected or not. An improvement to this solution can be achieved using the method `boost::biconnected_components`, that label each edge with the biconnected component it belongs to. Observe that an edge that would cause an increase in the number of components is always alone in its biconnected component (otherwise we could
prove that there is always another path connecting the components). 

Therefore, we need to count the number *n_i*  of edges that belong to each biconnected component. The, iterate over all the edges of the graph and pick those where *n_i* equals to 1. Lastly, we need to sort them for an ordered output.

For achieving the score in the last test set, make sure to order properly *u*,*v* s.t. *u*<*v* for each *e*=(*u*,*v*)!

### Results
```
   Test set 1 (40 pts / 2 s) : Correct answer      (0.005s)
   Test set 2 (40 pts / 2 s) : Correct answer      (0.386s)
   Test set 3 (20 pts / 2 s) : Correct answer      (0.0s)
```
