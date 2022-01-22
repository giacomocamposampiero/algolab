## Light the Stage
Yet another triangulation problem. In this case, however, it might not be clear what are the entities that must define the triangulation and what those who must be checked against it. We can observe that the ray of the people is variable, whereas the ray for the lights is fixed (and equal to the height of the light, as we can easily prove with some simple math). This should suggest us that maybe considering the lights for the triangulation is a good idea. Indeed, it is. 

For archieving the first 60 points (first three test sets) we just need to check if the distance of every person is greater or equal to the sum of the two rays. If it is, we print the index of the person; if it isn't, we continue iterating over the remaining people. Since we are guaranteed that at least one person will survive till the end, we can just forget about the order in which lights are turned on.

The last two test sets require a little more reasoning. In fact, in this case the latter assumption is no longer valid, and the order in which lights are turned on becomes actually really important. In fact, if we checked every person against all the lights, there might be a winner which win at some round `i` but that would have been eliminated by one of the lights `>i`. A possible solution (might not be the most efficient, but still pass all the tests) using binary search to find the
number of rounds required to have a winner in the game. Since constructing the triangulation requires a complexity *O(nlogn)*, we would end up with a complexity *O(logn\*nlogn)*, which is still good considered the given input size.

**Update** For an efficient solution, which runs within the time limit even without checking the last combination first, we need to construct the triangulation only with the sub-range of lights considered in the binary search. Indeed, it's also necessary to reformulate the solution a little bit.

### Results
```
   Test set 1 (20 pts / 2.500 s) : Correct answer      (0.189s)
   Test set 2 (20 pts / 2.500 s) : Correct answer      (1.026s)
   Test set 3 (20 pts / 2.500 s) : Correct answer      (1.103s)
   Test set 4 (20 pts / 2.500 s) : Correct answer      (1.247s)
   Test set 5 (20 pts / 2.500 s) : Correct answer      (1.058s)
```
