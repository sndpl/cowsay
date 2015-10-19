CF getopt
CF opendir
CF info
CF string
CF subset

CG -k getopt
CG -k opendir
CG -k info
CG -k string
CG -k subset

M80 =getopt/z
M80 =opendir/z
M80 =info/z
M80 =string/z
M80 =subset/z
lib80 cowlib=getopt,opendir,info,string,subset


CF main
CG -k main
M80 =main/z

L80 B:\LIB\CK,main,cowlib/s,B:\lib\mlib/s,B:\LIB\CLIB/S,B:\LIB\CRUN/S,B:\LIB\CEND,cowsay/N/Y/E:xmain
