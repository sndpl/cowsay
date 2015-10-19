#include "config.h"
#include "info.h"
#include <stdio.h>

VOID printusage()
{
  printf(" \
    %s %d.%d.%d The classic cowsay program written in MSX-C.\n \
    Usage: cowsay [OPTION] ...\n \
    \n \
    -b borg mode\n \
    -d dead mode\n \
    -g greedy mode\n \
    -s stoned mode\n \
    -t tired mode\n \
    -w wired mode\n \
    -y youthful mode\n \
    -e manually specifies eyes (DEFAULT = oo)\n \
    -T manually specifies tongue\n \
    -f select cow file\n \
    -l display COWPATH directory and exit\n \
    -W Word wrap on x column (DEFAULT = 40)\n \
    \n \
    -h, display this help and exit\n \
    -v, output version information and exit\n \
    \n \
    Report bugs to %s <%s>\n \
    ", PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL,
    AUTHOR, MAIL_TO);

  exit(0);
}

VOID printversion()
{
  printf("%s %d.%d.%d\n", PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL);
  exit(0);
}
