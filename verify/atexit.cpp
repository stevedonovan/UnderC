#include <iostream>
using namespace std;

typedef void (*Voidfn)();

class Atexit {
    Voidfn fun;
public:
    Atexit(Voidfn f) : fun(f) {}
        
    ~Atexit() {
        fun();
    }
};

void goodbye() {
    cerr << "goodbye" << endl;
}

int main() {
    Atexit a(goodbye);
    cerr << "hello" << endl;
    return 0;   
}