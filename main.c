#ifndef __graph_h__
#include "graph.h"
#endif

#ifndef __lattice_h__
#include "lattice.h"
#endif

#ifndef __densities_h__
#include "densities.h"
#endif

#ifndef __randomwalk_h__
#include "randomwalk.h"
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


#define BUFFER_SIZE 300


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


void initialize_walks(walk *walks, int n_walks, int n_nodes)
{
  int i;
  for (i=0; i<n_walks; i++) {
    (walks+i)->index = i;
    (walks+i)->step = 0;
    (walks+i)->loc = rand() % n_nodes;
    (walks+i)->x = NODES[walks[i].loc].x;
    (walks+i)->y = NODES[walks[i].loc].y;
  }
}


int main(int argc, char **argv)
{
  void **options = (void **) malloc(N_OPTIONS * sizeof(void *));
  parse_options(&argc, argv, options);
  srand(time(NULL));

  int n_nodes = build_graph(*(int *)options[OPTION_DEPTH]);
  int n_walks = *(int *)options[OPTION_NUMBER];
  int n_steps = *(int *)options[OPTION_STEPS];

  int i,j;
  walk *walks = (walk *) malloc(n_walks * sizeof(walk));
  initialize_walks(walks, n_walks, n_nodes);

  time_t rawtime;
  struct tm *timeinfo;
  char datetime[BUFFER_SIZE];
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(datetime, BUFFER_SIZE, "%C-%m-%d-%H%M", timeinfo);

  FILE **files = (FILE **) malloc(n_walks * sizeof(FILE *));
  char filename[BUFFER_SIZE];
  for (i=0; i<n_walks; ++i) {
    sprintf(filename, "%s/%s-%d.output",
            (char *) options[OPTION_OUTPUT],
            datetime,
            i);
    files[i] = fopen(filename, "w");

    fprintf(files[i], "# random walk index: %d\n", walks[i].index);
    fprintf(files[i], "# initial position: %d\n", walks[i].loc);
    fprintf(files[i], "%d\t%f\t%f\n", walks[i].loc, walks[i].x, walks[i].y);

    if (files[i] == NULL) {
      printf("Failed to open output file: %s", filename);
      exit(0);
    }
  }

  for (i=0; i<n_steps; ++i) {
    random_walk(walks, n_walks);
    for (j=0; j<n_walks; ++j)
      fprintf(files[j], "%d\t%f\t%f\n", walks[j].loc, walks[j].x, walks[j].y);
  }

  for (i=0; i<n_walks; ++i)
    fclose(files[i]);
  free(walks);

  free_graph();
  free(options);

  return 0;
}
