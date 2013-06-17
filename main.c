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


void print_graph(char *prefix, int n_nodes)
{
  int i,j;

  char filename[BUFFER_SIZE];
  sprintf(filename, "%s-graph.output", prefix);
  FILE *file = fopen(filename, "w");

  for (i=0; i<n_nodes; i++) {
    fprintf(file, "%d\t(%5.2f,%5.2f)\t", i, NODES[i].x, NODES[i].y);
    for (j=0; NODES[i].edges[j] != -1; j++)
      fprintf(file, "%d\t", NODES[i].edges[j]);
    fprintf(file, "\n");
  }

  fclose(file);
}


void get_datetime_string(char *s, int max_chars)
{
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(s, max_chars, "%Y-%m-%d-%H%M", timeinfo);
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


void initialize_files(walk *walks, FILE **files, int n_files, char *prefix)
{
  int i;
  char filename[BUFFER_SIZE];
  for (i=0; i<n_files; ++i) {
    sprintf(filename, "%s-%d.output", prefix, i);
    files[i] = fopen(filename, "w");

    if (files[i] == NULL) {
      printf("Failed to open output file: %s", filename);
      exit(0);
    }

    fprintf(files[i], "# random walk index: %d\n", walks[i].index);
    fprintf(files[i], "# initial position: %d\n", walks[i].loc);
  }
}


int main(int argc, char **argv)
{
  srand(time(NULL));
  void **options = (void **) malloc(N_OPTIONS * sizeof(void *));
  parse_options(&argc, argv, options);

  int i, j, n_nodes, n_walks, n_steps;
  char datetime[BUFFER_SIZE], prefix[BUFFER_SIZE];

  get_datetime_string(datetime, BUFFER_SIZE);
  sprintf(prefix, "%s/%s", (char *) options[OPTION_OUTPUT], datetime);

  n_nodes = build_graph(*(int *)options[OPTION_DEPTH]);
  n_walks = *(int *)options[OPTION_NUMBER];
  n_steps = *(int *)options[OPTION_STEPS];

  walk *walks = (walk *) malloc(n_walks * sizeof(walk));
  FILE **files = (FILE **) malloc(n_walks * sizeof(FILE *));

  initialize_walks(walks, n_walks, n_nodes);
  initialize_files(walks, files, n_walks, prefix);
  print_graph(prefix, n_nodes);

  for (i=0; i<n_steps; ++i) {
    for (j=0; j<n_walks; ++j)
      fprintf(files[j], "%f\t%f\n", walks[j].x, walks[j].y);
    random_walk(walks, n_walks);
  }

  for (i=0; i<n_walks; ++i)
    fclose(files[i]);
  free(walks);

  free_graph();
  free(options);

  return 0;
}
