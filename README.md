Random Walk on a Triangular Lattice
===================================
Transition paths on a [Sierpinski Gasket][1]...
-----------------------------------------------


### Introduction


Written for S.M. Ali Tabei for studies on random-walks. A quick program to:


 - Generate a triangular lattice graph
 - Layout the graph in Cartesian space
 - Execute a random walk on the graph


In principle, some of these components can be generalized to other kinds of lattices.


### Quick Start


```
t2ahc $ make
t2ahc $ ./randomwalk [options]
```


### Help


```
t2ahc $ ./randomwalk -h

Program for executing random walk on a lattice. Options:

-h		Prints the help menu to stdout and exits.
-s		Number of steps in random walk time series (dflt: 100)
-n		Number of time series to generate. (dflt: 4)
-o		Directory for writing output files. (dflt: "output")
-d		Recursion depth for lattice generation. (dflt: 3)

How you use it is up to you!

```


### Plotting


Package by default outputs to the `output` subdirectory. This can be changed by using the `-o` option. The default output directory includes a [matplotlib][2] script for printing a `.png` of a given random walk.


To plot, simply:

```
t2ahc $ python plot.py <some-graph.output> <some-random-walk.output>
```


Or for more information:

```
t2ahc $ python plot.py -h
```



### What you do with this...


... is up to you!





[1]: http://en.wikipedia.org/wiki/Sierpinski_triangle
[2]: http://matplotlib.org/