#ifndef __options_h__
#include "options.h"
#endif

#define BUFFER_SIZE 200
const char LETTERS[] = { 'h', 's', 'n', 'o', 'd' };
const char *DESCRIPTIONS[] = {
  "Prints the help menu to stdout and exits.",
  "Number of steps in random walk time series. (dflt: 100)",
  "Number of time series to generate. (dflt: 4)",
  "Directory for writing output files. (dflt: \"output\")",
  "Recursion depth for lattice generation. (dflt: 3)"
};

void print_help(void)
{
  int i;

  printf("\nProgram for executing random walk on a lattice. Options:\n\n");
  for (i=0; i<N_OPTIONS; i++) {
    printf("-%c\t\t%s\n",
           LETTERS[i],
           DESCRIPTIONS[i]);
  }
  printf("\nHow you use it is up to you!\n\n");
  return;
}

void parse_options(int *argc, char **argv, void *options[])
{
  int i,j;

  options[OPTION_HELP] = (int *) malloc(sizeof(int));
  * (int *) options[OPTION_HELP] = 0;

  options[OPTION_STEPS] = (int *) malloc(sizeof(int));
  * (int *) options[OPTION_STEPS] = 100;

  options[OPTION_NUMBER] = (int *) malloc(sizeof(int));
  * (int *) options[OPTION_NUMBER] = 4;

  options[OPTION_OUTPUT] = (char *) malloc(BUFFER_SIZE * sizeof(char));
  strcpy((char *) options[OPTION_OUTPUT], "output");

  options[OPTION_DEPTH] = (int *) malloc(sizeof(int));
  * (int *) options[OPTION_DEPTH] = 3;

  for (i=1; i<*argc; i++) {

    if (argv[i][0] != '-' || strlen(argv[i]) != 2) {
      print_help();
      exit(0);
    }
    i++;

    for (j=0; j<N_OPTIONS; j++) {
      if (argv[i-1][1] == LETTERS[j]) {

        switch (j) {

        case OPTION_HELP:
          * (int *) options[OPTION_HELP] = 1;
          break;

        case OPTION_STEPS:
          * (int *) options[OPTION_STEPS] = atoi(argv[i]);
          break;

        case OPTION_NUMBER:
          * (int *) options[OPTION_NUMBER] = atoi(argv[i]);
          break;

        case OPTION_OUTPUT:
          strcpy((char *) options[OPTION_OUTPUT], argv[i]);
          break;

        case OPTION_DEPTH:
          * (int *) options[OPTION_DEPTH] = atoi(argv[i]);
          break;

        default:
          * (int *) options[OPTION_HELP] = 1;
          break;

        }

      }
    }

  }

  if (* (int *) options[OPTION_HELP]) {
    print_help();
    exit(0);
  }

  return;
}
