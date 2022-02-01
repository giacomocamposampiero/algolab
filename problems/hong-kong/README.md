## Hong Kong
Solving the first three test sets of this problem actually corresponds to solving [H1N1](../h1n1/), with just a slightly modification for the first test set to take in account the possible initial points which have a large enough clearance on place (easy check on the distance between the Voronoi vertex of the starting point face of each baloon). 

The fourth test case presents, however, a new constraint. In fact, there is no longer a single escape point outside the convex hull of the forest, and the baloon can potentially take off even from points inside the forest. However, adapting the solution we developed so far is not so difficult if we make a very simple observation. To be a good take-off area, the Voronoi vertex of a Delauny face must be at least at a distance `(2*r + 2*s)^2`, where `r` is the tree radius and `s` the baloon
radius. In fact, we must have a minimum of `r+s` free space between the boundaries of the baloon and the boundaries of the the tree.

Now the trick: the required distance for being a valid take-off spot is the same as the required distance to pass between different faces inside the Delauny triangulation. Therefore, we don't need to deal with them separately and both of them define a single unique constraint. Therefore, we just need to add in the pre-processing of the triangulation also clearance of each face in the same way we add infinite faces. Then, when we explore each possible baloon, the value save in the info of
it's corresponding face will therefore correspond to the value of the max clearance spot that can be reached from that face.

This problem is identhical (from an algorithmic perspective) to the test exam **Dean Thomas**.

**Pitfall**
- EPIC kernel use `double` variables as storing point for `K::FT` values. In this case, using EPIC kernel resulted in an overflow error for a single test case in both Testset 2 and 3. EPEC kernel solves the issue.

### Pseudocode for precomputation
```
initialize priority queue which stores pairs <clearance of the face, triangulation face>

for each face of the triangulation

   if face is infinite
      emplace <+inf, face> in the queue
   else 
      emplace <distance between Voronoi vertex (dual of Delauny's face), face> in the queue
   set face -> info() = 0
 
 while the queue is not empty
  
   pop first element of the queue (maximum escape distance)
   
   if popped clearance < face -> info(), continue
   fface -> info() = clearance
   
   for every neighboring face
      
      if neighboring face is infinite or face -> info() is already set, continue
      compute the length of the edge which is shared by the two faces
      emplace <minimum(edge length, face clearance), neighboring face> in the queue
```

### Results
```
   Test set 1 (30 pts / 2 s) : Correct answer      (1.082s)
   Test set 2 (30 pts / 2 s) : Correct answer      (0.533s)
   Test set 3 (20 pts / 2 s) : Correct answer      (0.836s)
   Test set 4 (20 pts / 2 s) : Correct answer      (1.071s)
```
