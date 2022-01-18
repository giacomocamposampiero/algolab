## Canteen
This is a classical Max Flow Min Cost problem. We are required to maximize the number of students served by the canteen and minimize at the same time the cost for serving the meals. Each day can be easily modeled as a node in the flow graph, which has one incoming edge from the source (with capacity equal to the number of menus that can be produced that day and cost equal to the cost of the menu) and two outgoing edges (one to the sink, for students, and one to the following day - not for
the *n-1*-th node - for the refrigerated meals). 

The first two test set can be tackled using negative costs to represent the revenue earned selling out the menus. In order to achieve points for the last test set, we have to change `boost::cycle_canceling` method for cost computation to `boost::successive_shortest_path_nonnegative_weights`, which is indeed faster. To do so, we just need to set an "offset" to the cost of the served menus (no longer negative) and then remove that offset after the computation of the flow cost.

### Results
```
   Test set 1 (30 pts / 2 s) : Correct answer      (1.276s)
   Test set 2 (50 pts / 2 s) : Correct answer      (0.153s)
   Test set 3 (20 pts / 2 s) : Correct answer      (1.614s)
```
