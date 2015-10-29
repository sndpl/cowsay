#include <stdio.h>

#include "config.h"
#include "main.h"
#include "string.h"
#include "opendir.h"
#include "subset.h"

VOID printstring(str, lines, maxline)
char *str;
int lines;
int maxline;
{
   int i, j, line, linelen, strl;

#ifdef DEBUG
   printf("String2:\n%s\n\n", str);
   printf("%c\n", str[0]);
   printf("%c\n", str[1]);
   printf("%c\n\n", str[2]);
#endif

	puts(" ");

   strrepeat("_", maxline + 2);

   /* One line */
   if (lines == 1) {
     printf("\n< %s >\n ", str);
     strrepeat("-", maxline + 2);
	   putchar('\n');
     return 0;
   }

   /* Multi Line */
   i = 0;
   linelen = 0;
   line = 0;
   strl = strlen(str);
#ifdef DEBUG
	printf("strlen: %d\n", strl);
#endif
 	 puts("\n/ ");
   for(j = 0; j < strl; j++)
   {
     if (str[j] == '\n') {

       /* spaces */
       strrepeat(" ", maxline - linelen);

       /* close line */
       if (line  == 0) {
	       puts(" \\\n");
       } else if (line == lines -1) {
	       puts(" /\n ");
       } else {
	       puts(" |\n");
       }
       line++;

       /* open line */
       if (line == lines -1) {
	       puts("\\ ");
       } else {
	       puts("| ");
       }
       linelen = 0;
     } else {
       printf("%c", str[j]);
       linelen++;
     }
   }
   strrepeat(" ", maxline - linelen);
   puts(" /\n ");
   strrepeat("-", maxline + 2);
   putchar('\n');

}

VOID listcowfiles()
{
  char *cowpath[64];
  char *cowpathFull[64];
  cowpath = getenv("COWPATH");
  if (!strlen(cowpath)) {
    puts("Cow path not set, use SET COWPATH= to set the path where the cow templates are.\n");
    exit(1);
  }
  printf("Supported cows in %s :\n\n", cowpath);
  strcpy(cowpathFull, cowpath);
  strcat(cowpathFull, "\\");
  strcat(cowpathFull, "*.cow");
  opendir(cowpathFull);
  exit(0);
}

VOID	printcow(cow)
cow_t	*cow;
{
#ifdef DEBUG
 	puts("\nPrint the cow\n");
#endif
 	if (cow->cowfile == NULL) {
		printdefaultcow(cow);
	} else {
		loadcow(cow);
	}
}

VOID	loadcow(cow)
cow_t	*cow;
{
	FILE	*fp;
	char	buf[256];
	char	*line;
	char	cowfile[64];

	strcpy(cowfile, getenv("COWPATH"));
	strcat(cowfile, "\\");
	strcat(cowfile, cow->cowfile);
	strcat(cowfile, ".cow");

#ifdef DEBUG
	printf("DEBUG: Load cowfile: %s\n", cowfile);
#endif

	if ((fp = fopen(cowfile, "r")) == NULL) {
		if (cow->cowfile == DEFAULT_COWFILE) {
			printdefaultcow();
			return;
		}
		printf("Can't open cow file: %s %s!", cowfile, cow->cowfile);
		exit(1);
	}
#ifdef DEBUG
	puts("\nStart cow\n");
#endif
	while (fgets(buf, 256, fp)) {
		line = replace(buf, THOUGHTS, cow->thoughts);
		line = replace(line, TONGUE, cow->tongue);
		line = replace(line, EYES, cow->eyes);
		printf("%s", line);
	}
#ifdef DEBUG
	puts("\nEnd cow\n");
#endif
	fclose(fp);
}

VOID	printdefaultcow(cow)
cow_t	*cow;
{
#ifdef DEBUG
	puts("DEBUG: Printing default cow.\n");
#endif
	printf("       %s  ^__^\n",		cow->thoughts);
	printf("        %s (%s)\\_______\n",	cow->thoughts, cow->eyes);
	puts("          (__)\\       )\\/\\\n");
	printf("           %s ||----w |\n",	cow->tongue);
	puts("              ||     ||\n");
}
