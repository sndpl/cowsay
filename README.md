# Cowsay #

This is a MSX-C version of cowsay.

## Usage #

cowsay [OPTION] ...  

-b borg mode  
-d dead mode  
-g gready mode  
-s stoned mode  
-t tired mode  
-w wired mode  
-y youthfull mode  
-e manually specifies eyes (DEFAULT = oo)  
-T manually specifies tongue  
-f select cow file  
-l display COWPATH directory and exit  
-W Word wrap on x column (DEFAULT = 40)  

-h display this help and exit  
-v output version information and exit  

When no text is given the command will wait for text from the command line which can be ended with ```ctrl+Z```. It's also possible to pipe text into the cowsay program, e.g.:  

```
dir *.c | cowsay
```

## Environment ##

To tell the ```cowsay``` package where the cows are, set your ```COWPATH``` environment variable to the directory these cows are in. At the moment only **one** path can be set, e.g.:

```
set COWPATH=A:/cows
```

## Add your own cow templates ##
These are the simplest sorts of cows; they are just a plaintext file with the ASCII that is the cow in it. It has extension '.cow'.  

Use $eyes, $tongue and $thoughts in the file. $eyes and $tongue are replaced by the user-specified eyes and tongue, being strings of length two (if the user specifies longer eyes only the first two characters are used; if they specify a one-character eye it is padded with a space). The $thoughts token is the 'stem' part of the speech bubble, not the speech bubble itself. For a cow that is thinking, this is 'o' (dots leading up to the thought bubble); for a cow that is speaking, this is '\' (speech bubble stem).  

Any line starting with a '#' will be ignored, even if it is part of your cow!. If your cow has lines that start with '#' that should be part of the cow, indent the entire cow one space.  

Example (the default cow, you can see him at the start of the Readme):

```
# e.g. as default.cow
        $thoughts   ^__^
         $thoughts  ($eyes)\_______
            (__)\       )\/\
             $tongue ||----w |
                ||     ||
```

# Developer notes #

To compile the source code, use the following commands:

```
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

```

The best way is to copy the CK, MLIB, CLIB, CRUN, CEND rel files to this directory and update the L80 line (because it may not be longer then 127 chars!).

## TODO ##

- Update the Compile script by creating a cowsay library first with M80 and use this library with the L80 command.
- Fix bugs :)
