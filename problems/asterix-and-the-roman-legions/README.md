## Asterix and the Roman Legion
This problem is very related to [Inball](../inball/). In fact, we can easily by simply drawing the situation that the setting is more or less the same: we need to find a position inside the convex hull define by the legions (lines) such that the distance from these lines is maximized. However, there are some minor details which make them different problems. 

Firstly, we have that the optimal position is no longer contained in a particular half-plane as it was for Inball. In this case, we will need to find out in which half-plane the position lies with respect to a specific line, and then optimized the distance accordingly. Moreover, in this case legions have different speeds, and therefore we might have to considered different radius for different lines.

For what concerns the first point, we can observe that the relative position can be derived from the sign of the signed distance. From this, we can then modify the constraint which encodes the maximum distance from the lines of the optimal position accordingly. For what concern the speed, we can observe that, if the given legion has speed `v`, the distance from that line will have to be `v` times bigger than the distance from the "regular" legion with unitary speed. Therefore, it will
be enough to multiply the radius variable for the speed, and the issue is solved.

### Results
```
   Test set 1 (25 pts / 3 s) : Correct answer      (0.038s)
   Test set 2 (25 pts / 3 s) : Correct answer      (0.106s)
   Test set 3 (25 pts / 3 s) : Correct answer      (1.472s)
   Test set 4 (25 pts / 3 s) : Correct answer      (1.65s)
```
