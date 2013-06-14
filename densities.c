#ifndef __densities_h__
#include "densities.h"
#endif

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
