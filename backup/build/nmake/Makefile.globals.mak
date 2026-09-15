#Files used for every project
BASE_OBJS_D=Debug\breakpoints.obj Debug\class.obj Debug\code.obj Debug\common.obj Debug\directcall.obj Debug\dissem.obj Debug\engine.obj Debug\errors.obj Debug\ex_vfscanf.obj Debug\expressions.obj Debug\function.obj Debug\function_match.obj Debug\hard_except.obj Debug\imports.obj Debug\iostrm.obj Debug\keywords.obj Debug\lexer.obj Debug\main.obj Debug\mangle.obj Debug\operators.obj Debug\os.obj Debug\program.obj Debug\subst.obj Debug\table.obj Debug\templates.obj Debug\threads.obj Debug\tokens.obj Debug\types.obj Debug\uc_tokens.obj Debug\ucri.obj Debug\utils.obj Debug\tparser.obj
DLL_OBJS_D=Debug\dll_entry.obj
WCON_OBJS_D=Debug\wcon.obj Debug\twl.obj Debug\twl_misc.obj Debug\mstring.obj Debug\xt_int.obj Debug\uc_graphics.obj
BASE_OBJS_R=Release\breakpoints.obj Release\class.obj Release\code.obj Release\common.obj Release\directcall.obj Release\dissem.obj Release\engine.obj Release\errors.obj Release\ex_vfscanf.obj Release\expressions.obj Release\function.obj Release\function_match.obj Release\hard_except.obj Release\imports.obj Release\iostrm.obj Release\keywords.obj Release\lexer.obj Release\main.obj Release\mangle.obj Release\operators.obj Release\os.obj Release\program.obj Release\subst.obj Release\table.obj Release\templates.obj Release\threads.obj Release\tokens.obj Release\types.obj Release\uc_tokens.obj Release\ucri.obj Release\utils.obj Release\tparser.obj
DLL_OBJS_R=Release\dll_entry.obj
WCON_OBJS_R=Release\wcon.obj Release\twl.obj Release\twl_misc.obj Release\mstring.obj Release\xt_int.obj Release\uc_graphics.obj
#Default CL command line options
CL_INCLUDE_D=/I".\Debug"
CL_OPTIONS_D=/ZI /nologo /W3 /WX- /Od /Oy- /Gm /EHsc /RTC1 /GS /fp:precise /Zc:wchar_t /Zc:forScope /Gd /analyze- /errorReport:queue /MDd
CL_INCLUDE_R=/I".\Release"
CL_OPTIONS_R=/Zi /nologo /W3 /WX- /O2 /Oi /Oy- /GL /Gm- /EHsc /GS /Gy /fp:precise /Zc:wchar_t /Zc:forScope /Gd /analyze- /errorReport:queue /MD
#Default Linker options
LSYSLIBS_EXE=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
LOPTIONS_EXE=/NOLOGO /TLBID:1 /DYNAMICBASE /NXCOMPAT /MACHINE:X86 /ERRORREPORT:QUEUE
LMANIFEST_EXE=/ManifestFile:$@.intermediate.manifest /MANIFESTUAC:"level='asInvoker' uiAccess='false'"