## London
The script for this problem might seems quite harsh at first sight, and probably the most difficult step is to classify it as a flow problem. In fight, we might notice that this problem, from an algorithmic perspective, is not that much different from [Coin Tossing Tournament](../coin-tossing-tournament/). Even if the statement doesn't explicitly talk about a tournament and players, we can see how it's possible to interpret every char box (containing a character from the front page in
one side and the corresponding character from the back page in the other side) as a "match" and every letter of the alphabet as a "player". In this setting, the score of each player corresponds to the number of times that char appears in the target string. 

Once we have framed the problem in this way, the most difficult part is to deal with characters as integers and be careful with the indices of our vectors. The first solution I coded, that directly comes out of our interpretation of the problem, has a flow graph with a node (connected to the source with capacity 1) for each char box (totally h\*w char boxes) and a node for every letter of the alphabet (26 letters) connected with both the sink (capacity equals to the number of those
characters in the target string) and the the char box nodes (for every char box two connections, one to the char of the front letter and one to the char of the back letter). This solution allows us to achieve the first 60 points, since the flow has a complexity of *O(n^3)* and in the last test set the input size is 10^6 (clearly not feasible).

For the last test set, we need to do another little trick: instead of considering one node for each char box, we might want to group all of the char box which have the same letters in the front and the back (indipendently from the order front-back, e.g. 'AB', 'AB' and 'BA' would all be grouped in the same node). This allows us to greatly reduce the number of nodes in the first "layer" of our flow graph, from 10^6 to a maximum of 350. Therefore, the total cost of the graph will be ~400^3,
which is still good enough to achieve full points.

The code for this exercise was developed quite in a rush and might be not so comprehensible due to an heavy use of magic numbers.

### Results
```
   Test set 1 (10 pts / 2 s) : Correct answer      (0.003s)
   Test set 2 (10 pts / 2 s) : Correct answer      (0.004s)
   Test set 3 (20 pts / 2 s) : Correct answer      (0.008s)
   Test set 4 (20 pts / 2 s) : Correct answer      (0.022s)
   Test set 5 (40 pts / 2 s) : Correct answer      (0.917s)
```
