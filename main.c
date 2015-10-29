#include <stdio.h>      /* It's kind of a convention to put the
         system includes first */

/* https://github.com/schacon/cowsay/blob/master/cowsay */

#include "config.h"
#include "main.h"
#include "info.h"
#include "string.h"
#include "getopt.h"
#include "subset.h"

#define DEBUG 0

extern optind;
extern optopt;
extern optarg;
extern opterr;


VOID init_cow(cow)
cow_t *cow;
{
  cow->eyes = alloc(3);
  cow->eyes = DEFAULT_EYES;
  cow->tongue = alloc(3);
  cow->tongue = DEFAULT_TONGUE;
  cow->thoughts = alloc(3);
  cow->thoughts = DEFAULT_THOUGHTS;
  cow->cowfile = alloc(13);
  cow->cowfile = DEFAULT_COWFILE;
  cow->wordwrap = 40;
}

char main(argc, argv)
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
        cow.eyes = (char *)optarg;
        break;
      case 'T':
        cow.tongue = (char *)optarg;
        break;
      case 'W':
        cow.wordwrap = (int)optarg;
        break;
      case 'n':
        cow.wordwrap = -1;
        break;
      case 'f':
          cow.cowfile = (char *)optarg;
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
  str = getstr(optind, argc, argv, &cow);
  lines = 0;
  maxline = 0;
  strcnt(str, &lines, &maxline);

#ifdef DEBUG
  printf("Eyes: %s\n", cow.eyes);
  printf("Tongue: %s\n", cow.tongue);
  printf("File: %s\n", cow.cowfile);
#endif  
  if (!file_exist(cow.cowfile)) {
    printf("cowsay: Could not find %s cowfile!\n", cow.cowfile);
    exit(1);
  }
  printstring(str, lines, maxline);
  printcow(&cow);

  exit(0);
}

char file_exist(file)
char *file;
{
  FILE *fp;
  char *cowpath;
  char cowfile[64];
  cowpath = getenv("COWPATH");
  if (!strlen(cowpath)) {
    puts("Cow path not set, use SET COWPATH= to set the path where the cow templates are.\n");
    exit(1);
  }

  strcpy(cowfile, cowpath);
  strcat(cowfile, "\\");
  strcat(cowfile, file);
  strcat(cowfile, ".cow");

  if ((fp = fopen(cowfile, "r")) == NULL) {
    return FALSE;
  }
  fclose(fp);
  return TRUE;
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
