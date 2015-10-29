#include <stdio.h>

struct cow_struct {
  char *eyes;
  char *tongue;
  char *thoughts;
  char *cowfile;
  int wordwrap;
};

typedef struct cow_struct cow_t;

char *getstr(optind, argc, argv, cow);
char file_exist(file);
VOID init_cow(cow);
