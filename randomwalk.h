#ifndef __randomwalk_h__
#define __randomwalk_h__

#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __stdlib_h__
#define __stdlib_h__
#include <stdlib.h>
#endif

#ifndef __time_h__
#define __time_h__
#include <time.h>
#endif

typedef struct Walk{
  int index;
  double x,y;
  int step;
  int loc;
} walk;

void random_walk(walk *walks, int end);

#endif
