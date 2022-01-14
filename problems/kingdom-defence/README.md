## Kingdom Defence
This problem is a circulation problem with lower bound constraints on each edge. The solution of the problem is quite straightforward with the slides from the [tutorial session](https://algolab.inf.ethz.ch/doc/tutorials/tut07_bgl_flows.pdf). The only remarks that it's worth doing about the problem are:
- since the soldiers can use more than once the same path, we cannot model the problem as a "forward" flow, as there would be no way for the soldiers to use multiple paths
- it's important to "normalize" the value of the flow, as for each minimum required flow on edge we're adding to the value of the flow that value; therefore, when we check the actual value of the flow, we must take in account that the flow will have that surplus in it

This solution is not one of the fastest around the Internet. In fact it could still be improved with some pre-computation of net node incoming/outgoing flow from source and sink. However, the solution is slow but passes all the tests, so it's really not necessary to achieve full points.

### Results
```
   Test set 1        (15 pts / 5 s) : Correct answer      (2.19s)
   Test set 2        (15 pts / 5 s) : Correct answer      (0.761s)
   Test set 3        (25 pts / 5 s) : Correct answer      (2.487s)
   Test set 4        (25 pts / 5 s) : Correct answer      (2.175s)
   Hidden test set 1 (05 pts / 5 s) : Correct answer      (2.362s)
   Hidden test set 2 (05 pts / 5 s) : Correct answer      (0.81s)
   Hidden test set 3 (05 pts / 5 s) : Correct answer      (2.175s)
   Hidden test set 4 (05 pts / 5 s) : Correct answer      (2.877s)
```
