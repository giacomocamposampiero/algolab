## Knights
This problem is not excessively difficult to model on paper, but implementing requires some attention with indices. Our goal is to maximize the number of knights that are able to exit from the cave. Since the cave can be modeled as a graph (where hallways are edges and intersections are nodes) and we have specific constraints on edges and vertices, it's quite straightforward to use flows. 

First of all, we neeed to define constraint on hallways (edges): it's enough to define a max capacity of 1 for each edge. Then, we need to model the constraint on intersections, that can be visited at most C times. Since with flows we can define constraints only on edges, the trick is to split every vertex in two vertices, connected by an "artificial" edge. We can now define our vertex constraint as an edge constraint by setting the capacity of the inter-vertices edge to C.

Finally, observe that hallways are undirected: for each of them we need to add two edges in the flow graph, one from the `out_node` of the first to the `in_node` of the second and vice-versa, from the `out_node` of the second to the `in_node` of the first. `in_node` and `out_node` are two helper functions defined to improve readability of the the code and to make our life easier debugging.

### Results
```
   Test set 1 (40 pts / 1 s) : Correct answer      (0.134s)
   Test set 2 (40 pts / 1 s) : Correct answer      (0.122s)
   Test set 3 (20 pts / 1 s) : Correct answer      (0.125s)
```
