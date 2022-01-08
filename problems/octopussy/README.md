## Octopussy
In this problem, we are required to determine whether there is a feasible "reverse" visiting order (from the leaves to the root) in a binary tree such that every node is visited after a number of steps <= *v*, wwhere *v* is the value of the node. From the input size, we can observe that an algorithm with a complexity at most *O(nlogn)* is required to solve the problem.

Observe that visiting the binary tree from the leaves to the root and finding at each step the first node to visit is not that straightforward. On the other hand, visiting the tree from the root to the leaves is easy! We don't need an additional data structure to save the tree, as we can use a binary heap. Moreover, the task of finding the minimum among the open leaves can be translated, in the context of top-down tree visit, to finding the maximum among the open nodes - we will in fact
obtain the same sequence, with an inverse order. 

The implementation is then rather simple. I've used a `std::priority_queue` to store the list of open nodes during the visit to store the open nodes. This allows to pop the maximum value in the queue in *O(1)*, but also comes with a cost: inserts are now *O(logn)*, as the queue is kept ordered. However, this is fine, since we will perform at most *n* inserts, and the overall complexity will therefore be *O(nlogn)*.

### Results
```
   Test set 1        (20 pts / 1 s) : Correct answer      (0.0s)
   Test set 2        (20 pts / 1 s) : Correct answer      (0.006s)
   Test set 3        (20 pts / 1 s) : Correct answer      (0.016s)
   Test set 4        (20 pts / 1 s) : Correct answer      (0.16s)
   Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.0s)
   Hidden test set 2 (05 pts / 1 s) : Correct answer      (0.006s)
   Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.016s)
   Hidden test set 4 (05 pts / 1 s) : Correct answer      (0.16s)
```
