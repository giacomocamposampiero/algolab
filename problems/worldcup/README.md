## Worldcup
In this problem, we are required to find the maximum profit achievable with some constraints. In this case, I think it's convenient to approach the problem solving subtasks - firstly the first and the second test sets, then the other two. In fact, the solution is quite "incremental" and the two groups of test sets aim to solve to different type of problems (optimization for the first one, geometric for the second group).

To tackle the first 50 points, we observe that the problem can be framed as an LP problem. Min cost max flow has to be discarded in this case due to the fact that there are too many variables to be handled with only capacities and costs (alcool, revenues and supply constraints). Moreover, input sizes are appropriate and we shouldn't have any time limit problem.
The variables in this case can be defined to represent the litres delivered from a warehouse `i` to a stadium `j`, and indeed we will have `n*m` variables in our problem. For every stadium, we need to define three constraint: two to encode the demand (sum of incoming beer from all the warehouses must be <= and >= to the specific demand, as the quantity must be exactly that one defined) and one to encode the maximum amount of alcool sold in the stadium. 
For every warehouse, we just need to define one constraint on the outgoing quantity of beer, which must be lower than the maximum availability of beer for that warehouse. 
Finally, the objective function can be define as the (negative, as we have to maximize it) sum of revenues times the quantity of beer delivered for each pair (warehouse, stadium).

For the last two sets, we need to take in account the contourn lines constraints. Observe that the number of contourn lines can be huge (10^6) but that only a small fraction of them (10^2) actually contains a stadium or a warehouse. Because of this, we can select the subset of contourn lines which actually contains the warehouses and the stadiums, as they're the only ones which must be traversed eventually to move from different locations. A fast way to check this condition is using a
triangulation (a location is contained in a contour line iif the distance from it's center is lower than the radius). Then, when we just need to update the definition of the objective function computing the number of crossed contourn lines for each pair and adding the related *malus* to the objective. To do so, we can just check the relative position of the two locations of the pair (stadium, warehouse) w.r.t. the center of the contourn. If both are inside or outside, the road
connecting them won't cross this line, otherwise it will. 

### Results
```
   Test set 1 (25 pts / 4 s) : Correct answer      (0.094s)
   Test set 2 (25 pts / 4 s) : Correct answer      (0.24s)
   Test set 3 (25 pts / 4 s) : Correct answer      (0.256s)
   Test set 4 (25 pts / 4 s) : Correct answer      (1.509s)
```
