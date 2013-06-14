#ifndef __randomwalk_h__
#include "randomwalk.h"
#endif

void random_walk(walk *walks, int end)
{
  int i,j,p;
  walk awalk;
  node anode;

  for (i=0; i<end; ++i) {

    awalk = walks[i];
    anode = NODES[awalk.loc];

    for (j=0; anode.edges[j] != -1; ++j) {
      ; // Do the probability thing.
    }

    ; // Do some other stuff.

  }

  return;
}
