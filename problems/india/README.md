## India
This problem is clearly a graph problem, where cities correspond to vertices and guides correspond to edges. Moreover, every edge (guide) has a capacity (i.e. the number of elefants that can be used to move the luggages within that path) and a cost (moving every elephant has a defined cost). Moreover, we are also given the position of the source and target cities in the graph. This seems quite a bit a Min Cost Max Flow problem, and indeed it is!

For the first three test set, we know that the number of luggages that we will be able to move is either [0,10] - if the budget is not enough to transport all of the luggages - or `tot_el`, which represent the total number of elephants that can be moved between the two cities. Therefore, we can just add one edge at a time of capacity 1 for the first 10 edges, and check if the cost of the flow is smaller than the given budget. Then, we need also to check the cost for the case when *all*
elephants can be moved between the two cities, as it might be the case for some test cases. 

For the last test set, the number of luggages that can be moved between the two cities is no longer limited to 11 values as before, and indeed we cannot check every possible number of luggages (which is in the worst case in which all the guides directly connect the source and the target cities equal to the total number of elephant, ~10^6). But here's the trick: the number of elephants is naturally ordered, and therefore we can use binary search to find the optimal number of luggages
in logarithmic time. Now, time complexity is again good enough to achieve full points.

### Results
```
   Test set 1  (20 pts / 5 s) : Correct answer      (0.387s)
   Test set 2  (20 pts / 5 s) : Correct answer      (0.951s)
   Test set 3  (20 pts / 5 s) : Correct answer      (0.753s)
   Test set 4  (20 pts / 5 s) : Correct answer      (0.634s)
   Test set 1h (05 pts / 5 s) : Hidden             
   Test set 2h (05 pts / 5 s) : Hidden             
   Test set 3h (05 pts / 5 s) : Hidden             
   Test set 4h (05 pts / 5 s) : Hidden  
```
