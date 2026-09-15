#include "iostrm.h"
#define ostream 666
#include <list>
//~ #include <map>
//~ #include <algorithm>
using namespace std;

void dump(ostream& out)
{
	out << "hello dolly" << endl;
}

int main()
{
	ofstream out("tmp.txt");
	dump(out);
	return 0;
}
