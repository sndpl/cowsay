
/* https://github.com/schacon/cowsay/blob/master/cowsay */
#include "config.h"
#include "main.h"
#include "info.h"
#include "string.h"
#include "getopt.h"
#include "subset.h"
#include <stdio.h>

extern optind;
extern optopt;
extern optarg;
extern opterr;

char *getstr(optind, argc, argv, cow);

VOID init_cow(cow)
cow_t *cow;
{
  cow->eyes = DEFAULT_EYES;
  cow->tongue = DEFAULT_TONGUE;
  cow->thoughts = DEFAULT_THOUGHTS;
  cow->cowfile = NULL;
  cow->wordwrap = 40;
}

int main(argc, argv)
int argc;
char *argv[];
{
  int c, lines, maxline;
  cow_t cow;
  char *str = alloc(sizeof(char) * 1024);
  init_cow(&cow);

  while ( (c = getopt(argc, argv, "bdgpstwyhvlne:f:T:W:")) != -1) {
    switch(c) {
      case 'b':
        cow.eyes = BORG_EYES;
        break;
      case 'd':
        cow.eyes = DEAD_EYES;
        cow.tongue = DEAD_TONGUE;
        break;
      case 'g':
        cow.eyes = GREEDY_EYES;
        break;
      case 's':
        cow.eyes = STONED_EYES;
        break;
      case 't':
        cow.eyes = TIRED_EYES;
        break;
      case 'w':
        cow.eyes = WIRED_EYES;
        break;
      case 'y':
        cow.eyes = YOUTHFUL_EYES;
        break;
      case 'e':
        strcpy(cow.eyes, optarg);
        /* cow.eyes = optarg; */
        break;
      case 'T':
        strcpy(cow.tongue, optarg);
        break;
      case 'W':
        cow.wordwrap = (int)optarg;
        break;
      case 'n':
        cow.wordwrap = -1;
        break;
      case 'f':
        strcpy(cow.cowfile, optarg);
        break;
      case 'l':
          listcowfiles();
      case 'h':
          printusage();
      case 'v':
          printversion();
      case '?':
          if (optopt == 'e' || optopt == 'f' || optopt == 'W' || optopt == 'T') {
            printf("Option -%c requires an argument.\n", optopt);
          } else {
            printf("Unknown option `-%c'.\n", optopt);
          }
          exit(1);
    }
  }
  printf("\nGet string from command line\n");
  str = getstr(optind, argc, argv, &cow);
  lines = 0;
  maxline = 0;
  printf("\nCount string\n");
  strcnt(str, &lines, &maxline);

  printf("\nPrint string\n");
  printstring(str, lines, maxline);
  printf("\nPrint cow\n");
  printcow(&cow);

  exit(0);
}

char *getstr(optind, argc, argv, cow)
int optind;
int argc;
char *argv[];
cow_t *cow;
{
  int contentlen;
  char c;
  char *content = alloc(sizeof(char) * 1024);
  char *out = alloc(sizeof(char) * 1024);

  content[0] = '\0';
  out[0] = '\0';

  if (optind < argc) {
    while (optind < argc) {
      if (strlen(out)) {
        strcat(out, " ");
      }
      strcat(out, argv[optind++]);
    }
    wrap(content, out, cow->wordwrap);
  } else {
    while((c = getchar()) != EOF) {
      contentlen = strlen(content);
      if (contentlen <= 1024) {
        content[contentlen++] = c;
        content[contentlen] = '\0';
      }
    }
  }

  return content;
}

