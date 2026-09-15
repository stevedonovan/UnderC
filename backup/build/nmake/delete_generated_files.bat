@echo off
echo "!!!!WARNING DO ONLY EXUTE THIS BATCH DIRECTLY"
echo "!!!!FROM build/vs2010"
pause
@echo on
del /Q .\ucc\Debug\*
del /Q .\ucc\Release\*
del /Q .\ucc\*.idb .\ucc\*.pdb
del /Q .\uccdll\Debug\*
del /Q .\uccdll\Release\*
del /Q .\uccdll\*.idb .\uccdll\*.pdb
del /Q .\ucw\Debug\*
del /Q .\ucw\Release\*
del /Q .\ucw\*.idb .\ucw\*.pdb
del /Q .\ucwdll\Debug\*
del /Q .\ucwdll\Release\*
del /Q .\ucwdll\*.idb .\ucwdll\*.pdb