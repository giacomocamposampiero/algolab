## Deck of Cards
In this problem we are required to find the first subsequence (in alphabetical order, i.e. with the lower couple of indices i and j) of a given vector whose sum of all elements is closer to a given number *k*. 

We can observe that the time limit for the problem is set to 1s, and from this observation we can derive all the three possible solutions of the problem.
For the first test case the complexity of the algorithm must be *O(n^3)*: this is the complexity obtained by a naive algorithm that iterates overall all the possible combination of indices i and j and sum all the values between the two bounds. 

For the second test case we observe that the complexity must be reduce to *O(n^2)* in order to avoid the time limit. To do so, we need to implement the partial sum trick, that allows us to compute the sum between the two indices i and j in *O(1)*. 

For the third test case, a linear solution to the problem has to be found. In this case, a sliding window allows us to find the best pair of indices without iterating over all the possible combinations of i and j.

### Results
```
   Test set 1        (20 pts / 1 s) : Correct answer      (0.0s)
   Test set 2        (40 pts / 1 s) : Correct answer      (0.007s)
   Test set 3        (20 pts / 1 s) : Correct answer      (0.134s)
   Hidden test set 1 (05 pts / 1 s) : Correct answer      (0.0s)
   Hidden test set 2 (10 pts / 1 s) : Correct answer      (0.007s)
   Hidden test set 3 (05 pts / 1 s) : Correct answer      (0.134s)
```
