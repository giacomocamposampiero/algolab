## Surveillance photographs
In this problem, we have to find the maximum number of photographers which can be safely carried to a police station. There are many elements in the text that might suggest that this problem can be solved with flow, and indeed this is the right track to follow. 

For the first test set, the street network is guaranteed to be symmetric - that is, for any pair of intersections x and y the number of streets from x to y is equal to the number of streets from y to x. This is quite an advantage since we're guaranteed that, if a police agent can reach a photograph, there is for sure a way that can be used to return back to the original station. Therefore, we can forget about the way back of each agent and just think about they're journey to the photographs.
The flow in this case can be created wiring the police stations to the source and the photographs to the sink, and creating a network where each edge capacity equals to 1.

For the second test set, we no longer have any guarantees on the structure of the graph. Indeed, we must come up with a method to handle in different ways the "forward" trip of the agents and they're return back to the stations. The trick is that, if we need to have two different constraints on the same network, we can just duplicate the network and set different edge constraints on the two! In this case, we can create two versions of the same network: one with "infinite" edge capacity,
that can be used for the agents to reach the photographs. The photographs' nodes will be the actual link between the two networks: each one of them will be linked with the corresponding node on the 1-capacity network. Finally, in the 1-capacity network we will have to link every police station to the sink (with capacity 1 since every station has only one safe). Doing so, we're forcing the flow to move through the infinite-capacity network to reach every photograph and then we're enforcing the
"one photograph per edge" constraint in the 1-capacity network.

### Results
```
Test set 1 : Correct answer      (0.151s)
Test set 2 : Correct answer      (0.246s)
```
