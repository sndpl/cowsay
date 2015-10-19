#include <stdio.h>

int getopt(argc, argv, opts);

 /* error => print message */
int optind = 1;          /* next argv[] index */
int optopt = 1;          /* Set for unknown arguments */
char *optarg = NULL;     /* option parameter if any */

int getopt(argc, argv, opts);
