#ifndef __randomwalk_h__
#include "randomwalk.h"
#endif

void random_walk(walk *walks, int end)
{
  int i,j,next_node;
  walk awalk;
  node anode;

  for (i=0; i<end; ++i) {

    awalk = walks[i];
    anode = NODES[awalk.loc];

    next_node = anode.edges[0];
    for (j=0; anode.edges[j] != -1; ++j)
      next_node = ((rand() % 100) / 100.0) <= (1.0 / (float)j) ? \
        anode.edges[j] : next_node;

    awalk.loc = next_node;
    awalk.step += 1;
    awalk.x = NODES[awalk.loc].x;
    awalk.y = NODES[awalk.loc].y;

  }
}
