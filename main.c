#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_EDGES 6
typedef struct Triangle { int a,b,c; } triangle;

triangle *LATTICE;
int **NODES;
int NEXT_NODE = 0;

void compute_dimensions(int depth, int *n_triangles, int *n_points)
{
  int i, temp=1;
  *n_points = 3;
  for (i=1; i<=depth; i++)
    *n_points += temp *= 3;
  *n_triangles = pow(3, depth);
}

void set_up(int n_triangles, int n_points)
{
  int i,j;

  LATTICE = (triangle *) malloc(n_triangles * sizeof(triangle));
  NODES = (int **) malloc(n_points * sizeof(int *));

  for (i=0; i<n_points; i++) {
    NODES[i] = (int *) malloc(MAX_EDGES * sizeof(int));
    for (j=0; j<MAX_EDGES; j++)
      NODES[i][j] = -1;
  }

  LATTICE[0].a = 0;
  LATTICE[0].b = 1;
  LATTICE[0].c = 2;
  NEXT_NODE = 3;
}

void add_edge(int src, int dest)
{
  int j=0,k=0;

  while (NODES[src][j] != -1) j++;
  while (NODES[dest][k] != -1) k++;

  NODES[src][j] = dest;
  NODES[dest][k] = src;
}

void build_graph(int end)
{
  int i,a,b,c;
  for (i=0; i<end; i++) {
    a = LATTICE[i].a;
    b = LATTICE[i].b;
    c = LATTICE[i].c;

    add_edge(a,b);
    add_edge(a,c);
    add_edge(b,c);
  }
}

void print_graph(void)
{
  int i,j;
  for (i=0; i<NEXT_NODE; i++) {
    printf("%d: ", i);
    for (j=0; NODES[i][j] != -1; j++)
      printf("%d ", NODES[i][j]);
    printf("\n");
  }
}

void set_triangle(triangle *lattice, int i, int *corners)
{
  lattice[i].a = corners[0];
  lattice[i].b = corners[1];
  lattice[i].c = corners[2];
}

void build_inner_triangles(triangle outer, int outer_idx, triangle* nlattice)
{
  int ab = NEXT_NODE;
  int ac = NEXT_NODE + 1;
  int bc = NEXT_NODE + 2;
  NEXT_NODE += 3;

  int spec_a[3] = { outer.a, ab, ac };
  int spec_b[3] = { ab, outer.b, bc };
  int spec_c[3] = { ac, bc, outer.c };

  set_triangle(nlattice, outer_idx*3 + 0, spec_a);
  set_triangle(nlattice, outer_idx*3 + 1, spec_b);
  set_triangle(nlattice, outer_idx*3 + 2, spec_c);
}

void build_lattice(int depth, int n_triangles, int end_idx)
{
  if (depth == 0)
    return;

  int i=0;
  triangle *nlattice = (triangle *) malloc(n_triangles * sizeof(triangle));
  for (i=0; i<end_idx; i++)
    build_inner_triangles(LATTICE[i], i, nlattice);

  free(LATTICE);
  LATTICE = nlattice;

  build_lattice(depth-1, n_triangles, 3*end_idx);
}

void tear_down(int n_triangles, int n_points)
{
  int i;

  free(LATTICE);
  for (i=0; i<n_points; i++)
    free(NODES[i]);
  free(NODES);
}

int main(int argc, char **argv)
{
  assert(argc == 2);

  int depth = atoi(argv[1]), n_triangles, n_points;
  compute_dimensions(depth, &n_triangles, &n_points);
  set_up(n_triangles, n_points);

  build_lattice(depth, n_triangles, 1);
  build_graph(n_triangles);

  print_graph();
  tear_down(n_triangles, n_points);

  return 0;
}
