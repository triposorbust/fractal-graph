#ifndef __options_h__
#include "options.h"
#endif

typedef struct Specification {
  char letter;
  char *expanded;
  char *help;
} spec;

void print_help(spec *specs)
{
  int i;
  printf("\nProgram for executing random walk on a lattice. Options:\n\n");
  for (i=0; i<N_OPTIONS; i++) {
    printf("-%c\t--%s  \t%s\n",
           specs[i].letter,
           specs[i].expanded,
           specs[i].help);
  }
  printf("\nHow you use it is up to you!\n\n");
  return;
}

void build_options(spec *specs)
{
  specs[OPTION_DEPTH].letter = 'd';
  specs[OPTION_DEPTH].expanded = "depth";
  specs[OPTION_DEPTH].help = "Recursion depth for lattice. (dflt: 3)";

  specs[OPTION_STEPS].letter = 's';
  specs[OPTION_STEPS].expanded = "steps";
  specs[OPTION_STEPS].help = "Number of steps in random walk. (dflt: 100)";

  specs[OPTION_COUNT].letter = 'c';
  specs[OPTION_COUNT].expanded = "count";
  specs[OPTION_COUNT].help = "Number of time series to generate. (dflt: 4)";

  specs[OPTION_OUTPUT].letter = 'o';
  specs[OPTION_OUTPUT].expanded = "output";
  specs[OPTION_OUTPUT].help = "Directory for output files. (dflt: \"output\")";

  specs[OPTION_HELP].letter = 'h';
  specs[OPTION_HELP].expanded = "help";
  specs[OPTION_HELP].help = "Prints the help menu to stdout and exits.";
}

void parse_options(int *argc, char **argv)
{
  int i;
  spec *specs = (spec *) malloc(N_OPTIONS * sizeof(spec));
  build_options(specs);

  if (*argc == 1) {
    print_help(specs);
    exit(0);
  }

  for (i=1; i<*argc; i++) {
    printf("Processing argument: %s\n", argv[i]);
  }

  free(specs);
  return;
}
