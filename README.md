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


### What you do with this...


... is up to you!





[1]: http://en.wikipedia.org/wiki/Sierpinski_triangle