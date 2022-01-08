## Boats
This problem is, in fact, very similar to the interval scheduling problem presented in the week tutorial (slides [here](https://algolab.inf.ethz.ch/doc/tutorials/tut05_greedy_split_and_list.pdf)). As we have seen in the turorial session, it's possible to prove that finding the maximum number of mutually compatible intervals can be done with a greedy algorithm. The greedy strategy consists of picking always the interval with the earlier finish time (**staying ahead**). 

In our setting, this equals to place every boat starting from the leftmost available position - i.e. the maximum between *p-l* and the last occupied position from the previous boat. If the starting position is lower than the ring position, this means that there are no conficts between the two boats and we can pick both of them. Otherwise, there is a conflict and we need to choose which one discard and which one mantain. Here's we apply our greedy decision, by comparing the two
ending positions (observe that for the second boat we need to re-compute the starting position not considering the previous boat). The resulting algorithm is linear in the number of boats. 

However, the boats are not given in an ordered fashion, and initially we will need to order them on their ring positions. This steps has a complexity of *O(nlogn)*, which is therefore also the complexity of our total algorithm.

### Results
```
   Test set 1 (30 pts / 2 s) : Correct answer      (0.002s)
   Test set 2 (30 pts / 2 s) : Correct answer      (0.006s)
   Test set 3 (40 pts / 2 s) : Correct answer      (0.684s)
```
