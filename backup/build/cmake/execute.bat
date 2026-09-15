@echo off
:configtest
IF "%1"=="" goto help
goto compile

:help
echo Please execute this bat like this:
echo execute.bat [project]
echo.
echo Aviable projects are:
echo ucc-debug,ucc-release,uccdll-debug,uccdll-release,
echo ucw-debug,ucw-release,ucwdll-debug,ucwdll-release,
echo all
echo.
echo Where all compiles everything.
pause
exit

:compile
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
set PATH=C:\gnuwin32\bin;%PATH%
cmake -f Makefile.mak %1
pause
exit
