## Shopping Trip
Yet another simple problem (from an algorithmic perspective) to get used to flows with BGL. In this case it's easy to observe that, since Rick need to return back home after each visit to a store, the problem can be modeled as a "directed" (in the sense that the flow just flows forward from the source to the sink) flow problem. The constraint that each edge can be visited at most once can be modeled setting edge capacities to 1 (except for the edge between the source and Rick's
house, which need to have a capacity of s).

To get the solution of the problem. we just need to compare the flow value with the number of stores - if they're equals it means that there are at least s paths from Rick's house to the sink, and indeed all the stores can be reached.

### Results
```
   Test set 1 (40 pts / 1 s) : Correct answer      (0.0s)
   Test set 2 (40 pts / 1 s) : Correct answer      (0.009s)
   Test set 3 (20 pts / 1 s) : Correct answer      (0.081s)
```
