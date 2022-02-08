## Lestrade
In this problem, we are required to find a minimum cost assignment between agents and gang members. The solution requires to use differented techniques, namely LP and triangulations.

The first subproblem that we need to tackle is to find the closest gang member to each given agent. In this case, we can observe that the size of the gang members is small enough to allow the construction of a Delauny's traingulation, which will then allow us to find the closest member to each agent. Once we found for each agent the closest gang member, we have to "filter" the agents, since many agents might be closer to the same member and we just need one to get the informations (it can be
proven easily that a solution that includes more than one agent for each gang member is not optimal in terms of overall cost). 

Once we found the cheapest agent to monitor each gang member, we now have to find out whether it exists a valid subset of the agents such that the sum of their costs is lower than Sherlock's fee and all the constraints on the three information quantities (`u`, `v` and `w`) are satisfied. We can observe that a greedy approach is impossible, and also a DP approach would fail (we would need to store the three quantities to optimize but they're all >= 2^24, therefore the memo table is way too
big to be handled efficiently). However, we can observe that all the given constraints are linear in the number of surveillance hours. This sounds a lot like LP (and indeed it is!). 

The variables will be defined as the number of hours worked by each of the min-cost agents (bounded by `0 <= h <= 24`). On the other hand, we will need only three constraints: one for each of the three questions *how*, *where* and *whom*. Finally, the objective function can be trivially defined as the sum `h * agent_cost`.

### Results
```
Test set 1 : Correct answer      (0.486s)
Test set 2 : Correct answer      (0.487s)
Test set 3 : Impossible to test in CodeExpert
```
