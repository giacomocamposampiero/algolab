## Ludo Badman
This problem might seem at first sight an LP problem. However, we soon realize that it can't be, as the input dimensions are too big (either we use one variable for team or for match doesn't really make any difference, they're both above the upper threshold for "good" LP execution time. Our second hope might be to model it as a flow problem, and in this case we are definitely more lucky. In fact, we can observe that we can represent the matches as edges in a biparthite graph (where all East
teams are on the left side and all West teams are on the right side). 

The main difficulty in this problem is, however, to model the constraint that every team must play at least `l` not difficult matches in the schedule. In order to do so, we have to be able to redirect part of the flow (the necessary `l` matches for each team) on a preferential route. A practical solution is indeed adding two helper nodes, one for the left part of the graph and one for the right. This trick allows us to redirect all the "excessive" flow through those nodes, while imposing at the
same time a minimum amount of flow through each node. The ausiliary node will be able to carry at most `p - l*e` and `p - l*w` flow each, which is indeed "what we're missing to get the total required number of matches". The total risk of a schedule can be computed simply defining a cost for each match edge and computing the flow cost. 

To get the last 25 points, it's necessary to handle the difficult matches conditions. These matches can't clearly be inserted with the others, as there would be no way to differentiate between them. Therefore, we need to define `e+w` additional nodes to the graph, where we can place the corresponding matches. Then, we can link these nodes with the ausiliary nodes (only excess of flow will flow through them, meaning that they will be picked only when the `l` easy matches constraint will be
satisfied.

### Results
```
   Test set 1 (25 pts / 2 s) : Correct answer      (0.103s)
   Test set 2 (25 pts / 2 s) : Correct answer      (0.49s)
   Test set 3 (25 pts / 2 s) : Correct answer      (0.662s)
   Test set 4 (25 pts / 2 s) : Correct answer      (1.172s)
```
