#include "getopt.h"

int opterr; /* Error */
int optind = 0; /* Next argv argument */
int optopt; /* Set for unknown arguments */
char *optarg; /* Option parameter if any */

int getopt(argc, argv, opts)
int argc;
char *argv[];
char *opts;
{
  static int sp = 1; /* position within argument */
  int c; /* option letter */
  char *cp; /* -> option in `opts' */

  if (optind == 0) {
    optind = 1;
    opterr = 1;
    optopt = 1;
    optarg = NULL;
  }

  if (sp == 1) { /* fresh argument */
    if(optind >= argc || /* no more arguments */
      argv[optind][0] != '-' ||  /* no more options */
      argv[optind][1] == '\0' /* no more options */
    ) {
        return(EOF);
    } else if(strcmp(argv[optind], "--") == NULL) {
      optind++;   /* skip over "--" */
      return(EOF); /* "--" marks end of options */
    }
  }
  optopt = c = argv[optind][sp]; /* option letter */

  if (c == ':' || (cp=strchr(opts, c)) == NULL) {
    if (argv[optind][++sp] == '\0') { /* end of argument */
      ++optind; /* get ready for next try */
      sp = 1; /* beginning of next argument */
    }
    return('?');
  }

  if(*++cp == ':') {
    if(argv[optind][sp+1] != '\0') {
      optarg = &argv[optind++][sp+1];
    } else if(++optind >= argc) {
      sp = 1;
      return('?');
    } else {
      optarg = argv[optind++];
    }
    sp = 1;
  } else {
    if(argv[optind][++sp] == '\0') {
      sp = 1;
    }
    optind++;
    optarg = NULL;
  }
  return(c);
}

