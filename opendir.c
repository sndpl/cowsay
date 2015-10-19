#include "opendir.h"


VOID	_ffirst(pattern, fib, regs)
char	*pattern;
FIB	*fib;
XREG	*regs;
{
	regs->bc = SEARCH_MASK | (unsigned)_FFIRST;
	regs->de = (unsigned)pattern;
	regs->ix = (unsigned)fib;
	callxx(BDOS, regs);
}

VOID	_fnext(fib, regs)
FIB	*fib;
XREG	*regs;
{
	regs->bc = SEARCH_MASK | (unsigned)_FNEXT;
	regs->ix = (unsigned)fib;
	callxx(BDOS, regs);
}

VOID	opendir(pattern)
char	*pattern;
{
	FIB		fib;
	BOOL		done;
	XREG		regs;
  int i = 0;

	/* Make sure the whole FIB is set to 0			*/
	memset(&fib, (char)0, sizeof(FIB));

	/* Search for first entry */
	_ffirst(pattern, &fib, &regs);


	if (!(regs.af & 0xff00)) {
		/* Found at least one matching file	*/
    printf("%s\n", fib.name);
    i++;

		/* Look for more matches		*/
		done = FALSE;

		while(!done) {
			_fnext(&fib, &regs);
			if (regs.af & 0xff00) {
				done = TRUE;
			} else {
				printf("%s\n", fib.name);
        i++;
			}
		}
	}

  if (i == 0) {
    printf("No .cow files found!\n\n");
  }
}
