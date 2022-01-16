## H1N1
This problem is not so easy, and definitely requires more attention than many others. The problem that has to be solved is basically "Motion planning" problem presented during the tutorial session. The only given clues is

> Hint: Work with the dual Delaunay triangulation...

which might feel quite generic and vague (spoiler: it is). But it can make sense. Taking a look to the Delauny/Voronoi picture, we can realize that the "best" paths to escape are indeed the Voronoi edges, as they're the points in the plane that are more far from the Delauny vertices (in our setting the infected people). Another important observation is that the most critical parts of these paths actually corresponds to the intersections with Dealauny's edges, as those are the points were
the moving object is closer to the vertices (note also that is exactly in the *middle* of the Delauny's edge). 

We can now explore the possible situations we might end up with. If the person to save is outside the triangulation (i.e. in an infinite face) the only condition that has to be met is that the distance with the closest vertex is at least d. This condition, however, has to be met in every point of the space, and indeed has to be checked for every person. 

The other possible situation is when the person is actually inside a finite triangulation face. In this case, we must derive whether is possible for he/she escape. To do so, it is possible to precompute, for each face of the triangulation, the radius of the maximum circle that can exit from that face. This computation can be done only once for every person to save, as this property doesn't depend on the radius of the person. To do this computation, we can use a prority queue (necessary as we
need to explore the faces in order of "max possible radius that can escape", starting from the infinite faces and then proceding with inner vertices. 

Then, we will just need to check for each person the constraint of minimum initial distance (discussed before), use `locate` method to find the Delauny face that contains the vertex and check if the maximum escape radius from that face is big enough for that person's radius or not.

### Results
```
   Test set 1 (20 pts / 1 s) : Correct answer      (0.003s)
   Test set 2 (20 pts / 1 s) : Correct answer      (0.033s)
   Test set 3 (20 pts / 1 s) : Correct answer      (0.242s)
   Test set 4 (20 pts / 1 s) : Correct answer      (0.406s)
   Test set 5 (20 pts / 1 s) : Correct answer      (0.381s)
```
