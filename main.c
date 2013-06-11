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
  int n_nodes = build_graph(atoi(argv[1]), 1);
  return 0;
}
