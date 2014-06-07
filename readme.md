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

UnderC supports two extensions to the old standard, `decltype` and `auto`.
`decltype` roughly corresponds to the new `decltype` keyword;
`auto` is compatible with C++11.

On the Downloads page there are 32-bit binaries for Linux and Windows; these do not have any
extra dependencies (the Linux version merely requires libstdc++ 6). Extract them anywhere.
You may copy the ucc(.exe) executable to your path (or make a link) but it is important
to set the `UC_HOME` environment variable to point to the original directory so that UnderC
knows where to find its include and library files.

	$ export UC_HOME=/home/me/UnderC
	d:\> set UC_HOME=c:\path\to\UnderC

UnderC uses the excellent [linenoise](https://github.com/antirez/linenoise) library for
command history editing, which is statically linked in.

## Building from Source

You will only need g++ to build UnderC; bison is only needed if you 
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
    (std::string) 'hello'
    ;> s.substr(s.find("dolly"),5);
    (std::string) 'dolly'
    ;> s += " you're so swell";
    (std::string&) 'hello dolly you're so swell'
    ;> s.length();
    (int) 27
    ;> // creating a list of strings...
    ;> list<string> ls;
    instantiated: list<string>
    ;> ls.push_back(s);
    ;> ls.push_back("way back when");
    ;> ls.front();
    (std::string&) 'hello dolly you're so swell'
    ;> ls.back();
    (std::string&) 'way back when'
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

## Importing Functions

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

## UnderC Library

There are 'pocket' versions of standard libraries like iostreams and strings, and some common C headers as well.

Since UC is an interpreter,  you can evaluate C++ expressions; this is particularly useful because UC can be built as a shared library.

`void uc_macro_subst(const char* expr, char* buff, int buffsize);`

Expands the text in expr using the UnderC preprocessor, putting the result
into buff.

`void uc_cmd(const char* cmd);`

Executes a UC #-command, like #l or #help.
  uc_cmd() expects the name of the command, _without_ the hash,
  e.g. uc_cmd("l fred.cpp") or uc_cmd("help").

`int uc_exec(const char* expr);`

Evaluates any C++ expression or statement; will return non-zero if
unsuccessful. 

`void uc_result_pos(int ret, char* buff, int buffsize, char* filename, int* line);`

Copies the result of the last uc_exec() into a buffer; if passed a non-zero 
value in 'ret' it will get the error string,
otherwise the string will contain the value of the expression evaluated
(generally anything which is a 'message')
If 'filename' isn't NULL, then it will contain the file at which the message
occured, and 'line' will receive the line number.
 
### Evaluating C++ Expressions

`uc_exec()` is fed a C++ statement as you would type it in, complete with semicolon if required. You may be evaluating a statement for its side-effects, or be declaring something, but sometimes it's necessary to see the result of an operation:

    ;> uc_exec("23+2;");
    ;> char buff[80];
    ;; uc_result_pos(0,buff,80,0,0);
    ;> buff;
    (char*) "(int) 25
    "

The result is in fact exactly what you would get from the interactive UnderC prompt, complete with expression type and line feed at the end.  It's fairly straightforward to strip these elements away.  In fact, the UnderC shared library exports a function called `uc_eval()` which does precisely this.

If the expression fails to compile, or has a run-time error, `uc_exec()` will return a non-zero value.  `uc_result_pos()` can then be used to get the error message.

    ;> int line; char file[120];
    ;> uc_exec("23=2");
    (int) -1
    ;> uc_result(-1,buff,80,file,&line); buff;
    (char*) "Can't assign to a const type"
    ;> file; line;
    (char*) "CON"
    (int) 6

### Regular Expressions with rx++

rx++ is a simple class wrapper around the standard POSIX regular expression calls; for UnderC we're using John Lord's RX library under Windows, and the libc implementation under Linux. Although sometimes tricky to set up, regular expressions are a powerful means of searching and processing text, which AWK and Perl programmers have used very effectively. C++ programmers do not currently have a standard way of using them (although the next iteration of the standard library promises to rectify this, probably by using the BOOST libraries)

    ;> #include <rx++.h>
    ;> Regexp rx("dog");
    ;> char* str = "the dog sat on the mat; the dog went outside";
    ;> rx.match(str);
    (bool) true
    ;> rx.matched();
    (std::string) 'dog'

You may wish to directly access the matched position in the given string:

    ;> rx.index();
    (int) 4
    ;> rx.end_match();
    (int) 7
    ;> int s = rx.index(), e = rx.end_match();
    ;> char buff[80];
    ;> strncpy(buff,str+s,e-s);
    (char*) "dog"

The full POSIX functionality is available.  For example, regular expressions are a 
powerful way to extract formated data such as dates.  Anything inside escaped parentheses
(\(, \)) is a group, which can be extracted from the matched string using a one-based index to the Regexp::matched() method:

    ;> Regexp rdat("\([0-9]*\)/\([0-9]*\)/\([0-9]*\)");
    ;> rdat.match(dates);
    (bool) true
    ;> rdat.matched();     // the whole matched expression
    (std::string) '10/09/2003'
    ;> rdat.matched(1);
    (std::string) '10'
    ;> rdat.matched(2);
    (std::string) '09'
    ;> rdat.matched(3);
    (std::string) '2003'

rx++.h doesn't have the most efficient implemention (in particular the string extraction in `Regexp::matched()` is expensive) but it makes using the POSIX calls less confusing.

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


  

