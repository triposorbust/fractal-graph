#ifndef __randomwalk_h__
#include "randomwalk.h"
#endif

void random_walk(walk *walks, int end)
{
  int i,j,next_node;
  node anode;

  for (i=0; i<end; ++i) {

    anode = NODES[(*(walks+i)).loc];

    next_node = anode.edges[0];
    for (j=0; anode.edges[j] != -1; ++j)
      next_node = ((rand() % 100) / 100.0) <= (1.0 / (float)j) ? \
        anode.edges[j] : next_node;

    (*(walks+i)).loc = next_node;
    (*(walks+i)).step += 1;
    (*(walks+i)).x = NODES[(*(walks+i)).loc].x;
    (*(walks+i)).y = NODES[(*(walks+i)).loc].y;

  }
}
