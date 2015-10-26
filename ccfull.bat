echo Compiling getopt...
cf getopt
cg -k getopt
m80 =getopt/z

echo
echo Compiling opendir...
cf opendir
cg -k opendir
m80 =opendir/z

echo
echo Compiling info...
cf info
cg -k info
m80 =info/z

echo
echo Compiling string...
cf string
cg -k string
m80 =string/z

echo
echo Compiling subset...
cf subset
cg -k subset
m80 =subset/z

echo
echo Creating library...
lib80 cowlib=getopt,opendir,info,string,subset

echo
echo Compiling main...
cf main
cg -k main
m80 =main/z

echo
echo Linking...
l80 B:\lib\CK,main,cowlib,B:\lib\mlib/s,B:\lib\CLIB/S,B:\lib\CRUN/S,b:\lib\CEND,cowsay/N/Y/E:xmain

echo
echo Cleaning up...
del build\*.rel
del build\*.mac
del build\*.sym
move *.rel build
move *.mac build
move *.sym build
