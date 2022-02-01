## Severus Snape
This problem is an instance of a binary multidimensional knapsack problem. The challenge is that, except for the first test set, there is no way to optimize the Power and the Happiness together. For this reason, there are no possible greedy shortcuts possible and we need to brute force all the possible combinations. Unfortunately, this naive approach would have a complexity of *O(n\*2^n)*, as for each potion we should make the decision "keep it or discard it".

Fortunately, we do have a powerful tool to make our brute force aproach a slightly more intelligent: DP. However, defining a DP state in this problem is particularly difficult, and definitely not natural if you haven't seen something like this before. The trick is considering as a state the subsequence starting from index *start* of the potions vector, and finding in it this subsequence the max value of Power fixed a specific number of positions to pick and Happines achieved. With this
definition we're able to find the best possible value of Power that respects the Happines bound for each value of picked potions *k*. By iterating over *k* (starting from 0 to n) we can find the smallest number of potions which respects both the constraints for Happiness and Power. 

For the last test set (and also for the first three, but at least for those I wrote the code on my own) thanks to @tarqluca.

![meme](meme.jpg?raw=true)

### Results
```
   Test set 1 (30 pts / 4.500 s) : Correct answer      (0.972s)
   Test set 2 (30 pts / 4.500 s) : Correct answer      (1.128s)
   Test set 3 (20 pts / 4.500 s) : Correct answer      (2.831s)
   Test set 4 (20 pts / 4.500 s) : Correct answer      (2.768s)
```
