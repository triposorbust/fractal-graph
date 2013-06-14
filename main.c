#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __lattice_h__
#include "lattice.h"
#endif

#ifndef __densities_h__
#include "densities.h"
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


int main(int argc, char **argv)
{
  void **options = (void **) malloc(N_OPTIONS * sizeof(void *));
  parse_options(&argc, argv, options);
  srand(time(NULL));

  int n_nodes = build_graph(*(int *)options[OPTION_DEPTH]);

  if (0) { /* deprecated density functions */
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
