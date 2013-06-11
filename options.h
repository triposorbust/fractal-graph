#ifndef __options_h__
#define __options_h__

#ifndef __stdio_h__
#define __stdio_h__
#include <stdio.h>
#endif

#ifndef __stdlib_h__
#define __stdlib_h__
#include <stdlib.h>
#endif

#ifndef __string_h__
#define __string_h__
#include <string.h>
#endif

#define N_OPTIONS 5
enum { OPTION_HELP, OPTION_STEPS, OPTION_NUMBER, OPTION_OUTPUT, OPTION_DEPTH };
void parse_options(int *argc, char **argv, void **options);

#endif
