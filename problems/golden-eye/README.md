## Golden Eye
This is a classical triangulation problem. The problem can be described as follows: there is a collection of congruent disks (umbrellas) whose centers are given, but the radius (power consumption) is variable. One can safely move within the union U of these disks. Depending on the radius, U may consist of several connected components. Missions are given as source and target points. A mission can be executed if source and target lie in the same component of U. The goal is to figure out:

- which of the missions can be executed for a given starting radius `p`
- what is the smallest radius `a` so that all of the given missions can be executed
- what is the smallest radius `b` so that all of the missions from the first subtask can be executed

The test sets can be divided in two main groups: 
- test set 1 is the easiest, as we are only required to find the solution for the first subtask
- test sets 2, 3 and 4, on the other hand, require to tackle all the subtasks

To find out if a mission can be executed or not, we need to find the components which are connected when the radius corresponds to the given radius, and then check if the mission starting and end points lies on the same component [and obviously if they are at a distance lower than the given radius]. To find out the connected components, it's useful to use the `boost::disjoint_sets_with_storage` container, which allows us to keep track of connected components. As usual, we order the Delauny's
edges by squared length and pick the shortest one and connected the two endpoints, until when the squared length of the edge becomes greater than the given radius. Then, we just need to compare the connected component associated to the nearest vertex of every starting point of a mission with the connected component of the nearest vertex of the corresponding end point. The job is done!

For the other two subtasks, it's a little more tricky. For the smallest radius `b`, we need to keep track of the missions which are doable with the given radius. For both `a` and `b`, then, it will be necessary to keep track of the maximum distance between the endpoints of the missions [in the case of `b` only of the doable missions] and the nearest vertices. Then, we will just need to re-iterate the construction of the connected components, this time checking for every iteration if all the
mission's nearest vertices are connected or not. When they're connected, we found the minimum edge length necessary to connect the two; however, we need to compare this with the max dist from the endpoints previously computed, and pick the maximum value between them (if the components are connected but the mission endpoint is not covered, the minimum radius will correspond to the distance between the endpoint and the jammer). 

### Results
```
   Test set 1        (20 pts / 2 s) : Correct answer      (0.025s)
   Test set 2        (20 pts / 2 s) : Correct answer      (0.114s)
   Test set 3        (20 pts / 3 s) : Correct answer      (0.157s)
   Test set 4        (20 pts / 3 s) : Correct answer      (1.735s)
   Hidden test set 1 (05 pts / 2 s) : Correct answer      (0.027s)
   Hidden test set 2 (05 pts / 2 s) : Correct answer      (0.106s)
   Hidden test set 3 (05 pts / 3 s) : Correct answer      (0.152s)
   Hidden test set 4 (05 pts / 3 s) : Correct answer      (1.207s)
```
