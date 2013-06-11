#ifndef __options_h__
#include "options.h"
#endif

void print_help(void)
{
  printf("This is a thingie!\n");
}

void parse_options(int *argc, int **argv)
{
  if (*argc == 1) {
    print_help();
    exit(0);
  }
}
