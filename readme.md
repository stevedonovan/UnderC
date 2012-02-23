# UnderC C++ Interpreter

UnderC implements a generous subset of the old ISO standard, including
exception handling, namespaces, and templates.  Obviously the more
advanced features are somewhat restricted, but will do fine for
educational purposes.  UnderC compiles source into an intermediate
p-code, so it isn't slow, but speed has not
been a concern yet.  I think correctness, robustness and friendliness
are the main goals, and there has been good progress with the first two.
(The error messages are still a little non-obvious).

This version has been modernized by José Baltasar García Perez-Schofield, so
that it compiles with few complaints with gcc 4.4 and runs fine at -O2. 
Both Windows and Linux is supported, but currently only x86.  The roadmap involves
replacing use of custom assembler dynamic calls with libffii, and  thereby getting
a truly portable version.  (One of the original goals of the project was to allow
compiled C++ shared libraries to be used, but rapid changes and differences in
the ABI between the supported compilers (MSVC and GCC) make this a hard
target, especially for a portable version.)

## Building from Source

You will only need g++ and readline-dev to build UnderC; bison is only needed if you 
need to modify `parser.y`. The incantation should be familiar - go to the `src`
directory and:

    $ ./configure
    $ make
    
The configure step's main job is to encode the home directory directly in the
`ucc` executable.  This ensures that `ucc` can find the `include` and `lib`
directories.  Thereafter, you can make a symlink or even a copy on your path
and `ucc` will remember its home.


## An Example Transcript

    $> UnderC C++ Interpreter vs 1.2.9L
    Steve Donovan, 2001-2003
    This program is GPL'd; see LICENCE for details
    ;> // demonstrating std::string
    ;> string s = "hello dolly";
    ;> s.substr(0,5);
    (string) 'hello'
    ;> s.substr(s.find("dolly"),5);
    (string) 'dolly'
    ;> s += " you're so swell";
    (string&) 'hello dolly you're so swell'
    ;> s.length();
    (int) 27
    ;> // creating a list of strings...
    ;> list<string> ls;
    instantiated: list<string>
    ;> ls.push_back(s);
    ;> ls.push_back("way back when");
    ;> ls.front();
    (string&) 'hello dolly you're so swell'
    ;> ls.back();
    (string&) 'way back when'
    ;> ls.push_front("singing...");
    ;> typedef list<string> LS;
    ;> LS::iterator li;
    ;> for(li=ls.begin();li!=ls.end();++li)
    ;>   cout << *li << endl;
    singing...
    hello dolly you're so swell
    way back when
    ;> // demonstrating vectors...
    ;> vector<int> vi;
    instantiated: vector<int>
    ;> for(int i=0;i<10;i++)
    ;>   vi.push_back(i);
    ;> vi[9];
    (int&) 9
    ;> // a useful shortcut!
    ;> #define FORALL(i,c) \
    ;>  for(i=c.begin();i!=c.end();++i)
    ;> vector<int>::iterator ii;
    ;> int sum = 0;
    ;> FORALL(ii,vi) sum += *ii;
    ;> sum;
    (int) sum = 45
    ;> // typing in a function
    ;> int sqr(int i) { return i*i;}
    ;> sqr(10);
    (int) 100
    ;> double sqr(double x) { return x*x; }
    ;> sqr(1.2);
    (double) 1.44
    ;> // the function main is special
    ;> int main() {
    ;:1} int i,j;
    ;:1} cin >> i >> j;
    ;:1} cout << "i+j = " << i+j << endl;
    ;:1} }
    ;> #r                      
    
## Built-in Functions

The following library functions are already available:

sin, cos, exp, log, tan, atof, atoi, rand, 
strcpy, strncpy, strcat, strcmp, strdup, strtok, strstr, strlen,memmove,
puts,printf,sprintf,gets,fgets,fprintf,fscanf,fread,fwrite,feof,
fopen,fclose,fflush 


## Importing Functions and Classes

It is easy to import any extern "C" function from a DLL. For example,
all modern Linux systems have the runtime shared library, libc.so.6
To make `isalpha()` available, one can say:

    ;> #lib libc.so.6
    ;> extern "C" int isalpha(char);
    ;> #lib
    ;>isalpha('*');
    (int) 0

It is also possible to use '#pragma dlink' which has the same meaning as 
'#lib' but is C++ compatible.

## Command Summary

`defs.h` is the default script that is included when UnderC loads, and
contains the basic standard library includes (it's of course possible
to define and use another `defs.h` by working from another directory). 
If it is not found in the current directory, then the version in the 
UnderC directory will be used.

`ucc` can execute a C/C++ program directly; without parameters it becomes 
interactive: `#help` is your friend.

### Quit Command: #q, #ql

Close session; #ql in addition writes a unique log file, with a
name based on the time and date.

### Load Command: #l <file>

The most important of these is '#l file' which has the same effect
as '#include "file"', except that the system does some clean-ups if
that module has been previously loaded.  It will remove any macros
that were defined in that source file, clean out typedefs, and 
remove any injected namespaces.  So even if the std namespace is 
loaded in your interactive session (and this is the default) this
doesn't apply to any #l'd files.

After the first load, '#l' on its own will reload the last file.

### Run Program: #r <file> <command-line arguments>

After a file containing a main() function is loaded, and successfully
compiled, #r will let you run that program with the supplied
arguments.  The program is run in its own thread and console window,
so you can interactively evaluate variables etc while the program is
waiting for input.

### Execute shell command: #x <cmd>

For example, #x dir /w

### Load Library command: #lib <dll>

After this command, any prototype or class definition is assumed
to be a request for dynamically linking to the library.


  

