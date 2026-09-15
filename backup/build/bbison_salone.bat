SET PATH=%PATH%;C:\gnuwin32\bin
bison -y -d -v parser.y
copy y.tab.c tparser.cpp
copy y.tab.h tparser.h
pause