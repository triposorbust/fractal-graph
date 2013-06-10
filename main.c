#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __lattice_h__
#include "lattice.h"
#endif

#ifndef __stdio_h__
#define __stdio_h__
#include <stdio.h>
#endif

#ifndef __stdlib_h__
#define __stdlib_h__
#include <stdlib.h>
#endif

#ifndef __assert_h__
#define __assert_h__
#include <assert.h>
#endif

int main(int argc, char **argv)
{
  assert(argc == 2);

  int depth = atoi(argv[1]), n_triangles, n_points;
  compute_dimensions(depth, &n_triangles, &n_points);
  set_up(n_triangles, n_points);

  build_lattice(depth, n_triangles, 1);
  build_graph(n_triangles);

  print_graph(n_points);
  tear_down(n_triangles, n_points);

  return 0;
}
