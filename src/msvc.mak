# Microsoft nmake file for console-build UnderC C++ interpreter

OBJ = tparser.obj function_match.obj class.obj code.obj common.obj \
      directcall.obj dissem.obj engine.obj expressions.obj \
      function.obj breakpoints.obj tokens.obj keywords.obj \
      mangle.obj operators.obj os.obj subst.obj \
      table.obj templates.obj hard_except.obj  mstring.obj  \
      types.obj program.obj uc_tokens.obj lexer.obj main.obj \
      errors.obj utils.obj imports.obj ex_vfscanf.obj ucri.obj

# throw in a /MD here if you want a non-static link against the MS runtime
CXXFLAGS = /nologo /EHsc -c /O1 /WX /DNO_READLINE /D_CONSOLE

ucc: $(OBJ)
	link /nologo $(OBJ) /out:ucc.exe

.cpp.obj:
	cl $(CXXFLAGS) $<

tparser.obj: tparser.cpp

clean:
	del *.obj

function_match.obj: function_match.cpp function_match.h \
       common.h templates.h

class.obj: class.cpp class.h common.h \
   directcall.h operators.h opcodes.h tparser.h std_utils.h

linenoise.obj: linenoise.c

code.obj: code.cpp code.h common.h opcodes.h tparser.h

common.obj: common.h function_match.h tparser.h code.h \
	opcodes.h engine.h

directcall.obj: directcall.cpp directcall.h common.h \
        opcodes.h directcall.h mangle.h hard_except.h os.h

dissem.obj: dissem.cpp common.h \
        opcodes.h breakpoints.h

engine.obj: engine.cpp engine.h common.h errors.h \
        opcodes.h directcall.h breakpoints.h hard_except.h

expressions.obj: expressions.cpp expressions.h common.h \
         function_match.h tparser.h operators.h directcall.h

function.obj: function.cpp function.h common.h opcodes.h \
         module.h

breakpoints.obj: breakpoints.cpp breakpoints.h common.h \
         module.h opcodes.h tokens.h std_utils.h os.h

tokens.obj: tokens.cpp tokens.h utils.h

keywords.obj: keywords.cpp common.h \
       tparser.h

mangle.obj: mangle.cpp mangle.h common.h

operators.obj: operators.cpp operators.h common.h \
        tparser.h

os.obj: os.cpp os.h

subst.obj: subst.cpp

table.obj: table.cpp table.h

templates.obj: templates.cpp templates.h common.h \
         tparser.h std_utils.h

hard_except.obj: hard_except.cpp hard_except.h

types.obj: types.cpp types.h common.h \
       templates.h

program.obj: program.cpp program.h common.h \
       module.h errors.h utils.h

uc_tokens.obj: uc_tokens.cpp uc_tokens.h common.h \
       module.h version.h errors.h

lexer.obj: lexer.cpp common.h \
      tparser.h keywords.h operators.h input.h uc_tokens.h

main.obj:  main.cpp common.h \
      breakpoints.h module.h uc_tokens.h engine.h mangle.h \
      directcall.h keywords.h operators.h program.h utils.h \
      input.h version.h errors.h

errors.obj: errors.cpp errors.h common.h \
      input.h

imports.obj: imports.cpp imports.h common.h \
      mangle.h os.h

ucri.obj: ucri.cpp module.h directcall.h program.h imports.h

dll_entry.obj: dll_entry.cpp module.h engine.h main.h errors.h directcall.h input.h

ex_vfscanf.obj: ex_vfscanf.h

utils.obj: utils.cpp utils.h classlib.h

mstring.obj: mstring.cpp mstring.h


