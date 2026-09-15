@echo off
exit
echo "!!!!WARNING DO ONLY EXUTE THIS BATCH DIRECTLY"
echo "!!!!FROM build/vs2010"
pause
@echo on
RMDIR .\Debug /s /q
RMDIR .\Release /s /q
RMDIR .\ipch /s /q
RMDIR .\ucc\Debug /s /q
RMDIR .\ucc\Release /s /q
RMDIR .\uccdll\Debug /s /q
RMDIR .\uccdll\Release /s /q
RMDIR .\ucw\Debug /s /q
RMDIR .\ucw\Release /s /q
RMDIR .\ucwdll\Debug /s /q
RMDIR .\ucwdll\Release /s /q
del vs2010.sdf
