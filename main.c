#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __lattice_h__
#include "lattice.h"
#endif

#ifndef __options_h__
#include "options.h"
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

#ifndef __time_h__
#define __time_h__
#include <time.h>
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

void distribute_densities(int n_nodes, double *densities, node *nodes)
{
  int i,j,n_edges;
  double amount;
  double *udensities = (double *) malloc(n_nodes * sizeof(double));

  for (i=0; i<n_nodes; i++)
    udensities[i] = 0.0;

  for (n_edges=0, i=0; i<n_nodes; i++) {
    while (nodes[i].edges[n_edges] != -1) n_edges++;

    amount = densities[i] / (float) n_edges;
    for (j=0; j<n_edges; j++)
      udensities[ nodes[i].edges[j] ] += amount;
  }

  for (i=0; i<n_nodes; i++)
    densities[i] = udensities[i];

  free(udensities);
  return;
}

void compute_densities(double *densities, int n_nodes, int steps, int number)
{

  int i, step, temp;

  for (i=0; i<n_nodes; i++)
    densities[i] = 0.0;

  assert(number <= n_nodes);
  for (i=0; i<number; i++) {
    temp = rand()%n_nodes;
    if (densities[temp] == 1.0) {
      i--;
      continue;
    }
    densities[temp] = 1.0;
  }

  for (step=0; step<steps; step++)
    distribute_densities(n_nodes, densities, NODES);

  return;

}

int main(int argc, char **argv)
{
  void **options = (void **) malloc(N_OPTIONS * sizeof(void *));
  parse_options(&argc, argv, options);
  srand(time(NULL));

  int n_nodes = build_graph(*(int *)options[OPTION_DEPTH]);

  if (0) {
    double *densities = (double *) malloc(n_nodes * sizeof(double));
    compute_densities(densities,
                      n_nodes,
                      *(int *)options[OPTION_STEPS],
                      *(int *)options[OPTION_NUMBER]);
    free(densities);
  }

  free_graph();
  free(options);

  return 0;
}
