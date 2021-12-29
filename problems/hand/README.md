## Hand
It was helpful to me interpet this problem as a clustering problem (possible as every tent has to be assigned to one and only one family) and use the given sample code given [here](https://algolab.inf.ethz.ch/doc/tutorials/sample_code/tut08_emst.cpp).
The problem required to answer two different questions:

1. For given f0, what is the largest s such that there exists an (f0, s)-reasonable assignment? 
2. For given s0, what is the largest f such that there exists an (f, s0)-reasonable assignment?

To answer the first question, we have to find the minimum distance between clusters when there are exactly f0 clusters.
For the second question, we have to find the number of clusters when the minimum distance between different clusters equals to s0.

### Results
```
  Test set 1 (30 pts / 2 s) : Correct answer      (0.013s)
  Test set 2 (30 pts / 2 s) : Correct answer      (0.368s)
  Test set 3 (20 pts / 2 s) : Correct answer      (0.317s)
  Test set 4 (20 pts / 2 s) : Wrong answer        (0.239s)
```
