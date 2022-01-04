## First Hit
In this problem, we start using more challenging applications of CGAL. The problem it's quite similar to [Hit](../hit/), with the (quite important) difference that in this case we are required to actually compute the closest interception to the ray source.

Computing the clostest interception make things quite harder. In fact, the computation of the interception required the use of EPEC kernel (slower than EPIC). Moreover, if we use a naive approach to find the closest interception to the source, we will have to use EPECWS. This obviously isn't enough fast to pass all the test sets, and we will need to use some tricks in order to avoid the use of EPEC with sqrt and limit as much as possible the use of constructions (predicates are far less expensive).

First thing first, observe that we don't actually need to compute the intersection for *every* segment if we create a temporary segment which ties the current best intersection to the ray origin. In fact, we can check whether the new segment intersect the tmp best segment or not; if it does, it means that it intersects the ray before the current best, and we need to compute the new intersection; if it doesn't, we can discard the new segment, as it will intersect the ray after the current best or
it won't intersect it at all.

Moreover, this solution allows us to compute intersections between segments and compute only one intersection ray-segment (the first). In general, the first ones should be (not 100% sure) faster than the others. 

To achieve points from the last set, it was actually necessary to random shuffle the input segments, as they were probably given in a specific adversal order (e.g. ordered by the farthest to the closest --> always need to compute the intersection). However, there are discordant opinions about how to achieve these last points on the Web.

Take-home messages:
- intersections segm-segm are faster than intersections with rays
- avoid constructions as much as possible
- EPEC with sqrt should be used only if there are literally no other options
- shuffling the input might help in some problems

### Results
```
   Test set 1 (15 pts / 1.000 s) : Correct answer      (0.006s)
   Test set 2 (15 pts / 1.000 s) : Correct answer      (0.055s)
   Test set 3 (15 pts / 1.000 s) : Correct answer      (0.068s)
   Test set 4 (15 pts / 1.000 s) : Correct answer      (0.054s)
   Test set 5 (10 pts / 1.000 s) : Correct answer      (0.182s)
   Test set 6 (10 pts / 1.000 s) : Correct answer      (0.062s)
   Test set 7 (10 pts / 1.000 s) : Correct answer      (0.053s)
   Test set 8 (10 pts / 0.200 s) : Correct answer      (0.053s)
```
