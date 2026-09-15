all: ucc-debug ucc-release uccdll-debug uccdll-release ucw-debug ucw-release ucwdll-debug ucwdll-release

ucc-debug:
	cd ucc
	nmake -f Makefile.mak Debug\ucc.exe
	cd ..

ucc-release:
	cd ucc
	nmake -f Makefile.mak Release\ucc.exe
	cd ..

uccdll-debug:
	cd uccdll
	nmake -f Makefile.mak Debug\ucc.dll
	cd ..

uccdll-release:
	cd uccdll
	nmake -f Makefile.mak Release\ucc.dll
	cd ..

ucw-debug:
	cd ucw
	nmake -f Makefile.mak Debug\ucw.exe
	cd ..

ucw-release:
	cd ucw
	nmake -f Makefile.mak Release\ucw.exe
	cd ..

ucwdll-debug:
	cd ucwdll
	nmake -f Makefile.mak Debug\ucw.dll
	cd ..

ucwdll-release:
	cd ucwdll
	nmake -f Makefile.mak Release\ucw.dll
	cd ..
