## Moving Books
In this problem, we are required to find the minimum number of step necessary to empty a container. However, the elements of the container are weighted, and so are the "moving capabilities" - we can remove *n* elements in each step, but the "removers" have a certain strenght and can remove only the elements whose weight is lower or equal to their strength.

As a first step, we order both the container (books) and the "removers" (friends). The ordering of container is performed automatically using a particular data structure, the `multiset` (an associative container that contains a sorted set of objects). The multiset allows *O(1)* removals and *O(logn)* lookups, which will be used a lot in the solution. 

Then, we just iterate until the container is empty or there are no friends that are able to move the boxes left. In the first case, we found the best assignment of boxes to the friends and we can print out the time we needed to move all the boxes; in the second one, there is no viable solution and we need to output `impossible`.

### Results
```
   Test set 1 (20 pts / 1 s) : Correct answer      (0.008s)
   Test set 2 (40 pts / 1 s) : Correct answer      (0.51s)
   Test set 3 (40 pts / 1 s) : Correct answer      (0.89s)
```
