## Planet Express
In this problem we are required to find the shortest path between a target node and a source node in a set of possible sources. The situation is further complicated by the presence of the teleport network, that is not so easy to model at first sight (it's also not trivial to understand how it works, make sure to have a look at the provided input examples). 

First of all, we want to analyse the teleport network. A naive algorithm to deal with it could compute shortest paths between all the teleport planets (to find whether they're connected or not) and then add teleport shortcuts accordingly. However, we soon realize this is not a valid approach, with a complexity of *O(n^2\*logn+n\*m)* (definitely bad given the input sizes). In fact, we don't really need to get distances between teleport planets to build the teleport network, we just
need to know whether they're connected with each other or not: in other words, each teleport "cluster" must be strongly connected! Since we realize this, the implementation is rather easy, using the BOOST method `strong_components` that was also presented in the [tutorial session](https://algolab.inf.ethz.ch/doc/tutorials/tut04_bglintro.pdf). 

The last piece of information we miss about the teleport network is about the complexity in terms of edge number. If we go for a naive implementation, where we connect each teleport node to the others in the same strongly connected component, we might end up with a n^2 number of nodes. If we want to use Dijkstra algorithm for finding shortest paths in the graph later on, this might cause some troubles. One easy fix to this problem is adding a new node for each strongly connected component, and
connecting every teleport node to it; the number of additional edges is now linear again in the number of teleport planets (at most 2n). 

The total complexity of teleport network build is ~*O(n+m)*, good for our inputs! 

We now have a graph with all the possible paths in the network and we just need to find the minimum distance between the target planet (fixed position) and a set of warehouses. Computing shortest paths from every warehouse to the target planet is again infeasible, as the number of warehouses can be up to n, and this would again lead to a quadratic (*O(n^2\*logn+n\*m)* precisely) complexity. Since the graph is directed, we cannot simply apply Dijkstra from the target. But here's the
trick: we just need to create a new graph where all edges are flipped (edge (u,v) becomes (v,u) in the inverse graph, for every edge) and apply Dijkstra to it.

### Results
```
   Test set 1        (20 pts / 1.000 s) : Correct answer      (0.054s)
   Hidden test set 1 (05 pts / 1.000 s) : Correct answer      (0.054s)
   Test set 2        (20 pts / 1.000 s) : Correct answer      (0.336s)
   Hidden test set 2 (05 pts / 1.000 s) : Correct answer      (0.336s)
   Test set 3        (20 pts / 1.000 s) : Correct answer      (0.546s)
   Hidden test set 3 (05 pts / 1.000 s) : Correct answer      (0.546s)
   Test set 4        (20 pts / 1.000 s) : Correct answer      (0.551s)
   Hidden test set 4 (05 pts / 1.500 s) : Correct answer      (0.551s)
```
