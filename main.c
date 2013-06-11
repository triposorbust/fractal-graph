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

void print_graph(int end)
{
  int i,j;
  for (i=0; i<end; i++) {
    printf("%d\t(%5.2f,%5.2f)\t", i, NODES[i].x, NODES[i].y);
    for (j=0; NODES[i].edges[j] != -1; j++)
      printf("%d\t", NODES[i].edges[j]);
    printf("\n");
  }
}

int main(int argc, char **argv)
{
  assert(argc == 2);
  int n_nodes = build_graph(atoi(argv[1]));

  print_graph(n_nodes);

  free_graph();
  return 0;
}
