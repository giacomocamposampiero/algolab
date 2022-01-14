## Suez
In this problem, we are required to maximize the sum of the perimeters of a set of rectangles without having any overlap between them. The maximization is possible as the dimensions of a subset of these rectangles can be stretched by a (continuos) factor `a`, which can be chosen individually for each rectangle. Even in this problem, the difficulty lays in correctly interpret the problem from a geometric perspective.

We can observe that in this problem the variables are the `n` streching factors, whereas the constraints are defined by the distances between the neighboring rectangles. These distances can be vertical, orizontal or diagonal. The latter is not really necessary, as we're dealing with rectangles and only one of the first two will be meaningful. The solution for this problem is actually incremental (as many LP problem solution are) and indeed we will tackle one test at a time.

For the first test set, the number of dimensions that define the constraint is limited to one (and there are no pre-existing rectangles). We therefore need to set constraints only between new rectangles' x position. A smart way to do it is to order rectangles on they're x coordinates and then do an iteration to set the constraint between the i-th rectangle and the (i-1)-th. The objective function is defined by the sum of the perimeters of the new triangles (for this test set and
for the other as well).

For the second test set, we have to take in account the y-dimension, and we therefore need to modify the constraint previously defined. In fact, with two dimensions we need, for each pair of rectangle, to specify a constraint on the greatest of the x-based and y-based distances (as it's the most important one). Consider for example the first sample from the given input sample. In this case, the rectangles share pairwise a common coordinate, and if we picked the minimum difference we
would end up having constraints <= 0, which is not correct (this is not a formal proof, just to give an intuition of why we're considering the maximum difference).

For the last two test sets, we have to deal with already placed rectangles, which cannot be scaled. Observe than that we don't need any variable for them, and they will just contribute to the formulation of the problem with additional constraints. As a first attempt, we could think to do the same we did for new rectangles, that is specifying a new constraint for each pair of (old, new) rectangles. However, due to the size of the old rectangle set, we would end up time limiting the
last set. To achieve full score, we need to observe that we don't actually need to set a constraint for each pair (~10^4 constraints, way too much), because this number can be made linear in the number of new rectangles by just setting a constraint with the *closer* old rectangle. 

### Results
```
   Test set 1        (20 pts / 1.500 s) : Correct answer      (0.14s)
   Test set 2        (20 pts / 1.500 s) : Correct answer      (0.402s)
   Test set 3        (20 pts / 1.500 s) : Correct answer      (0.736s)
   Test set 4        (20 pts / 1.500 s) : Correct answer      (1.038s)
   Hidden test set 1 (05 pts / 1.500 s) : Correct answer      (0.62s)
   Hidden test set 2 (05 pts / 1.500 s) : Correct answer      (0.802s)
   Hidden test set 3 (05 pts / 1.500 s) : Correct answer      (0.869s)
   Hidden test set 4 (05 pts / 1.500 s) : Correct answer      (1.302s)
```
