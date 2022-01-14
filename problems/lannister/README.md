## Lannister (aka Casterly Rock)
Lannister is a typical LP problem: not difficult because of LP, but tricky from a geometric point of view. The problem script, to outline it in few words, provides us two contraints (Cersei’s constraint on the position of the houses and Tywin’s constraint on the maximum sum of the distances between the housese and the sewage canal) and a quantity to minimize (the maximum distance between all the length of fresh water pipes). Before getting started, we need to define our variables: in this case,
we will use `a`, `b` and `c`, the three coefficients that together define the equation of the sewage canal `ax+by+c=0`.

The first test set can be solved by just adapting the linear separability code we've seen during the tutorial. In fact, we just need to check whether there is a valid line that exactly separates nobles' houses from commons' houses, keeping nobles' houses on the left of the sewage. So far, so good.

From the second test set, I directly went for the full point score. The first thing we need to add to the 25 pts solution is the Tywin’s constraint. This is however rather easy: we know from how we created the linear separation that all NH (nobles' houses) are on the left, and all CH (commons' houses) are on the right. We are then able to derive from the sewage canal equation the distance between it and each house, for both NH and CH. Summing the two together and imposing the Tywin’s
constraint, we end up with the corresponding LP constraint:

![](https://latex.codecogs.com/svg.image?{a&space;\cdot&space;\left&space;(&space;&space;\sum_{commons}^{}x_{house}-\sum_{nobles}^{}x_{house}-s&space;\right&space;)&space;&plus;&space;b&space;\cdot&space;\left&space;(&space;\sum_{commons}^{}y_{house}&space;-&space;\sum_{nobles}^{}&space;y_{house}&space;\right&space;)&space;&plus;&space;c&space;\cdot&space;(m&space;-&space;n)&space;\leq&space;0})

Once we defined Tywin's constraint, it's time to actually think about the fresh water pipe. In fact, our optimization has to be done over the maximum-length fresh water pipe in order to minimize its length. The fresh water pipe needs to be perpendicular to the sewage pipe, and this means that its defining equation will be somethin like `dx+ey+f=0` where perpendicularity condition `ad + be = 1` must hold. We soon realize that it's impossible to code this condition with a linear constraint.
But don't worry, there's the trick!

However, to get it we need to make a step back, and analyse our objective function. In fact, we need to maximize the longest fresh water pipe. How do we get the longest? LP trick: we just need to define a new variable s.t. the variable is >= than every water pipe length given. But how do we find the lengths of the fresh water pipes in the first intance? Well, for the fresh water pipes we no longer know the exact location of each house with respect to the fresh water canal. However, we can
observe that the length of the water pipes corresponds to the norm of the distance between the house and the canal (that is the difference of `y`'s cordinates, since the pipe must be vertical). Observe that we can now transform this in two equivalent linear constraints

![](https://latex.codecogs.com/svg.image?{}\left|&space;y_{house}&space;-&space;y_{canal}&space;\right|&space;<&space;l_{max}&space;\quad&space;\Rightarrow&space;\quad&space;-l&space;\leq&space;&space;y_{house}&space;-&space;y_{canal}&space;\leq&space;l_{max})

Now we just need the last piece of the puzzle. So far, we have the constraints that define `l_max` in terms of `y`s, but we still don't know what those `y`s are. In fact, we're still stuck with the perpendicularity problem. Let's observe better however what the `y` of the canal really is. It can be defined as

![](https://latex.codecogs.com/svg.image?{y_{canal}&space;=&space;\frac{-d&space;\cdot&space;x_{house}-f}{e}&space;=&space;b&space;\cdot&space;h_{house}&space;-&space;f})

If we set one of the sewage coefficient (`a` in this case) to 1! Note that we don't lose any generality with this definition, as `b` and `c` still guarantee to obtain all the possible lines in our setting. And now we're done! Perpendicularity is encoded directly with our choice of coefficients and we just need to update the constraints on the norm of the distance to get our final formulation of the problem. 

**Pitfalls of the problem and take-home messages**:
- `typedef long IT;`, if you don't wanna lose hours debugging and wondering why your solution which has no faults from a theorical perspective still doesn't pass that single test case in test set 2 
- be careful with the sign of the equations for linear separation; however, since the possible combinations are limited, if you're stuck just try them all
- keep track of constraint indices using a dedicated variable, definitely more handy

### Results
```
   Test set 1 (25 pts / 2 s) : Correct answer      (0.141s)
   Test set 2 (25 pts / 2 s) : Correct answer      (0.699s)
   Test set 3 (25 pts / 2 s) : Correct answer      (0.375s)
   Test set 4 (25 pts / 2 s) : Correct answer      (0.531s)
```
