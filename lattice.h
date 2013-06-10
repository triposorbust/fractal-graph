#ifndef __lattice_h__
#define __lattice_h__

#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __stdio_h__
#define __stdio_h__
#include <stdio.h>
#endif

#ifndef __stdlib_h__
#define __stdlib_h__
#include <stdlib.h>
#endif

#ifndef __math_h__
#define __math_h__
#include <math.h>
#endif

#define MAX_EDGES 6

void compute_dimensions(int depth, int *n_triangles, int *n_points);
void set_up(int n_triangles, int n_points);
void build_graph(int end);
void print_graph(int end);
void build_lattice(int depth, int n_triangles, int end_idx);
void tear_down(int n_triangles, int n_points);

#endif
