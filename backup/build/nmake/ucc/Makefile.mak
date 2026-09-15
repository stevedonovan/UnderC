!INCLUDE ..\Makefile.globals.mak
#CL command line options
CL_DEFINES_D=/D "_WIN32" /D "_MFC_VER" /D "_DEBUG" /D "_CONSOLE" /D "NFAKE_IOSTREAM" /D "NUSRDLL" /D "NMSTRING" /D "_MBCS" /D "_CRT_SECURE_NO_WARNINGS"
CL_DEFINES_R=/D "_WIN32" /D "_MFC_VER" /D "NDEBUG" /D "_CONSOLE" /D "NFAKE_IOSTREAM" /D "NUSRDLL" /D "NMSTRING" /D "_MBCS" /D "_CRT_SECURE_NO_WARNINGS"
#LINK command line options

all: Debug\ucc.exe Release\ucc.exe

{..\..\..\src\}.cpp{Debug\}.obj:
	$(CPP) $(CL_INCLUDE_D) $(CL_DEFINES_D) $(CL_OPTIONS_D) /Fo$*.obj -c $<

{..\..\..\src\}.cpp{Release\}.obj:
	$(CPP) $(CL_INCLUDE_R) $(CL_DEFINES_R) $(CL_OPTIONS_R) /Fo$*.obj -c $<

Debug\tparser.cpp Debug\tparser.h:
	call "..\..\bbison.bat" .\Debug ..\..\..

Release\tparser.cpp Release\tparser.h:
	call "..\..\bbison.bat" .\Release ..\..\..

Debug\tparser.obj:
	$(CPP) $(CL_INCLUDE_D) $(CL_DEFINES_D) $(CL_OPTIONS_D) /Fo$@ -c Debug\tparser.cpp

Release\tparser.obj:
	$(CPP) $(CL_INCLUDE_R) $(CL_DEFINES_R) $(CL_OPTIONS_R) /Fo$@ -c Release\tparser.cpp

Debug\ucc.exe: Debug\tparser.cpp $(BASE_OBJS_D)
	link $(LOPTIONS_EXE) /OUT:$@ $(LMANIFEST_EXE) $(LSYSLIBS_EXE) $(BASE_OBJS_D) /ALLOWISOLATION /DEBUG /PDB:Debug\ucc.pdb

Release\ucc.exe: Release\tparser.cpp $(BASE_OBJS_R)
	link $(LOPTIONS_EXE) /OUT:$@ $(LMANIFEST_EXE) $(LSYSLIBS_EXE) $(BASE_OBJS_R) /ALLOWISOLATION
