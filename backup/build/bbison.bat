SET PATH=%PATH%;C:\gnuwin32\bin
bison -y --output="%1\tparser.cpp" --defines="%1\tparser.h" "%2\src\build\parser.y"
