#ifndef __densities_h__
#define __densities_h__

#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __stdlib_h__
#define __stdlib_h__
#include <stdlib.h>
#endif

#ifndef __assert_h__
#define __assert_h__
#include <assert.h>
#endif

void compute_densities(double *densities, int n_nodes, int steps, int number);

#endif
