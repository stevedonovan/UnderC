/* Interpreted exception handling.
 *
 * The try-block marker object and the thrown-object slot both carry host
 * addresses, and THROW_EX carries a parser type handle rather than a Type
 * object.  All three used to be int-sized or misdecoded, which made every
 * throw either miss its catch block or fault.
 */
#include <stdio.h>
#include <uc_except.h>

class Derived: public Exception {
public:
    Derived() : Exception("derived") {}
};

static int caught_int()
{
    try {
        throw 42;
    } catch(int value) {
        return value;
    }
    return -1;
}

static const char *caught_object()
{
    try {
        throw Exception("boom");
    } catch(Exception e) {
        return e.what();
    }
    return "";
}

static const char *caught_base()
{
    try {
        throw Derived();
    } catch(Exception e) {
        return e.what();
    }
    return "";
}

static int caught_any()
{
    try {
        throw 7;
    } catch(...) {
        return 1;
    }
    return 0;
}

static int caught_nested()
{
    int total = 0;
    try {
        try {
            throw 3;
        } catch(int inner) {
            total += inner;
            throw 4;
        }
    } catch(int outer) {
        total += outer;
    }
    return total;
}

static int uncaught_type_falls_through()
{
    int reached = 0;
    try {
        try {
            throw 1;
        } catch(char *ignored) {
            reached = 1;
        }
    } catch(int value) {
        reached = 2 + value;
    }
    return reached;
}

int main()
{
    if (caught_int() != 42) return 1;
    if (strcmp(caught_object(), "boom") != 0) return 2;
    if (strcmp(caught_base(), "derived") != 0) return 3;
    if (caught_any() != 1) return 4;
    if (caught_nested() != 7) return 5;
    if (uncaught_type_falls_through() != 3) return 6;
    printf("exception-handling-ok\n");
    return 0;
}
