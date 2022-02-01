## Idéfix and the Mansions of the Gods
This problem represents a variation on the theme "Growing Disks". The objective in this case is twofold:
- given a radius `r`, find the largest number a of distinct bones that Idéfix can inspect on a walk through the forest, if he can freely choose start and end point and if his trajectory must be contained in the union of the shadows (i.e. with a fixed radius `r`, find the largest number of bones in a connected component)
- given an integer `k`, find the smallest radius b (instead of r) that the oak trees would need to have such that it becomes possible for Idéfix to inspect at least k bones on a walk through the forest (i.e. find the smallest radius such that it's possible for Idéfix to find `k` bones in a connected component)
These solutions solves only the first of the two problems, that corresponds to achieving half of the total available points. 

To get points from the first two test set, we need to solve the first sub task. To tackle it, a possible solution is to find all the minimum spanning trees in the graph with only edges of length <= `s`, and then check what is the maximum number of bones which are covered by their shadow. Framing the problem as a "Growing disks" instance, we are required to find the maximum number of points which are contained in the area of a connected subset of disks of radius s. Using the
`boost::disjoint_sets_with_storage` as shown in [emst.cpp](https://algolab.inf.ethz.ch/doc/tutorials/sample_code/tut08_emst.cpp) and stopping the merging of different connected components whene the length of the edge to add becomes greater than `s` will do the trick.

For the last two set of points, just add an edge for between every bone and the nearest tree, keep track of the bones of each connected component and re-iterate the construction with the union-find until when a component reach `k` bones.

### Results
```
   Test set 1 (25 pts / 1 s) : Correct answer      (0.018s)
   Test set 2 (25 pts / 1 s) : Correct answer      (0.099s)
   Test set 3 (25 pts / 1 s) : Correct answer      (0.028s)
   Test set 4 (25 pts / 1 s) : Correct answer      (0.272s)
```
