## Casino Royale
This problem has many elements which might suggest that is a flow problem, and indeed it is. However, it might be interesting take in account also other possible approaches to tackle the problem. 
For instance, a possible alternative could be using a greedy algorithm that uses a earliest finish time strategy (like for example in [Boats](../boats/)). However, we soon realize that this approach works well when priorities are all equals, but not as much for heterogeneous mission priorities.

Back to the flow solution, we have to find the right formulation of the flow to model the problem. Firstly, we can create the network, linking each station `t` to the following `t+1`. Note that we are required to maximize the total sum of selected mission's priorities, and we therefore need to reformulate weights in such a way that the Min-Cost-Max-Flow algorithm will produce the right answer. A possible solution is to use negative weights for the mission priorities. However, as we know, the most efficient method for cost computation
`boost::successive_shortest_path_nonnegative_weights` only works with non negative weights.

To reformulate non negative weights, we need to add an offset to every edge in the graph. To do so, we will consider each segment between the stop `t` and stop `t+1` to have a fixed cost of 128, which corresponds to the maximum priority that a mission can achieve. Then, every mission edge will be given a cost equal to the number of edges between the source station and the target station minus the actual priority of the mission. The total maximum priority sum will be computed as the
difference between the `flow * 128 * number of stations` minus the actual cost of the flow. 

The last step we're missing is how to fix the constraint on the maximum number of agents. This is rather easy to implement, as we just need to set the constraint on the edge which links the source to the first station.

### Results
```
Test set 1 : Correct answer      (0.015s)
Test set 2 : Impossible to test in CodeExpert
Test set 3 : Impossible to test in CodeExpert
```
