#ifndef __lattice_h__
#include "lattice.h"
#endif

typedef struct Triangle { int a,b,c; } triangle;
triangle *LATTICE;

void compute_dimensions(int depth, int *n_triangles, int *n_points)
{
  int i, temp=1;
  *n_points = 3;
  for (i=1; i<=depth; i++)
    *n_points += temp *= 3;
  *n_triangles = pow(3, depth);
}

int new_node(double x, double y)
{
  static int index = 0;

  NODES[index].x = x;
  NODES[index].y = y;

  return index++;
}

void set_up(int n_triangles, int n_points)
{
  int i,j;

  LATTICE = (triangle *) malloc(n_triangles * sizeof(triangle));
  NODES = (node *) malloc(n_points * sizeof(node));

  for (i=0; i<n_points; i++) {
    NODES[i].edges = (int *) malloc(MAX_EDGES * sizeof(int));
    for (j=0; j<MAX_EDGES; j++)
      NODES[i].edges[j] = -1;
  }

  LATTICE[0].a = new_node( 0.0,   1.0);
  LATTICE[0].b = new_node( 0.866, 0.5);
  LATTICE[0].c = new_node(-0.866, 0.5);
}

void add_edge(int src, int dest)
{
  int j=0,k=0;

  while (NODES[src].edges[j] != -1) j++;
  while (NODES[dest].edges[k] != -1) k++;

  NODES[src].edges[j] = dest;
  NODES[dest].edges[k] = src;
}

void read_lattice(int end)
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

void set_triangle(triangle *lattice, int i, int *corners)
{
  lattice[i].a = corners[0];
  lattice[i].b = corners[1];
  lattice[i].c = corners[2];
}

int node_between(int a_idx, int b_idx)
{
  double mx,my;
  mx = (NODES[a_idx].x + NODES[b_idx].x)/2.0;
  my = (NODES[a_idx].y + NODES[b_idx].y)/2.0;
  return new_node(mx, my);
}

void build_inner_triangles(triangle outer, int outer_idx, triangle* nlattice)
{
  int ab = node_between(outer.a, outer.b);
  int ac = node_between(outer.a, outer.c);
  int bc = node_between(outer.b, outer.c);

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
    free(NODES[i].edges);
  free(NODES);
}

int build_graph(int depth, int print_flag)
{
  int n_triangles, n_points;
  compute_dimensions(depth, &n_triangles, &n_points);
  set_up(n_triangles, n_points);

  build_lattice(depth, n_triangles, 1);
  read_lattice(n_triangles);

  if (print_flag) print_graph(n_points);
  tear_down(n_triangles, n_points);

  return n_points;
}
