## Car Sharing
Car sharing is a flow problem. A simple approach to tackle the problem consists in just generating the entire graph (`S` node per layer [with `S` number of stations and `t` layers (where `t` is the maximum time that appears in the bookings. Then, we connect every station with the following (in the time direction, e.g. station S1_0 with S1_1, S1_1 with S1_2 and so on, where the subscript represent the time) and finally we add the booking edges. However, this approach will pass only the first
three test sets, due to the big number of nodes which are comping the graph.

An improvement to this solution consists in considering only the "important" positions in the graph, i.e. those which appears as source or target of at least one booking, and skipping all the others. This allows us to consider just the relevant subset of nodes in the graph that allows us to solve the problem. However, also this solution won't achieve full points, as even if they're not part of the flow, we're still creating way too much nodes and the program will fail.

The final solution consists in creating a mapping between the relevant nodes and sequential indexes, in order to be able to create a flow graph that uses **only** those nodes. This mapping can be done using a simple `std::unordered_map`. With this trick, we will be able to achieve full score.

**Pitfalls**
- be careful with the costs used in the graph, you need to be able to compare paths that spans a different number of edges
- the final revenue might overflow in the last test case, mind the dimension of the results

### Results
```
   Test set 1 (20 pts / 5 s) : Correct answer      (0.113s)
   Test set 2 (20 pts / 5 s) : Correct answer      (0.001s)
   Test set 3 (20 pts / 5 s) : Correct answer      (0.328s)
   Test set 4 (20 pts / 5 s) : Correct answer      (0.71s)
   Test set 5 (20 pts / 5 s) : Correct answer      (1.388s)
```
