## Asterix and the Chariot Race
If you're reading this after being trapped for hours in the rabbit hole of thinking about this problem as a vertex cover, I feel you. However, you (and me) could potentially save many time just by checking the last test case. In this last example, in fact, it's easy to see that the vertex cover isn't always the solution, and to observe that for a city it's sufficient to have at least one of the connected neighbors repaired, and not one for every stage (as it would be if a vertex
cover was required). 

Back on the tracks of the right solution, we can observe that the starting point of the race is always unique (in the node 0) and therefore the race paths can be seen as a rooted tree. This makes a lot of difference, as we might start thinking about the problems in terms of tree algorithms. Indeed, we can observe that the problem can be decomposed in smaller sub-problems (i.e. subtrees). We can observe that each root of a subtree can have one of these three different states:

- **picked**, if the corresponding city is picked to be repaired (we need to consider the cost of this node)
- **covered**, when the corresponding node is not picked, but it's covered by at least one of its descendant
- **not covered**, when the node is neither picked or covered by its descendant, and therefore need to be covered by its anchestor

These states can be combined and progated through the tree using DFS. Starting from the root node, we can recursevely visity the tree and all its possible states. The cost values for each situation are computed as follows:

- for the **not-covered** state, the cost is computed as the minimum between the sum of the covered state of its anchestors (it is not covered by its anchestors, and indeed those must be not picked and also not not-covered) and the picked result for the same node (it might be convenient to pick the node in some situation)
- for the **covered** state, the cost is computed as the sum of covered state of the anchestors (which are already the optimum); it's important in this case to ensure that *at least one anchestor's cost* is selected as picked, otherwise the node won't be covered
- for the **picked** state, we need to sum the current cost of the node with the sum of **not-covered** costs of its anchestors (note that this un-covered costs is computed as the minimum between the **picked** and **covered** cost, and indeed we're considering the optimal solution)

The optimal solution for every sub-problem, given how we're computing the different costs, is always contained in the **covered cost** (since it's always the min between the picked cost and the covered cost).

### Results
```
   Test set 1 (25 pts / 3 s) : Correct answer      (0.084s)
   Test set 2 (25 pts / 3 s) : Correct answer      (0.091s)
   Test set 3 (25 pts / 3 s) : Correct answer      (0.09s)
   Test set 4 (25 pts / 3 s) : Correct answer      (1.364s)
```
