#include <stdio.h>
#include <bdosfunc.h>

#define	S_RO		0x01
#define	S_HIDDEN	0x02
#define	S_SYSTEM	0x04
#define	S_VOLUME	0x08
#define	S_DIRECT	0x10
#define	S_ARCHIV	0x20
/* reserved		0x40 */
#define	S_DEVICE	0x80

#define	SEARCH_MASK	(unsigned)((S_RO|S_HIDDEN|S_SYSTEM|S_DIRECT) * 256)


VOID	_ffirst(pattern, fib, regs);
VOID	_fnext(fib, regs);
VOID	opendir(pattern);
