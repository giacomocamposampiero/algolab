## Motorcycles
In this problem we are required to find the number of rays in a set which don't cross other rays or cross them in an intersection point which is closer (in terms of Euclidian distance) to their origin rather than the other intersecting ray's origin.

The use of a CGAL kernel in this case works but it's not efficient in terms of complexity. We can observe that we don't need to actually construct rays, but it's possible to compare them and solve the problem by working with just two of their properties: the starting y and the slope of the ray. Moreover, the input size is in the worst case 10^5, which means that our solution should have a complexity of at most *O(nlogn)*. 

First thing first, observe that ordering the rays on their starting y could be really helpful. In fact, without an order we would have to compare each ray with all the others at least one time, and this clearly doesn't respect our upper bound on the complexity. Moreover, observe that if the rays are ordered, it's possible to compare them using as only parameter their slopes. 

For the first 3 test sets, where all the slopes are positive, we can just observe that if we have two ray ordered on their starting y, the only way for the second not to intersect the first is to have a slope which is equal or lower than the first. Otherwise, even if its slope is infinitely bigger than the other, they will intersect for sure (at least in the limit x->+inf) and the first ray will win, as the intersection will be closer to it. Therefore, we just need to iterate over the
ordered rays, starting from the top one, keeping track of the current min slope (updating it for every good ray we find).

The last test set was actually difficult to figure out for me, but it only requires an additional iteration from bottom to top.

###
```
   Test set 1        (20 pts / 4 s) : Correct answer      (0.014s)
   Hidden test set 1 (05 pts / 4 s) : Correct answer      (0.014s)
   Test set 2        (20 pts / 4 s) : Correct answer      (0.045s)
   Hidden test set 2 (05 pts / 4 s) : Correct answer      (0.045s)
   Test set 3        (20 pts / 4 s) : Correct answer      (0.159s)
   Hidden test set 3 (05 pts / 4 s) : Correct answer      (0.159s)
   Test set 4        (20 pts / 4 s) : Correct answer      (1.199s)
   Hidden test set 4 (05 pts / 4 s) : Correct answer      (1.199s)
```
