# Makefile for console-build UnderC C++ interpreter
# vs 1.2.4 Can also build as a shared library, if SO is set

# variables from configure
UC_VERSION=1.3.1
UC_HOME=/home/azisa/uc/UnderC

OBJ = tparser.o function_match.o class.o code.o common.o \
      directcall.o dissem.o engine.o expressions.o \
      function.o breakpoints.o tokens.o keywords.o \
      mangle.o operators.o os.o subst.o \
      table.o templates.o hard_except.o  mstring.o  \
      types.o program.o uc_tokens.o lexer.o main.o \
      errors.o utils.o imports.o ex_vfscanf.o ucri.o

NAME = ucc
DEFINES = -D_CONSOLE
CFLAGS = -Wno-deprecated -Wno-write-strings -m32
ifdef DEBUG
CFLAGS := -g $(CFLAGS)
else
CFLAGS := -O1 $(CFLAGS)
ifdef DYNAMIC
LFLAGS = -Wl,-E
endif
endif

ifdef SO
LFLAGS := $(LFLAGS) -shared
OBJ := $(OBJ) dll_entry.o
# DEFINES = $(DEFINES) -D_USRDLL
DEFINES = -D_USRDLL
NAME = ucc131.so
NO_READLINE = 1
endif

ifndef NO_READLINE
DEFINES := $(DEFINES) -D_USE_READLINE
ifdef REALLY_USE_READLINE
DEFINES := $(DEFINES) -D_REALLY_USE_READLINE
LFLAGS := $(LFLAGS) -lreadline -lncurses
else
OBJ := $(OBJ) linenoise.o
endif
endif

ifndef BSD
LFLAGS := $(LFLAGS) -ldl
endif

ifdef STATIC
LFLAGS := $(LFLAGS) -static
endif

ucc: $(OBJ)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
ifndef SO
ifndef DYNAMIC
	nm -g ucc | awk -f xnames.awk > ../lib/self.imp
ifndef DEBUG
	strip ucc
endif
endif
endif

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(DEFINES) $<

tparser.cpp: parser.y
	bison -y -d parser.y; cp y.tab.c tparser.cpp; cp y.tab.h tparser.h

tparser.o: tparser.cpp

clean:
	rm -f *.o ucc *~ ../lib/string_imp.dll

lib:
	$(CXX) $(CFLAGS) -o ../lib/string_imp.dll -shared -Wl,-export-dynamic ../lib/string_imp.cpp

function_match.o: function_match.cpp function_match.h \
       common.h templates.h

class.o: class.cpp class.h common.h \
   directcall.h operators.h opcodes.h tparser.h std_utils.h
   
linenoise.o: linenoise.c

code.o: code.cpp code.h common.h opcodes.h tparser.h

common.o: common.h function_match.h tparser.h code.h \
	opcodes.h engine.h

# gcc 4.6 optimization omits frame pointers, which upsets callfn
directcall.o: directcall.cpp directcall.h common.h \
        opcodes.h directcall.h mangle.h hard_except.h os.h
	$(CXX) -c $(CFLAGS) -fno-omit-frame-pointer $(DEFINES) directcall.cpp        

dissem.o: dissem.cpp common.h \
        opcodes.h breakpoints.h

engine.o: engine.cpp engine.h common.h errors.h \
        opcodes.h directcall.h breakpoints.h hard_except.h

expressions.o: expressions.cpp expressions.h common.h \
         function_match.h tparser.h operators.h directcall.h

function.o: function.cpp function.h common.h opcodes.h \
         module.h

breakpoints.o: breakpoints.cpp breakpoints.h common.h \
         module.h opcodes.h tokens.h std_utils.h os.h

tokens.o: tokens.cpp tokens.h utils.h

keywords.o: keywords.cpp common.h \
       tparser.h

mangle.o: mangle.cpp mangle.h common.h

operators.o: operators.cpp operators.h common.h \
        tparser.h

os.o: os.cpp os.h

subst.o: subst.cpp

table.o: table.cpp table.h

templates.o: templates.cpp templates.h common.h \
         tparser.h std_utils.h

hard_except.o: hard_except.cpp hard_except.h

types.o: types.cpp types.h common.h \
       templates.h

program.o: program.cpp program.h common.h \
       module.h errors.h utils.h

uc_tokens.o: uc_tokens.cpp uc_tokens.h common.h \
       module.h version.h errors.h

lexer.o: lexer.cpp common.h \
      tparser.h keywords.h operators.h input.h uc_tokens.h

main.o:  main.cpp common.h \
      breakpoints.h module.h uc_tokens.h engine.h mangle.h \
      directcall.h keywords.h operators.h program.h utils.h \
      input.h version.h errors.h

errors.o: errors.cpp errors.h common.h \
      input.h

imports.o: imports.cpp imports.h common.h \
      mangle.h os.h

ucri.o: ucri.cpp module.h directcall.h program.h imports.h

dll_entry.o: dll_entry.cpp module.h engine.h main.h errors.h directcall.h input.h

ex_vfscanf.o: ex_vfscanf.h

utils.o: utils.cpp utils.h classlib.h

mstring.o: mstring.cpp mstring.h


