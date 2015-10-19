#include "string.h"
#include <stdio.h>

VOID strrepeat(input, multiplier)
char *input;
int multiplier;
{
  int i;
  for (i = 0; i < multiplier; i++)
    printf(input);
}

/*
The strdup() function returns a pointer to a new string which is a duplicate of the string s.
Memory for the new string is obtained with malloc(3), and can be freed with free(3).
*/
char *strdup(s)
char *s;
{
    char *p = malloc(strlen(s) + 1);
    if(p) { strcpy(p, s); }
    return p;
}

/*
Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
*/
char *strstr(searchee, lookfor)
char *searchee;
char *lookfor;
{
  /* Less code size, but quadratic performance in the worst case.  */
  if (*searchee == 0) {
    if (*lookfor) {
      return (char *) NULL;
    }
    return (char *) searchee;
  }

  while (*searchee) {
    size_t i;
    i = 0;

    while (1) {
      if (lookfor[i] == 0) {
        return (char *) searchee;
      }

      if (lookfor[i] != searchee[i]) {
        break;
      }
      i++;
    }
    searchee++;
  }
  return (char *) NULL;
}

/*
Replace substr in string with replacement
*/
char *replace(original, pattern, replacement)
char *original;
char *pattern;
char *replacement;
{
  int replen = strlen(replacement);
  int patlen = strlen(pattern);
  int orilen = strlen(original);
  int retlen = 0;
  char *returned;

  int patcnt = 0;
  char *oriptr;
  char *patloc;

  /* find how many times the pattern occurs in the original string */
  for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
  {
    patcnt++;
  }

  /* allocate memory for the new string */
  retlen = orilen + patcnt * (replen - patlen);
  returned = (char *) malloc( sizeof(char) * (retlen + 1) );

  if (returned != NULL) {
    /* copy the original string, */
    /* replacing all the instances of the pattern */
    char * retptr = returned;
    for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen) {
      int skplen = patloc - oriptr;
      /* copy the section until the occurence of the pattern */
      strncpy(retptr, oriptr, skplen);
      retptr += skplen;
      /* copy the replacement */
      strncpy(retptr, replacement, replen);
      retptr += replen;
    }
    /* copy the rest of the string. */
    strcpy(retptr, oriptr);
  }
  return returned;

}


/*
Wrap a string at x columns
*/
VOID wrap(out, str, columns)
char *out;
char *str;
int columns;
{
    int len, n, w;
    int wordlen=0;
    int linepos=0;
    int outlen=0;
    char *word;
    len = strlen(str) + 1;
    word = malloc(len * sizeof(char));

    for(n=0; n<=len; n++) {
        if(str[n] == ' ' || str[n] == '\n' || n == len ) {
            if(linepos > columns) {
                out[outlen++] = '\n';
                linepos = wordlen;
            }

            for(w=0; w<wordlen; w++) {
                out[outlen++] = word[w];
                word[w] = '\0';
            }

            if(n == len) {
                out[outlen] = '\0';
            } else if(str[n] == '\n') {
                out[outlen] = str[n];
                linepos=0;
            } else {
                out[outlen] = ' ';
                linepos++;
            }

            outlen++;
            wordlen=0;
        } else {
            word[wordlen++] = str[n];
            linepos++;
        }
    }
    free(word);
}

int strmax(optind, argc, argv)
int optind;
int argc;
char *argv[];
{
    int len = 0;
    int max = 0;
    char *option;
    int words = 0;

    while (optind < argc) {
        option = argv[optind++];
        printf("%s\n", option);
        len = strlen(option);
        max += len;
        words++;
    }
    max += words-1;
    return max;
}

VOID strcnt(content, lines, maxline)
char *content;
int *lines;
int *maxline;
{
  int i,len, length;
  len = 0;
  length = strlen(content);
  for (i = 0; i < length; i++) {
    if (content[i] == '\n') {
      *lines = *lines + 1;
      if (len > *maxline) {
        *maxline = len;
      }
      len = 0;
    }
    len++;
  }
  if (len > *maxline) {
    *maxline = len;
  }
  *lines = *lines + 1;
}
