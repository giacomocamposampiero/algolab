## Asterix in Switzerland
This problems is as difficult as easy it's the final solution. We are required to find a subset of the provinces whose difference between sum of balances and sum of the outgoing debts (edges) is positive. The number of provinces is at most in the order of 10^3, whereas the maximum number of edges (debts) is 10^5. 

A possible naive solution would be brute-forcing all the possible subsets of provinces. This solution, since n<=20, might actually manage to pass the first test set (I've not tried tho, but the complexity should be something around 2^20 ~= 10^6 which is still good for the given time limit).
Other solution might achieve partial score in the specific subtasks (e.g. we can observe that in test set 2 and 3 edges are always stronger in magnitude w.r.t. balances, so we might succed exploiting this characteristic, by looking at only connected components).

However, none of these approaches will bring you more than 40 points, at most. The right idea is indeed totally different, and exploit flows. In fact, we built a flow connecting every node with a balance >0 to the source (it can "give" cash to other provinces if needed) and every node with a balance <=0 to the sink (this provinces need cash, which is flow in our setting). Then, we might add all the debts as edges in the graph, with capacity equal to the value of the debt. The intuition
is that money will flow from source to targets, and if it exists a subset of the graph which has a net positive cash quantity this subset will create a bottleneck in the network, and indeed this will limit the value of the flow, which won't longer be equal to the sum of the positive balance. By checking the value of the flow of the network, we can determine if the required subset exists or not in the given graph.

### Results
```
   Test set 1 (20 pts / 1 s) : Correct answer      (0.0s)
   Test set 2 (20 pts / 1 s) : Correct answer      (0.229s)
   Test set 3 (20 pts / 1 s) : Correct answer      (0.149s)
   Test set 4 (40 pts / 1 s) : Correct answer      (0.232s)
```
