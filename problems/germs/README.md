## Germs
The situation in this problem is very similar to "Growing disks" from the tutorial session on the week ([slides](https://algolab.inf.ethz.ch/doc/tutorials/tut08_proximity.pdf)). In this case, we are given a relation which define the growing rate of the disks, that depends on a parameter `t`, and we're ask to find three different values of `t` which corresponds to three different critical steps in the evolution of the disks:
- the moment in which the first bacterium dies (i.e. the value of `t` for which the closest disks touch each others - or the closest disk to a border touch it)
- the moment in which the amount of bacteria still alive goes below 50% (i.e. the value for the radius of the disk is greater than the distances of the nearest neighbor of more than an half of the disks)
- the moment in which the last bacterium dies (i.e. the moment in which every disk touches another or the border)

To find all these values, computing the minimum distance from it's nearest neighbor (or from the border) for each disk and then ordering these distance will do the trick. The difficulty in this case it's not really algorithmic, but good luck with implementing it with CGAL.

### Results
```
   Test set 1 (20 pts / 0.600 s) : Correct answer      (0.002s)
   Test set 2 (20 pts / 0.600 s) : Correct answer      (0.059s)
   Test set 3 (30 pts / 0.600 s) : Correct answer      (0.22s)
   Test set 4 (30 pts / 0.600 s) : Correct answer      (0.194s)
```
