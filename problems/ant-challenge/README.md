## Ant Challenge
In this problem we are essentially required to find the minimum path between two nodes of the graph. However, the definition of this graph is a little tricky. In fact, we're not dealing with a single graph, but virtually with `s` different graphs (where `s` is the number of bug species living in the forest). This happens because every edge has a different crossing cost for every different species, even if the edges are identical.

Moreover, the network of every species doesn't cover the whole forest, but it's defined as follows:
> The private network of each species was established years ago during the exploration of the forest: starting from its hive located at a particular tree, each species explored new trees one at a time. The next tree to be explored was always the one fastest to be reached from the already explored territory (you may assume that every edge has a unique travel time for every species, in particular, the next tree to be explored is unique). The private network of every species covers all trees of the forest and consists of all edges that were used during this species’ exploration of the forest.

The trick here is to observe that, since the next tree to be explored is unique, this generation process always ends up with the minimum spanning tree over the network (for the species' specific edge weights). Therefore, we just need to apply Kruskal's algorithm to every species' complete forest to get its private network.

Finally, we can use the edges of the MST of every species to create a new graph and then apply Dijkstra algorithm to find the best path between the given start and end nodes (for every pair of nodes in the graph which are connected by more than one edge - i.e. the edge is covered by more than one private network - Dijkstra will choose the cheapest one).

### Results
```
   Test set 1 (20 pts / 1 s) : Correct answer      (0.008s)
   Test set 2 (20 pts / 1 s) : Correct answer      (0.049s)
   Test set 3 (20 pts / 1 s) : Correct answer      (0.026s)
   Test set 4 (40 pts / 1 s) : Correct answer      (0.169s)
```
