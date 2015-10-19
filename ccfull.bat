CF getopt
CF opendir
CF info
CF string
CF subset
CF main

CG -k getopt
CG -k opendir
CG -k info
CG -k string
CG -k subset
CG -k main

M80 =getopt/z
M80 =opendir/z
M80 =info/z
M80 =string/z
M80 =subset/z
M80 =main/z

L80 B:\LIB\CK,main,subset,getopt,opendir,info,string,B:\lib\mlib/s,B:\LIB\CLIB/S,B:\LIB\CRUN/S,CEND,cowsay/N/Y/E:xmain
xmain
